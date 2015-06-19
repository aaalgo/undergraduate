/**
  * \file countTumbleWindow.c
  * \author Dong Wei and J. Zhao
  */
#include <argus.h>

/* tumble window based on COUNTING */

struct count_tumble
{
	// operator
	operator_t opr;
	
	// window size
	int window_size;
	
	// current window size
	int tupleNum;
};

int count_tumble_receive (struct count_tumble *countTumbleWindow, int type, int time, tuple_t *tuple)
{
	if(type & TUPLE_ADDED)
	{
		// nothing to do
	}
	// IStream tuple
	if(type & TUPLE_INS)
	{
		// dispatch IStream tuple
		dispatch_tuple(countTumbleWindow->opr.schedopr,TUPLE_INS, time, tuple);
		
		// update window tuple number
		countTumbleWindow->tupleNum++;
		
		// if window full, dispatch update and clean signal tuple
		if (countTumbleWindow->tupleNum == countTumbleWindow->window_size)
		{
			dispatch_tuple(countTumbleWindow->opr.schedopr,TUPLE_UPDATE, time, NULL);
			dispatch_tuple(countTumbleWindow->opr.schedopr,TUPLE_CLEAN, time, NULL);
			countTumbleWindow->tupleNum = 0;
		}
	}

	return 0;
}

int count_tumble_destroy (struct count_tumble *countTumbleWindow)
{
	// free window operator
	free(countTumbleWindow);
	
	return 0;
}

operator_t *count_tumble_create (int window_size)
{
	// define window operator
	struct count_tumble *countTumbleWindow = NULL;
	
	// allocate memory for operator
	countTumbleWindow = type_alloc(struct count_tumble);
	
	// set operator receive and operator destory function pointer
	countTumbleWindow->opr.receive = (operator_receive_f)count_tumble_receive;
	countTumbleWindow->opr.destroy = (operator_destroy_f)count_tumble_destroy;
	
	// set operator window size 
	countTumbleWindow->window_size = window_size;
	
	// set current tuple number = 0
	countTumbleWindow->tupleNum = 0;
	
	// return operator pointer
	return (operator_t *)countTumbleWindow;
}