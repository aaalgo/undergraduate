/**
  * \file operTimeSlidewindow.c
  * \author J.Zhao 2004/09/09 
  */
#include <argus.h>

#define SLIDELISTSIZE 64

/* tuple pointer list node */
struct tupleList_node
{
	tuple_t *pTuple[SLIDELISTSIZE];
	int time[SLIDELISTSIZE];

	struct tupleList_node *next;
};

/* slide window based on time */
struct time_slide
{
	// operator
	operator_t opr;

	// window size [second]
	int window_size;

	// update frequency [second]
	int update_freq;

	// define List pointer
	struct tupleList_node *head;
	struct tupleList_node *tail;

	// define List node position
	int headPos;
	int tailPos;

	// define tuple number
	int tuple_num;

	// define timber pointer
	struct timerreg_t *pTimer;
};

int time_slide_receive(struct time_slide *time_op,int type, int time, tuple_t *tup)
{
	struct tupleList_node *pTemp = NULL;

	int currentTime = 0;

	// remind timer to generate signal if the operator has been scheduled
	if(type & TUPLE_ADDED)
	{
		// begin to generate the time signal immediately
		// generate one time signal every "time_op->update_freq" second
		// generate the time signal until deregister this operator
		time_op->pTimer = timer_register(time_op->opr.schedopr,0,time_op->update_freq,0);
	}
	
	// new data tuple arrived
	if(type & TUPLE_INS)
	{
		// save tuple
		
		time_op->tail->pTuple[time_op->tailPos] = tup;
		time_op->tail->time[time_op->tailPos] = time;

		time_op->tailPos++;

		if(time_op->tailPos == SLIDELISTSIZE)
		{
			pTemp = type_alloc(struct tupleList_node);

			time_op->tail->next = pTemp;

			time_op->tail = pTemp;
			
			pTemp->next = NULL;

			time_op->tailPos = 0;
		}

		time_op->tuple_num++;

		// generate + stream tuple
		tuple_lock(tup);
		dispatch_tuple(time_op->opr.schedopr,TUPLE_INS, time, tup);
	}
	
	// time signal arrived
	if(type & TUPLE_TIME)
	{
	/*	currentTime = TIME();*/
		currentTime = time;
		
		currentTime -= time_op->window_size;
		
		while(time_op->tuple_num > 0)
		{
			if(time_op->head->time[time_op->headPos] < currentTime)
			{
				// dispatch - stream tuple
				dispatch_tuple(time_op->opr.schedopr,TUPLE_DEL, currentTime, time_op->head->pTuple[time_op->headPos]);

				time_op->tuple_num--;

				time_op->headPos++;

				if(time_op->headPos == SLIDELISTSIZE)
				{
					time_op->headPos = 0;

					pTemp = time_op->head;

					time_op->head = time_op->head->next;

					free(pTemp);
				}
			}
			else
			{
				break;
			}
		}
		
		// generate update signal
		dispatch_tuple(time_op->opr.schedopr,TUPLE_UPDATE, time, NULL);
	}
	
	return 0;	
}

int time_slide_destroy(struct time_slide *time_op)
{
	struct tupleList_node *pTemp = NULL;

	// deregister operator's timer
	timer_deregister(time_op->pTimer);

	// free tuple list 
	while(time_op->head != time_op->tail)
	{
		pTemp = time_op->head;

		time_op->head = time_op->head->next;

		free(pTemp);
	}

	free(time_op->head);

	// free operator
	free(time_op);

	return 0;
}

operator_t *time_slide_create(int window_size/* second */,int update_freq/* second */)
{
	// define time slide window operator pointer
	struct time_slide *timeSlideWindow = NULL;

	// allocate memory for time slide window operator
	timeSlideWindow = type_alloc(struct time_slide);

	// set receive function and destroy function for time slide window operator
	timeSlideWindow->opr.receive = (operator_receive_f)time_slide_receive;
	timeSlideWindow->opr.destroy = (operator_destroy_f)time_slide_destroy;

	// set window size and update frequency for time slide window
	timeSlideWindow->window_size = window_size ;
	timeSlideWindow->update_freq = update_freq ;

	// allocate memory for tuple pointer list
	timeSlideWindow->head = type_alloc(struct tupleList_node);
	timeSlideWindow->tail = timeSlideWindow->head;
	timeSlideWindow->head->next = NULL;

	// initialize list position
	timeSlideWindow->headPos = 0;
	timeSlideWindow->tailPos = 0;

	// initialize tuple number
	timeSlideWindow->tuple_num = 0;

	// initialize timer pointer
	timeSlideWindow->pTimer = NULL;

	// return the operator
	return (operator_t *)timeSlideWindow;
}