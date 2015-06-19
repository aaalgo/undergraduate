/**
  * \file schedule.h
  * \author Dong Wei
  * \brief Header file for the scheduler.
  */

#ifndef __ARGUS_SCHEDULE__
#define __ARGUS_SCHEDULE__

/* tuple */

#define TUPLE_INS		1
#define TUPLE_DEL		2
#define TUPLE_TIME 		4
#define TUPLE_UPDATE	8
#define TUPLE_CLEAN 	16
#define TUPLE_ADDED		32
#define TUPLE_REPLACE	64
#define TUPLE_SCHEDULE 128

extern int tuple_id;

/** Tuple type. */
typedef struct
{
		int id;
		/** Time stamp. */
/*		struct timeval time;*/
/*		int time;*/
		/** Size/Pointer to data. */
		int lock;
		/** Data size */
		size_t size;
		/* the tuple object does not own the schema object,
		 * so when freeing the tuple, the schema should not be freed */
		schema_t *schema;
		char data[1];
} tuple_t;

static __inline void tuple_lock (tuple_t *tup)
{		
		tup->lock++;
}

static __inline void tuple_unlock (tuple_t *tup)
{
		tup->lock--;
		if (tup->lock == 0)
		{
			int i;
			field_t *fld;
#ifdef GET_SYSINFO
			info_mem_used -= tup->size;
			info_tuple_exist--;
#endif
			for (i = 0; i < tup->schema->nof; i++)
			{
				type_t *type;
				fld = &tup->schema->field[i];
				type = fld->type;
				if (type->free != NULL)
				{
					type->free(tup->data + fld->offset); 
				}
			}
			free(tup);
		}
}

static __inline tuple_t *tuple_alloc (int data_size, schema_t *schema)
{
		tuple_t *t = (tuple_t *)xmalloc(sizeof(tuple_t) + data_size);
		t->id = tuple_id++;
		t->lock = 1;
		t->size = data_size;
		t->schema = schema;
/*		t->time = TIME();*/
#ifdef GET_SYSINFO
		info_mem_used += data_size;
		info_tuple_exist++;
#endif
		return t;
}


typedef struct __operator operator_t;
/** Operator destructor. */
typedef int (*operator_destroy_f) (operator_t *operator);

typedef struct __buffer buffer_t;
/** Operator receive callback function type. */
typedef int (*operator_receive_f) (operator_t *operator, int type, int time, tuple_t *tuple);

typedef struct __schedopr schedopr_t;
	
/** Details of operator structure. */
struct __operator
{
	/** Destructor. */
	operator_destroy_f destroy;
	/** Receiving callback. */
	operator_receive_f receive;
	/** schedopr */
	schedopr_t *schedopr;
	char data[1];
};

/* scheduler */

/** Initialize the scheduler. */
extern int sched_init (void);

/** Finalize the scheduler. */
extern int sched_cleanup (void);

/** Start the scheduler. */
int sched_start (void);

/** Stop the scheduler. */
int sched_stop (void);

extern DECLARE_MUTEX(sched_mutex);
/** Suspend the scheduler. */
static __inline void sched_suspend (void)
{
	MUTEX_LOCK(sched_mutex);
}

/** Resume the scheduler. */
static __inline void sched_resume (void)
{
	MUTEX_UNLOCK(sched_mutex);
}


/** Add an operator. */
schedopr_t* sched_add_operator (operator_t *, int priority);

/** Remove an operator. */
int sched_remove_operator (schedopr_t *);

/** Add a destination to an operator. */
int sched_add_dest (schedopr_t *src, schedopr_t *dest);

/** Remove a destination from an operator. */
int sched_remove_dest (schedopr_t *src, schedopr_t *dest);

/** Dispatch an operator's packet to its destinations. */
int dispatch_tuple (schedopr_t *src, int type, int time, tuple_t *);

/** Send a tuple to an operator. */
int send_tuple (schedopr_t *dest, int type, int time, tuple_t *, int resched);

/* send a tuple to an operator, used in the receive function of an operator */
int sched_flush_tuple (schedopr_t *dest);

/* send a tuple to an operator, used in anyplace other than the receive function of an operator */
int send_tuple_async (schedopr_t *src, int type, int time, tuple_t *, int resched);

#endif

