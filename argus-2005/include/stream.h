/**
  * \file stream.h
  * \author Dong Wei
  */

#ifndef __STREAM_H__
#define __STREAM_H__

typedef struct __stream stream_t;
struct __stream {
/*		stream_t *next;*/
		int id;
		char name[MAX_ID_LEN];
		schema_t *schema;
		schedopr_t *opr;
/*		int table_id;*/
};

int stream_init ();
int stream_cleanup ();
int stream_register (char *name, schema_t *schema);
int stream_deregister (int id);

stream_t *stream_from_id (int id);
stream_t *stream_from_name (char *name);
int stream_get_id (char *name);

#endif

