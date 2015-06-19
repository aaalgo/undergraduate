#ifndef __ARGUS_CLIENT__
#define __ARGUS_CLIENT__

/* tuple */

#define TUPLE_INS	1
#define TUPLE_DEL	2
#define TUPLE_TIME 	4
#define TUPLE_UPDATE	8
#define TUPLE_CLEAN 	16
#define TUPLE_ADDED	32
#define TUPLE_REPLACE 64

extern int tuple_id;

/** Tuple type. */
typedef struct
{
		int id;
		/** Time stamp. */
/*		struct timeval time;*/
		int time;
		/** Size/Pointer to data. */
		int lock;
		/** Data size */
		size_t size;
		/* the tuple object does not own the schema object,
		 * so when freeing the tuple, the schema should not be freed */
		schema_t *schema;
		char data[1];
} tuple_t;

#endif