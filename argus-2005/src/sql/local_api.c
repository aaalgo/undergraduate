#include <argus.h>

#define ARGUS_MAGIC ((ARGUS *)0xABCDDCBA)
static int argus_running = 0;

argus_callback_f __callback;
void * __callback_param;

ARGUS *argus_connect (char *server)
{
	/* do initializing jobs */
	if (argus_running) return 0;
	type_init();
	register_internal_types();
	timer_init();
	sched_init();
	sched_start();
	stream_init();
	argus_running = 1;
	return ARGUS_MAGIC;
}

int argus_shutdown (ARGUS *h)
{
	assert(h == ARGUS_MAGIC);
	query_cleanup();
	stream_cleanup();
	sched_stop();
	sched_cleanup();
	timer_cleanup();
	type_cleanup();	
	return 0;
}

int argus_create_stream (ARGUS *h, char *name, schema_t *schema)
{
	assert(h == ARGUS_MAGIC);
	return stream_register(name, schema);
}

int argus_drop_stream (ARGUS *h, int id)
{
	assert(h == ARGUS_MAGIC);
	return stream_deregister(id);
}

int argus_insert_tuple (ARGUS *h, int id, int type, void *data)
{
	stream_t *stream;
	tuple_t *tuple;
	int size, i;
	assert(h == ARGUS_MAGIC);
	stream = stream_from_id(id);
	assert(stream != NULL);
	tuple = NULL;
	if (data != NULL)
	{
		schema_t *schema;
		field_t *field;
		schema = stream->schema;
		size = schema_data_size(schema);
		tuple = tuple_alloc(size, schema);
		memcpy(tuple->data, data, size);
		field = schema->field;
		for (i = 0; i < schema->nof; i++)
		{
			if (field->type->copy != NULL)
			{
				field->type->copy((char *)(tuple->data) + field->offset,
						(char *)data + field->offset);
			}
			field++;
		}
	}
	send_tuple_async(stream->opr, type, TIME(), tuple, 1);
	return 0;
}

int argus_exec_sql (ARGUS *h, char *sql,
		argus_callback_f callback,
		void *param)
{
	int id;
	assert(h == ARGUS_MAGIC);
	__callback = callback;
	__callback_param = param;
	sql_compile(sql);
	if (!sql_ok)
	{
		callback(param, ARGUS_ERROR, ARGUS_ERROR_COMPILE, NULL);
		return 0;
	}
	sql_dump();
	id = register_query();
	if (id < 0)
	{
		callback(param, ARGUS_ERROR, ARGUS_ERROR_REGISTER, NULL);
	}
	else
	{
		schema_t *schema;
		schema = query.joined_schema;
		if (query.grouped_schema != NULL) schema = query.grouped_schema;
		if (query.mapped_schema != NULL) schema = query.mapped_schema;
		callback(param, ARGUS_REGISTERED, id, schema);
	}
	sql_cleanup_query();
	return 0;
}

int argus_drop_sql (ARGUS *h, int id)
{
	assert(h == ARGUS_MAGIC);
	deregister_query(id);
	return 0;	
}

