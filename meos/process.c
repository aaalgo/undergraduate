/* filename: process.c
   by Dong Wei */
#include <io.h>
#include <clib.h>
#include <vga.h>
#include <gdt.h>
#include <process.h>

volatile pcb_t *current = NULL;
volatile pcb_t *sleeping = NULL;
pcb_t *running = NULL;
volatile int critical = FALSE;

int process_init (void)
{
	running = (pcb_t *)tss_alloc(NULL);
	running->sel = gdt_insert(make_tss_desc((tss_t *)running));
	running->prev = running->next = running;
	running->lprev = running->lnext = running;
	running->pid = 0;
	strcpy(running->cmdline, "init");
	running->state = STATE_RUNNING;
	asm("ltr %0\n"::"m"(running->sel));
	current = running;
	critical = FALSE;
	sleeping = NULL;
	return TRUE;
}

int schedule (void)
{
	pcb_t *next;
	if (critical) return TRUE;
	next = current->next;
	if (current == next) return TRUE;
	current->state = STATE_ACTIVE;
	current = next;
	current->state = STATE_RUNNING;
	switchto(current->sel);
	return TRUE;
}

pcb_t *create_process (void *start, void *param, char *cmdline)
{
	pcb_t *new;
	cli();
	static int cid = 1;	
	new = (pcb_t *)tss_alloc(start);
	assert(new != NULL);
	if (new ==  NULL) return NULL;
	new->sel = gdt_insert(make_tss_desc((tss_t *)new));
	assert(new->sel != 0);
	if (new->sel == 0)
	{
		page_free(new);
		return NULL;
	}
	else
	{
		new->next = current->next;
		new->prev = current;
		current->next->prev = new;
		current->next = new;
	}
	new->tss.esp -= 4;
	*(void **)(new->tss.esp) = param;
	new->tss.esp -= 4;
	*(void **)(new->tss.esp) = exit;
	new->pid = cid;
	new->state = STATE_ACTIVE;
	new->lprev = running->lprev;
	new->lnext = running;
	running->lprev->lnext = new;
	running->lprev = new;
	strcpy(new->cmdline, cmdline);
	cid++;
	sti();
	return new;
}

void exit (int f)
{
	pcb_t *old;
	if (current == running) return;
	cli();
	old = current;
	current = old->next;
	current->prev = old->prev;
	old->prev->next = current;
	old->lprev->lnext = old->lnext;
	old->lnext->lprev = old->lprev;
	page_free(old);
	switchto(current->sel);
	sti();
}

int sleep (int n)
{
	pcb_t *old;
	if (current == running) return TRUE;
	if (n <= 0) return TRUE;
	cli();
	current->state = STATE_SLEEP;
	old = current;
	current = old->next;
	current->state = STATE_RUNNING;
	old->prev->next = current;
	current->prev = old->prev;
	old->sleep = n;
	if (sleeping == NULL)
	{
		sleeping = old->prev = old->next = old;
	}
	else
	{
		old->next = sleeping;
		old->prev = sleeping->prev;
		sleeping->prev->next = old;
		sleeping->prev = old;
		sleeping = old;
	}
	switchto(current->sel);
	sti();
	return TRUE;
}

void do_timer (void)
{
	pcb_t *tmp, *next;
	outb(0x20, 0x20);
	if (sleeping != NULL)
	{
		tmp = sleeping;
		do
		{
			next = tmp->next;
			tmp->sleep--;
			if (tmp->sleep == 0)
			{
				if (next == tmp)
				{
					sleeping = NULL;
					next = NULL;
				}
				else
				{
					tmp->prev->next = next;
					next->prev = tmp->prev;
				}
				tmp->next = current;
				tmp->prev = current->prev;
				current->prev->next = tmp;
				current->prev = tmp;
			}
			tmp = next;
		} while (tmp != sleeping);
	}
	if (!critical) schedule();
}

void checksem (sem_t *sem)
{
	int n;
	pcb_t *p;
	if (sem->n >= 0)
	{
		assert(sem->wait == NULL);
	}
	else
	{
		n = 1;
		for (p = sem->wait->next; p != sem->wait; p = p->next)
			n++;
		assert(sem->n == n);
	}
}

int sem_p (sem_t *sem)
{
	pcb_t *old;
	cli();
	sem->n--;
	if (sem->n < 0)
	{
		current->state = STATE_BLOCK;
		old = current;
		current = old->next;
		current->state = STATE_RUNNING;
		old->prev->next = current;
		current->prev = old->prev;
		if (sem->wait == NULL)
		{
			sem->wait = old->prev = old->next = old;
		}
		else
		{
			old->next = sem->wait;
			old->prev = sem->wait->prev;
			sem->wait->prev->next = old;
			sem->wait->prev = old;
		}
		switchto(current->sel);
	}
	sti();
	checksem(sem);
	return TRUE;
}

int sem_v (sem_t *sem)
{
	pcb_t *new;
	cli();
	sem->n++;
	if (sem->n <= 0)
	{
		new = sem->wait;
		if (sem->n == 0)
		{
			sem->wait = NULL;
		}
		else
		{
			sem->wait = new->next;
			sem->wait->prev = new->prev;
			new->prev->next = sem->wait;
		}
		new->state = STATE_ACTIVE;
		new->next = current->next;
		new->prev = current;
		current->next->prev = new;
		current->next = new;
	}
	sti();
	checksem(sem);
	return TRUE;
}

int sem_destroy (sem_t *sem)
{
	pcb_t *h, *t;
	cli();
	if (sem->n < 0)
	{
		h = sem->wait;
		t = sem->wait->prev;
		h->prev = current;
		t->next = current->next;
		current->next->prev = t;
		current->next = h;
	}
	sti();
	return TRUE;
}

char *sstate[] = {"running ", "active  ", "sleeping", "blocked "};

void dump_ps (void)
{
	pcb_t *pcb;
	char *state;
	begin_critical_section();
	pcb = running;
	do
	{
		vtprintf(0, "%x %s %s\n", pcb->pid, pcb->cmdline, sstate[pcb->state]);
		pcb = pcb->lnext;
	} while (pcb != running);
	end_critical_section();
}
