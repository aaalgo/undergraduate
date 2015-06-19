#include <io.h>
#include <clib.h>
#include <vga.h>
#include <key.h>
#include <entry.h>
#include <page.h>
#include <gdt.h>
#include <process.h>
#include <floppy.h>
#include <ext2.h>

#define TERM_SYS 3
#define TERM_USR1 1
#define TERM_USR2 2
#define TERM_USR 0

vt_t vt[TERMNUM];
int vt_cur;
char *dmabuf = (char *)0x10000;

struct param
{
	int vt;
	char *msg;
};

void do_task1 (void);
void do_task2 (struct param *);
void blink (void);

int init ()
{
	vt_init();
	vt_show(TERM_USR);
	vt_clear(TERM_USR);
	page_init();
	vt_puts(TERM_USR, "PAGE INIT");
	gdt_init();
	vt_puts(TERM_USR, "GDT INIT");
	process_init();
	vt_puts(TERM_USR, "PROCESS INIT");
}


struct param p1 = {TERM_USR1, "TERM_USR1"};
struct param p2 = {TERM_USR2, "TERM_USR2"};

void login (void)
{
	char usr[128];
	char pass[128];
	vt_clear(0);
	vt_color(0, COLOR_CYAN);
	vtprintf(0, "MEOS");
	vt_color(0, COLOR_WHITE);
	vtprintf(0, " started.\n");
	for (;;)
	{
		vtprintf(0, "\nLogin: ");
		gets(usr);
		vtprintf(0, "Password: ");
		hgets(pass);
		if (strcmp(usr, "cybra")) goto error;
		if (strcmp(pass, "dongwei")) goto error;
		break;
error:		vtprintf(0, "Login incorrect.\n");
	}
	vtprintf(0, "\nWelcome to the exciting world of ");
	vt_color(0, COLOR_CYAN);
	vtprintf(0, "MEOS");
	vt_color(0, COLOR_WHITE);
	vtprintf(0, "!\n\n");
}

int main ()
{
	void *p;
	tss_t *tss1, *tss2;
	int i;
	key_init();
	vt_puts(TERM_USR, "KEY INIT");
	floppy_init();
	ext2_init();
	vt_puts(TERM_USR, "FLOPPY INIT"); 
	create_process(blink, NULL, "blink");
	create_process(do_task1, NULL, "shell");
	create_process(do_task2, &p1, "foo");
	create_process(do_task2, &p2, "foo");
	for(;;);
	return 0;
}

int cleanup ()
{
	vt_puts(TERM_USR, "Cleaning up...");
	return 0;
}

volatile char key = 0;

volatile int tcolor;

char tohex (char c)
{
	if (c >= 10) return c + 'A' - 10;
	return c + '0';
}

void test_floppy ()
{
	int i, j, k;
	floppy_read(2, dmabuf);
	sleep(18);
	vt_ln(TERM_USR);
	i = 0;
	for (j = 0; j < 16; j++)
	{
		for (k = 0; k < 32; k++)
		{
			vt_put(TERM_USR, tohex((dmabuf[i] >> 4) & 0x0f));
			vt_put(TERM_USR, tohex(dmabuf[i] & 0x0f));
			i++;
		}
		vt_ln(TERM_USR);
	}	
}

void shell (void)
{
	static char cmd[128];
	login();
	for (;;)
	{
		vtprintf(TERM_USR, "[meos]$");
		gets(cmd);
		if (strcmp(cmd, "about") == 0)
		{
			about();
			continue;
		}
		if (strcmp(cmd, "clear") == 0)
		{
			vt_clear(TERM_USR);
			continue;
		}
		if (strcmp(cmd, "exit") == 0)
		{
			break;
		}
		if (strcmp(cmd, "help") == 0)
		{
			help();
			continue;
		}
		if (strcmp(cmd, "super") == 0)
		{
			dump_super_block();
			continue;
		}
		if (strcmp(cmd, "ps") == 0)
		{
			dump_ps();
			continue;
		}
		vtprintf(TERM_USR, "Command not recognized.\n");
	}
}

void do_task1 (void)
{
	for (;;)
		shell();
}

void do_task2 (struct param *p)
{
	int i;
	for (i = 0; i < 65536; i++)
	{
		sleep(18);
		begin_critical_section();
		vt_color(p->vt, (i % 14) + 1);
		vt_puts(p->vt, p->msg);
		end_critical_section();
	}
}

void blink (void)
{
	int i = 0;
	for (;;)
	{
		sleep(4);
		vt_cursor(vt_cur);
		sleep(4);
		vt_cursor((vt_cur+1)%4);
	}
}

void about (void)
{
	vt_color(0, COLOR_CYAN);
	vtprintf(0, "MEOS");
	vt_color(0, COLOR_WHITE);
	vtprintf(0, " -- a prototype of a 32-bit protect mode operating system\nVersion ");
	vt_color(0, COLOR_GREEN);
	vt_put(0, 0xeb);
	vt_color(0, COLOR_WHITE);
	vtprintf(0, "\nBy ");
	vt_color(0, COLOR_RED);
	vtprintf(0, "Dong Wei\n");
	vt_color(0, COLOR_WHITE);
	vtprintf(0, "Database Laboratory\nComputer Science & Technology Department\nPeking University\n\n");
}

void help (void)
{
	vtprintf(0, "Command List:\n");
	vtprintf(0, "  about  -  print information of meos\n");
	vtprintf(0, "  clear  -  clear screen\n");
	vtprintf(0, "  help   -  print this help screen\n");
	vtprintf(0, "  ps     -  report process status\n");
}
