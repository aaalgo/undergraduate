/* filename: aggre.h
   by Dong Wei */

#ifndef __ARGUS_AGGRE__
#define __ARGUS_AGGRE__

/* an aggregate function is defined as 4 sub-functions - initilize, update,
 * value and cleanup.
 */
typedef void *(* aggre_init_f) (void); /* return the handle */

/* flag == TUPLE_INS insert
   flag == TUPLE_DEL delete
 */
typedef void (* aggre_update_f) (void *handle, void *data, int flag);

/* Put the current value to *data */
typedef void (* aggre_value_f) (void *handle, void *data);

/* terminate aggregation, free resources */
typedef void (* aggre_cleanup_f) (void *);

/* Two aggregate functions can have the same name,
   but must have distinct value of the tuple
   (itype, name). */

typedef struct
{
	type_t* itype;	/* type of input */
	type_t* otype;	/* type of output */
	aggre_init_f init;
	aggre_update_f update;
	aggre_value_f value;
	aggre_cleanup_f cleanup;
	char name[MAX_ID_LEN];
} aggre_t;


/* return index of the aggregate in the array laggregate */
aggre_t *aggre_load (char *name, type_t *itype);
int is_aggre (char *name);
#endif
