#include <stdlib.h>
#include <config.h>
#include <cmnhdr.h>
#include <osdept.h>
#include <libtype.h>
#include <schema.h>
#include <udp.h>
#include <service.h>
#include <api.h>
#include <llist.h>
#include <client.h>


extern int schema_encode (void *sch, void *out, int bufsize);
extern int schema_decode (void *sch, void *in);
extern int tuple_encode (schema_t *schema, void *tuple, void *buffer, int buf_size);
extern int tuple_decode (schema_t *schema, void *tuple, void *buffer);


static lnode_t conn = {NULL};

struct __argus
{
	lnode_t link;
	struct sockaddr_in addr;
	schema_t *schema;
	argus_callback_f callback;
	void *param;
	DECLARE_SEMAPHORE(lock);
	int ret;
};

int reply_stream_created (void *nul, package_t *package)
{
	int ret;
	ARGUS *argus = *(ARGUS **)package->data;
	ret = *(int *)(package->data + sizeof(ARGUS *));
	argus->ret = ret;
	SEMAPHORE_POST(argus->lock);
	return 0;
}

int reply_stream_dropped (void *nul, package_t *package)
{
	int ret;
	ARGUS *argus = *(ARGUS **)package->data;
	ret = *(int *)(package->data + sizeof(ARGUS *));
	argus->ret = ret;
	SEMAPHORE_POST(argus->lock);
	return 0;
}

int reply_query_created (void *nul, package_t *package)
{
	int id;
	schema_t *schema = NULL;
	ARGUS *argus = *(ARGUS **)package->data;
	id = *(int *)(package->data + sizeof(ARGUS *));
	if (id >= 0)
	{
		schema_decode(&schema, package->data + 2 * sizeof(int));
	}
	argus->schema = schema;
	argus->callback(argus->param, ARGUS_REGISTERED, id, schema);
	return 0;
}

int reply_query_dropped (void *nul, package_t *package)
{
	ARGUS *argus = *(ARGUS **)package->data;
	argus->callback(argus->param, ARGUS_DEREGISTERED, 0, NULL);
	return 0;
}

int reply_send_tuple (void *nul, package_t *package)
{
	char *p = package->data;
	int id;
	int type;
	int size;
	int tsize;
	tuple_t *tuple;
	ARGUS *argus = *(ARGUS **)p;
	p += sizeof(ARGUS *);
	id = *(int*)p;
	p += sizeof(int);
	type = *(int *)p;
	p += sizeof(int);
	size = *(int *)p;
	p += sizeof(int);
	if (size > 0)
	{
		if (argus->schema == NULL) return 0;
		tsize = schema_data_size(argus->schema);
		tuple = (tuple_t *)xmalloc(tsize + sizeof(tuple_t));
		tuple->id = id;
		tuple->schema = argus->schema;
		tuple->size = tsize;
		tuple->time = 0;
		tuple_decode(argus->schema, tuple->data, p);
	}
	else tuple = NULL;
	argus->callback(argus->param, ARGUS_TUPLE, type, tuple);
	if (tuple != NULL) free(tuple);
	return 0;
}

int reply_error (void *nul, package_t *package)
{
	int id;
	ARGUS *argus = *(ARGUS **)package->data;
	id = *(int *)(package->data + sizeof(ARGUS *));
	argus->callback(argus->param, ARGUS_ERROR, id, 0);
	return 0;
}

ARGUS *argus_connect (char *server)
{
	ARGUS *ret;
	if (llist_empty(conn))
	{
		type_init();
		register_internal_types();
		udp_init();
		udp_register(ARGUS_REPLY_STREAM_CREATED, reply_stream_created, NULL);
		udp_register(ARGUS_REPLY_STREAM_DROPPED, reply_stream_dropped, NULL);
		udp_register(ARGUS_REPLY_QUERY_CREATED, reply_query_created, NULL);
		udp_register(ARGUS_REPLY_QUERY_DROPPED, reply_query_dropped, NULL);
		udp_register(ARGUS_REPLY_SEND_TUPLE, reply_send_tuple, NULL);
		udp_register(ARGUS_REPLY_ERROR, reply_error, NULL);
		udp_start(0);
	}
	ret = type_alloc(ARGUS);
	memset(ret, 0, sizeof (ARGUS));
	ret->addr.sin_family = AF_INET;
	ret->addr.sin_addr.s_addr = inet_addr(server);
	ret->addr.sin_port = htons(ARGUS_PORT);
	ret->link.next = conn.next;
	ret->callback = NULL;
	ret->param = NULL;
	ret->schema = NULL;
	ret->ret = 0;
	ret->link = conn;
	SEMAPHORE_CREATE(ret->lock, 1);
	conn.next = (lnode_t *)ret;
	return ret;
}

