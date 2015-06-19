/**
  * \file libtype.h
  *	\author Dong Wei
  * \brief A library aids processing data of different types and functions on them.
  */

#ifndef __LIB_TYPE__
#define __LIB_TYPE__

typedef struct
{
	char nul;
	char second;
	char minute;
	char hour;
	char day;
	char month;
	unsigned short year;
} datetime_t;

/* A type in the system is identified by a integer ID, there is a type_t
   struct coresponding to each type, which give information on name,
   internal size, etc about the type.

   A special type "void" is always avaible, with ID = 0. */
typedef struct
{
		int id;
		char name[MAX_ID_LEN];
		/* internal size, fixed */
		size_t size;
		/* conver from/to string */
		/* return 0 if successfull */
		/* if readsize != NULL, then number of characters read is stored in it */
		int (*from_string) (void *, char *, int *readsize);
		/* return byte translated, including the trailing 0 */
		/* If buffer insufficient, then the size needed is returned */
		int (*to_string) (void *, char *, int bufsize);
		/* serialization functions */
		/* return byte translated, including the trailing 0 */
		/* if buffer insufficient, then the size needed is returned */
		int (*encode) (void *, void *, int bufsize);
		int (*decode) (void *, void *);
		/* copy */
		int (*copy) (void * /*to*/, void * /*from*/);
		/* comp */
		int (*comp) (void *, void *);
		/* free */
		int (*free) (void *);
		/* hash */
		unsigned (*hash) (void *);
} type_t;

extern type_t type_void;

/* type of general function
   a function can have at most 2 parameters */
typedef void (*func_f) (void *result,...);

typedef struct
{
		int id;
		char name[MAX_ID_LEN];
#ifdef LIBTYPE_REFLECT 
		char *tresult;
		char *tparam1;
		char *tparam2;
#endif
		/* pointer to function */
		func_f func;
		/* type of result and 2 parameters */
		type_t *result;
		type_t *param1;
		type_t *param2;
} func_t;

/* initialize/Finalize the type library */
int type_init (void);
int type_cleanup (void);

/* register type/function */
int type_register (type_t *type);
int func_register (func_t *func);

type_t *type_load (char *);
int type_load_id (char *);
type_t *type_from_id (int id);
/* load the function of given name and parameter types */
func_t *func_load (char *, type_t *param1, type_t *param2);
int func_load_id (char *, type_t *param1, type_t *param2);
func_t *func_from_id (int id);

/* load libraries in config file */
/*
int type_load_config (char *);
*/
extern type_t type_void;
extern type_t type_bool;
extern type_t type_char;
extern type_t type_int;
extern type_t type_float;
extern type_t type_string;
extern type_t type_ip;
extern type_t type_datetime;
#define TYPE_NULL (&type_void)
#define TYPE_VOID (&type_void)
#define TYPE_BOOL (&type_bool)
#define TYPE_CHAR (&type_char)
#define TYPE_INT (&type_int)
#define TYPE_FLOAT (&type_float)
#define TYPE_STRING (&type_string)
#define TYPE_IP (&type_ip)
#define TYPE_DATETIME (&type_datetime)

int register_internal_types(void);
#endif
