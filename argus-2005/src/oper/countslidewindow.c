/**
  * \file countSlideWindow.c
  * \author Dong Wei and J. Zhao
  */
#include <argus.h>

/* slide window based on COUNTING */
struct count_slide
{
	// operator
	operator_t opr;
	
	// window size
	int window_size;
	
	// tail tuple pointer ID
	int tail;
	
	// full tag
	int full;
	
	// tuple pointer buffer
	tuple_t **buf;
	
	// define timber pointer
	struct timerreg_t *pTimer;
};

int count_slide_receive (struct count_slide *countSlideWindow,int type, int time, tuple_t *tup)
{
	// operator scheduled
	if(type & TUPLE_ADDED)
	{
		// nothing to do
		countSlideWindow->pTimer = timer_register(countSlideWindow->opr.schedopr,0/* now begin */,1/* every one second */,0/* till register */);
	}
	
	// time signal
	if(type & TUPLE_TIME)
	{
		// dispatch update signal
		dispatch_tuple(countSlideWindow->opr.schedopr,TUPLE_UPDATE, time, NULL);
	}
	
	// IStream tuple
	if(type & TUPLE_INS)
	{
		// tuple pointer buffer full
		if (countSlideWindow->full == 1)
		{
			// dispatch DStream tuple
			dispatch_tuple(countSlideWindow->opr.schedopr,TUPLE_DEL, time, countSlideWindow->buf[countSlideWindow->tail]);
			
			// add new tuple to buffer
			countSlideWindow->buf[countSlideWindow->tail] = tup;
			countSlideWindow->tail++;
			countSlideWindow->tail %= countSlideWindow->window_size;
		}
		// tuple pointer buffer not full
		else if (countSlideWindow->full == 0)
		{
			// add tuple to buffer
			countSlideWindow->buf[countSlideWindow->tail] = tup;
			countSlideWindow->tail++;
			countSlideWindow->tail %= countSlideWindow->window_size;
			
			if (countSlideWindow->tail == 0)
			{
				countSlideWindow->full = 1;
			}
		}
		// invalid full tag
		else
		{
			assert(0);
		}

		// dispatch IStream tuple		
		tuple_lock(tup);
		dispatch_tuple(countSlideWindow->opr.schedopr,TUPLE_INS, time, tup);
	}
	
	return 0;	
}

int count_slide_destroy (struct count_slide *countSlideWindow)
{
	// deregister timer
	timer_deregister(countSlideWindow->pTimer);
	
	// free count slide window's tuple pointer buffer
	free(countSlideWindow->buf);
	
	// free count slide window operator
	free(countSlideWindow);
	
	return 0;
}

operator_t *count_slide_create (int window_size)
{
	// define count slide window pointer
	struct count_slide *countSlideWindow = NULL;
	
	// allocate memory for count slide window
	countSlideWindow = type_alloc(struct count_slide);
	
	// set recevie and destroy function for count slide window
	countSlideWindow->opr.receive = (operator_receive_f)count_slide_receive;
	countSlideWindow->opr.destroy = (operator_destroy_f)count_slide_destroy;
	
	// set window size
	countSlideWindow->window_size = window_size;
	
	// count slide window's tail tuple ID
	countSlideWindow->tail = 0;
	
	// count slide window's full tag
	countSlideWindow->full = 0;
	
	// allocate memory to save tuple pointer
	countSlideWindow->buf = type_calloc(window_size, tuple_t *);
	
	// set timer pointer
	countSlideWindow->pTimer = NULL;
	
	// return count slide window operator
	return (operator_t *)countSlideWindow;
}

