/**
  * \file stream.c
  * \author Dong Wei
  */
#include <argus.h>

/* static stream_t stream_head;*/
static stream_t stream[MAX_STREAM];
static int stream_table_id;

/*
static schema_fix_t stream_schema = {2,
		{{0, "id", TYPE_INT, sizeof(int), 0},
		{1, "name", TYPE_STRING32, MAX_ID_LEN, sizeof(int)}}};

int register_stream_reflect ()
{
		stream_table_id = table_register(TABLE_LINK|TABLE_SYSTEM, "@stream", (schema_t*)&stream_schema, &stream_head, NULL, 0);
		return 0;
}

static schema_fix_t schema_schema = {3,
		{{0, "id", TYPE_INT, sizeof(int), 0},
		{1, "name", TYPE_STRING32, MAX_ID_LEN, sizeof(int)},
		{2, "type", TYPE_TYPE, sizeof(void *), sizeof(int)+MAX_ID_LEN}}};
*/


/* stream operator */
int stream_destroy (operator_t *o)
{
	free(o);
	return 0;
}

int stream_receive (operator_t *o, int type, int time, tuple_t *tuple)
{
	dispatch_tuple(o->schedopr, type, time, tuple);
	return 0;
}

int stream_init ()
{
/*		stream_head.next = NULL;*/
		memset(stream, 0, sizeof stream);
		return 0;
}

int stream_cleanup ()
{
		int i;
		for (i = 0; i < MAX_STREAM; i++)
			if (stream[i].schema != NULL)
				stream_deregister(i);
		return 0;
}

int stream_register (char *name, schema_t *schema)
{
		int i;
		operator_t *opr;
		if (stream_from_name(name) != NULL) return -1;
		for (i = 0; i < MAX_STREAM; i++) if (stream[i].schema == NULL) break;
		if (i >= MAX_STREAM) return -1;
		
		opr = type_alloc(operator_t);
		opr->destroy = stream_destroy;
		opr->receive = stream_receive;
		stream[i].id = i;
		strcpy(stream[i].name, name);
		stream[i].schema = schema_dup(schema);
		stream[i].opr = sched_add_operator(opr, 0);
/*		stream[i].next = stream_head.next;
		stream_head.next = &stream[i];*/
/*		update_table(stream_table_id, &stream[i], 1);
		stream[i].table_id = table_register(TABLE_ARRAY|TABLE_STREAM, name, (schema_t*)&schema_schema, schema->field, &schema->nof, sizeof(field_t));
		row = GenRowTypeFromSchema(schema);
		assert(row != NULL);
		InsertTable(0, name, row);*/
		return i;
}

int stream_deregister (int id)
{
		assert(stream[id].schema != NULL);
/*		t = stream_head.next;*/
		info("deregister stream...\n");
/*		update_table(stream_table_id, &stream[id], -1);
		table_deregister(stream[id].schema->field);*/
		sched_remove_operator(stream[id].opr);
		free(stream[id].schema);
		stream[id].schema = NULL;
/*		r = &stream_head;
		t = stream_head.next;
		while (t != NULL)
		{
				if (t == &stream[id])
				{
						r->next = t->next;
						break;
				}
				r = t;
				t = r->next;
		}*/
		return 0;
}

stream_t *stream_from_id (int id)
{
		assert(id >= 0 && id < MAX_STREAM);
		if (stream[id].schema == NULL) return NULL;
		return &stream[id];
}

stream_t *stream_from_name (char *name)
{
		int i;
		for (i = 0; i < MAX_STREAM; i++)
				if (stream[i].schema != NULL)
						if (strcmp(stream[i].name, name) == 0) return &stream[i];
		return NULL;
}

int stream_get_id (char *name)
{
		int i;
		for (i = 0; i < MAX_STREAM; i++)
				if (stream[i].schema != NULL)
						if (strcmp(stream[i].name, name) == 0) return i;
		return -1;
}

