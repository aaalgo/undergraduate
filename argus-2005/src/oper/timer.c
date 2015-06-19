#include <argus.h>
#include <timer.h>

DECLARE_THREAD(timer_thread);
DECLARE_MUTEX(timer_mutex);

int timer_acc;
struct wakereg_t *wake_head;
static timer_running;

/* To send a timer signal to an operator, use the following statement:
	send_tuple_async(opr, TUPLE_TIME, NULL);
*/

void timer_worker (void *p)
{
	//printf("Timer start\n");
	timer_running = 1;
	while (wake_head)
	{
		struct timerreg_t *timer_p;
		struct wakereg_t *temp;
		int now=TIME();
		if (wake_head->wake_time>now)	// if it's later, send tuple at once, otherwise sleep
			SLEEP((wake_head->wake_time-now));
		
		MUTEX_LOCK(timer_mutex);
		
		temp=wake_head;
		timer_p=wake_head->timer_p;
		if (timer_p->count==-1) {	// disregistered
			wake_head=wake_head->next;
			free(temp);
		}
		else {
			send_tuple_async(timer_p->opr, TUPLE_TIME, now, NULL, 1);
			//printf("%d %d %d %d\n", TIME(), timer_p->index, timer_p->period, timer_p->count);////
			if (timer_p->count==1) {	// timer is ending
				wake_head=wake_head->next;
				free(temp);
			}
			else {
				if (timer_p->count>0) timer_p->count--;
				wake_head->wake_time+=timer_p->period;
			
				for (; temp->next && temp->next->wake_time<wake_head->wake_time; temp=temp->next);
				if (temp!=wake_head) {
					struct wakereg_t *temp2=wake_head;  wake_head=wake_head->next;
					temp2->next=temp->next;  temp->next=temp2;
				}
			}
		}
		
		MUTEX_UNLOCK(timer_mutex);
	}
	//printf("Timer end\n");
	timer_running = 0;
	THREAD_EXIT(0);
}

int timer_init (void)
{
	timer_acc=0;
	wake_head=NULL;
	timer_running = 0;
	MUTEX_CREATE(timer_mutex);
	return 0;
}

int timer_cleanup (void)
{
	struct wakereg_t *wake, *t2;
	if (timer_running) THREAD_DESTROY(timer_thread);
	MUTEX_DESTROY(timer_mutex);
	wake = wake_head;
	while (wake != NULL)
	{
		t2 = wake;
		wake = wake->next;
		free(t2->timer_p);
		free(t2);
	}
	return 0;
}

struct timerreg_t *timer_register (schedopr_t *opr, int start, int period, int count)
{
	int now;
	struct timerreg_t *timer_p;
	struct wakereg_t *wake_p;

	MUTEX_LOCK(timer_mutex);		

	timer_p = type_alloc(struct timerreg_t);
	timer_p->opr=opr;  /* timer_p->index=timer_acc++;*/
	timer_p->period=period;  timer_p->count=count;
	//printf("Register %d ", timer_p->index);////
	
	wake_p=type_alloc(struct wakereg_t);
	wake_p->timer_p=timer_p;
	now=TIME();
	if (start==0)
		wake_p->wake_time=now+period;
	else if (start<now)
		wake_p->wake_time=now;
	else
		wake_p->wake_time=start;
	//printf("%d\n", wake_p->wake_time);////
	
	if (!wake_head || wake_p->wake_time<wake_head->wake_time) {
		wake_p->next=wake_head;  wake_head=wake_p;
		if (timer_running) THREAD_DESTROY(timer_thread);
		//THREAD_DESTROY(timer_thread);	// destroy it when it's sleeping!
		THREAD_CREATE(timer_thread, timer_worker, NULL);
	}
	else {
		struct wakereg_t *temp;
		int i;
		for (i=0, temp=wake_head; temp->next && temp->next->wake_time<wake_p->wake_time; temp=temp->next, i++);
		wake_p->next=temp->next;  temp->next=wake_p;
	}

	MUTEX_UNLOCK(timer_mutex);
	return timer_p;
}

int timer_deregister (struct timerreg_t *timer_p)
{
	MUTEX_LOCK(timer_mutex);
	timer_p->count=-1;
	//printf("Deregister %d\n", timer_p->index);////
	MUTEX_UNLOCK(timer_mutex);
	return 0;
}
/*
int main() {
	struct timerreg_t *timer_p;

	timer_init();
	timer_register(NULL, 0, 3, 5);
	timer_register(NULL, 0, 5, 5);
	timer_p=timer_register(NULL, 0, 2, 5);
	SLEEP(10000);
	timer_deregister(timer_p);
	SLEEP(20000);
	timer_cleanup();
	return 0;
}*/