int argus_shutdown (ARGUS *argus)
{
	ARGUS *temp;
	temp = (ARGUS *)&conn;
	while (temp->link.next != NULL)
	{
		if ((ARGUS *)(temp->link.next) == argus) break;
		temp = (ARGUS *)(temp->link.next);
	}
	if (temp->link.next == NULL) return 0;
	temp->link.next = argus->link.next;
	if (argus->schema != NULL) free(argus->schema);
	SEMAPHORE_DESTROY(argus->lock);
	free(argus);
	if (llist_empty(conn))
	{
		udp_stop();
		udp_cleanup();
	}
	return 0;
}

int argus_create_stream (ARGUS *argus, char *name, schema_t *schema)
{
	char buf[1024];
	char *p;
	unsigned short len, ret, left;
	package_t *out;
	p = buf;
	*(ARGUS **)p = argus;
	p += sizeof(ARGUS *);
	len = strlen(name) + 1;
	*(unsigned short *)p = len;
	p += sizeof (unsigned short);
	memcpy(p, name, len);
	p += len;
	left = 1024 - len;
	ret = schema_encode(&schema, p, left);
	if (ret > left) return -1;	
	out = udp_alloc_package(argus->addr, ARGUS_SERVICE_CREATE_STREAM, ret + p - buf, buf);
	udp_send(out);
	udp_free_package(out);
	argus->schema = schema_dup(schema);
	SEMAPHORE_WAIT(argus->lock);
	return argus->ret;
}

int argus_drop_stream (ARGUS *argus, int id)
{
	struct request {
		ARGUS *tag;
		int id;
	} request;
	package_t *out;
	request.tag = argus;
	request.id = id;
	out = udp_alloc_package(argus->addr, ARGUS_SERVICE_DROP_STREAM, sizeof(struct request), &request);
	udp_send(out);
	udp_free_package(out);
	SEMAPHORE_WAIT(argus->lock);
	return argus->ret;
}

int argus_insert_tuple (ARGUS *argus,int id, int type, void *data)
{
	struct request
	{
		int id;
		int type;
		int size;
		char buf[1024];
	} request;
	package_t *out;
	int ret;
	request.id = id;
	request.type = type;
	ret = tuple_encode(argus->schema, data, request.buf, 1024);
	if (ret > 1024) return 0;
	request.size = ret;
	out = udp_alloc_package(argus->addr, ARGUS_SERVICE_SEND_TUPLE, ret + sizeof(int) * 3, &request);
	udp_send(out);
	udp_free_package(out);
	return 0;
}

int argus_exec_sql (ARGUS *argus, char *sql,
			argus_callback_f callback,
			void *param)
{
	char buf[1024];
	char *p = buf;
	unsigned short len;
	package_t *out;
	argus->callback = callback;
	argus->param = param;
	*(ARGUS **)p = argus;
	p += sizeof(ARGUS *);
	len = strlen(sql) + 1;
	*(unsigned short *)p = len;
	p += sizeof(unsigned short);
	memcpy(p, sql, len);
	out = udp_alloc_package(argus->addr, ARGUS_SERVICE_CREATE_QUERY, len + sizeof(ARGUS *) + sizeof(unsigned short), buf);
	udp_send(out);
	udp_free_package(out);
	return 0;
}

int argus_drop_sql (ARGUS *argus, int id)
{
	struct request {
		ARGUS *tag;
		int id;
	} request;
	package_t *out;
	request.tag = argus;
	request.id = id;
	out = udp_alloc_package(argus->addr, ARGUS_SERVICE_DROP_QUERY, sizeof(struct request), &request);
	udp_send(out);
	udp_free_package(out);
	return 0;
}
