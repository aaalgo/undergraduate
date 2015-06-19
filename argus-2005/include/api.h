#ifndef __ARGUS_API__
#define __ARGUS_API__

typedef struct __argus ARGUS;

/* connect to the server,
   in the embedded version of argus, the server may be in the save process,
   but the interface are the same */
ARGUS *argus_connect (char *server);
/* All the following functions used ARGUS * as the first parameter. */

/*disconnect from server */
int argus_shutdown (ARGUS *);

/* The following functions are used in the 'writer' client */

/* Return the id of the stream */
int argus_create_stream (ARGUS *, char *name, schema_t *schema);

/* Delete a stream */
int argus_drop_stream (ARGUS *, int id);

/* insert a tuple into the stream */
int argus_insert_tuple (ARGUS *,int id, int type, void *data);


/* The following functions are used in the 'reader' client */

/* The synchronous version */
/* register a query, return the id */
/* int argus_create_query (ARGUS *, char *sql); */

/* pointer to tuple */
/* int argus_read_tuple (ARGUS *, int id, tuple_t **tuple); */

/* int argus_drop_query (ARGUS *, int id);*/


/* The async version of api */

/* callback functions */
typedef int (*argus_callback_f) (void *, int msg, int int_p, void *p_p);
/* on tuple arriving */

int argus_exec_sql (ARGUS *, char *sql,
			argus_callback_f callback,
			void *);
int argus_drop_sql (ARGUS *, int id);

/* Used by system */
extern argus_callback_f __callback;
extern void *__callback_param;

#define ARGUS_SUCCESS		0
#define ARGUS_REGISTERED	1
#define ARGUS_TUPLE		2
#define ARGUS_DEREGISTERED	3
#define ARGUS_ERROR		4
#define ARGUS_ERROR_COMPILE		100
#define ARGUS_ERROR_REGISTER	101
#endif
