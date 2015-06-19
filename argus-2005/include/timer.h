#ifndef __ARGUS_TIMER__
#define __ARGUS_TIMER__

struct timerreg_t {	// list of registered timer
	schedopr_t *opr;
	int period;
	int count;	// 0 -- forever, 1 -- ending
	struct timerreg_t *next;
};



struct wakereg_t {	// schedule of waking
	int wake_time;
	struct timerreg_t *timer_p;
	struct wakereg_t *next;
};

int timer_init (void);

int timer_cleanup (void);

struct timerreg_t *timer_register (schedopr_t *opr, int start, int period, int count);
/* To send a timer signal to an operator, use the following statement:
	send_tuple_async(opr, TUPLE_TIME, NULL);
*/

int timer_deregister (struct timerreg_t *opr);


#endif

