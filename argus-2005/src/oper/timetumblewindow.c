/**
  * \file timeTumble_window.c
  * \author J.Zhao 2004/09/09 
  */
#include <argus.h>

/* tumble window based on time */
struct time_tumble
{
	// operator
	operator_t opr;

	// window size [second]
	int window_size;

	// begin time [second]
	int begin_time;

	// begin tag [1 == true, 0 == false]
	int begin;

	// timer pointer
	struct timerreg_t *pTimer;
};

int time_tumble_receive(struct time_tumble *time_op,int type, int time, tuple_t *tup)
{

	// operator has been scheduled
	if(type & TUPLE_ADDED)
	{
		if(time_op->begin == 0)
		{
			// begin to generate time signal from "begin_time"
			// generate one time signal every "window_size" second
			// generate the time signal until deregister this operator
			time_op->pTimer = timer_register(time_op->opr.schedopr,time_op->begin_time,time_op->window_size,0);
		}
		// invalid value
		else
		{
			assert(0);
		}
	}
	
	// new data tuple arrived
	if(type & TUPLE_INS)
	{
		// window running
		if(time_op->begin == 1)
		{
			// generate + stream tuple
			dispatch_tuple(time_op->opr.schedopr,TUPLE_INS, time, tup);
		}
		// window not begin
		else if(time_op->begin == 0)
		{
			// ignore tuple
			tuple_unlock(tup);
		}
		// invalid value
		else
		{
			assert(0);
		}
	}
	
	// time signal arrived
	if(type & TUPLE_TIME)
	{
		// window is running, dispatch update and clean signal
		if(time_op->begin == 1)
		{
			// dispatch clean signal
			dispatch_tuple(time_op->opr.schedopr,TUPLE_UPDATE, time, NULL);
			dispatch_tuple(time_op->opr.schedopr,TUPLE_CLEAN, time, NULL);
		}
		// receive the first time signal, window begin
		else if(time_op->begin == 0)
		{
			time_op->begin = 1;
		}
		// invalid value
		else
		{
			assert(0);
		}
	}
	
	return 0;	
}

int time_tumble_destroy(struct time_tumble *time_op)
{
	// deregister operator's timer
	timer_deregister(time_op->pTimer);

	// free operator
	free(time_op);

	return 0;
}

operator_t *time_tumble_create(int window_size/* second */,int begin_time/* second */)
{
	// define time tumble window operator pointer
	struct time_tumble *timeTumbleWindow = NULL;

	// allocate memory for time tumble window operator
	timeTumbleWindow = type_alloc(struct time_tumble);

	// set receive function and destroy function for time tumble window operator
	timeTumbleWindow->opr.receive = (operator_receive_f)time_tumble_receive;
	timeTumbleWindow->opr.destroy = (operator_destroy_f)time_tumble_destroy;

	// set window size and begin time for time tumble window
	timeTumbleWindow->window_size = window_size ;
	timeTumbleWindow->begin_time  = 1  ;

	// set begin tag = 0
	timeTumbleWindow->begin = 0;

	// set timer pointer NULL
	timeTumbleWindow->pTimer = NULL;

	// return the operator
	return (operator_t *)timeTumbleWindow;
}