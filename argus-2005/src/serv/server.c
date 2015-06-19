#include <argus.h>
#include <udp.h>
#include <service.h>

ARGUS *argus;

extern int schema_encode (void *sch, void *out, int bufsize);
extern int schema_decode (void *sch, void *in);
extern int tuple_encode (schema_t *schema, void *tuple, void *buffer, int buf_size);
extern int tuple_decode (schema_t *schema, void *tuple, void *buffer);

struct session
{
	int tag;
	int query;
	struct sockaddr_in addr;
};


int service_callback (void *s, int msg, int int_p, void *p_p)
{
	struct session *session = (struct session *)s;
	switch (msg)
	{
	case ARGUS_REGISTERED:
		{
			char buf[1024];
			char *p = buf;
			package_t *out;
			int ret;
			*(int *)p = session->tag;
			p += sizeof(int);
			*(int *)p = int_p;
			p += sizeof(int);
			if (p_p != NULL)
			{
				ret = schema_encode(&p_p, p, 1024-2*sizeof(int));
				p += ret; 
			}
			out = udp_alloc_package(session->addr, ARGUS_REPLY_QUERY_CREATED, p - buf, buf);
			udp_send(out);
			udp_free_package(out);
			printf("Registered %d\n", int_p);
		}
		break;
	case ARGUS_ERROR:
		{
			struct reply
			{
				int tag;
				int id;
			} reply;
			package_t *out;
			reply.tag = session->tag;
			reply.id = int_p;
			out = udp_alloc_package(session->addr, ARGUS_REPLY_ERROR, sizeof reply, &reply);
			udp_send(out);
			udp_free_package(out);
		}
		break;
	case ARGUS_TUPLE:
		{
			struct reply
			{
				int tag;
				int id;
				int type;
				int size;
				char buf[1024];
			} reply;
			tuple_t *tuple;
			package_t *out;
			tuple = (tuple_t *)p_p;
			reply.tag = session->tag;
			reply.id = 0;
			reply.type = int_p;
			if (tuple == NULL)
			{
				reply.size = 0;
			}
			else
			{
				reply.id = tuple->id;
				reply.size = tuple_encode(tuple->schema, tuple->data, reply.buf, 1024);
				if (reply.size < 0) return 0;
			}
			out = udp_alloc_package(session->addr, ARGUS_REPLY_SEND_TUPLE, 4 * sizeof(int) + reply.size, &reply);
			udp_send(out);
			udp_free_package(out);
		}
		break;
	case ARGUS_DEREGISTERED:
		{
			package_t *out;
			out = udp_alloc_package(session->addr, ARGUS_REPLY_QUERY_DROPPED, sizeof(int), &(session->tag));
			udp_send(out);
			udp_free_package(out);
		}
		break;
	}
	return 0;
}

int service_create_stream (void *nul, package_t *package)
{
	int name_len, size;
	char *name;
	void *schema_data;
	schema_t *sch;
	struct __reply {
		int tag;
		int id;
		unsigned short name_len;
		char name[MAX_ID_LEN];
	} reply;
	package_t *out;
	reply.tag = *(int *)package->data;
	name_len = *(unsigned short *)(package->data + sizeof(int));
	name = package->data + sizeof(unsigned short) + sizeof(int);
	schema_data = name + name_len;
	schema_decode(&sch, schema_data);
	reply.id = argus_create_stream(argus, name, sch);
	reply.name_len = name_len;
	strcpy(reply.name, name);
	size = sizeof(int) + 2 * sizeof(unsigned short) + name_len;
	out = udp_alloc_package(package->addr, ARGUS_REPLY_STREAM_CREATED, size, &reply);
	udp_send(out);
	udp_free_package(out);
	free(sch);
	return 0;
}

int service_drop_stream (void *nul, package_t *package)
{
	struct reply
	{
		int tag;
		int ret;
	} reply;
	int id;
	package_t *out;
	reply.tag = *(int *)(package->data);
	id = *(int *)(package->data + sizeof(int));
	reply.ret = argus_drop_stream(argus, id);
	out = udp_alloc_package(package->addr, ARGUS_REPLY_STREAM_DROPPED, sizeof(struct reply), &reply);
	udp_send(out);
	udp_free_package(out);
	return 0;
}

int service_create_query (void *nul, package_t *package)
{
	struct session *session = type_alloc(struct session);
	char *query;
	session->addr = package->addr;
	session->query = -1;
	session->tag = *(int *)package->data;
	query = package->data + sizeof(unsigned short) + sizeof(int);
	info("Create query:\n\t%s\n", query);
	argus_exec_sql(argus, query, service_callback, session);
	return 0;
}

int service_drop_query (void *nul, package_t *package)
{
	argus_drop_sql(argus, *(int *)(package->data+sizeof(int)));
	return 0;
}

int service_tuple (void *nul, package_t *package)
{
	int id;
	int type;
	int data_size;
	char *tuple_data;
	char *out;
	stream_t *stream;
	id = *(int *)package->data;
	tuple_data = package->data + sizeof(int);
	type = *(int *)tuple_data;
	tuple_data += sizeof(int);
	data_size = *(int *)tuple_data;
	tuple_data += sizeof(int);
	stream = stream_from_id(id);
	if (stream == NULL) return 0;
	
	if (data_size == 0)
	{
		argus_insert_tuple(argus, id, type, NULL);
	}
	else
	{
		out = (char *)xmalloc(schema_data_size(stream->schema));
		tuple_decode(stream->schema, out, tuple_data);
		argus_insert_tuple(argus, id, type, out);
		free(out);
	}
	return 0;
}


/*
#define FILE_NAME "querytime_2002_12_1"

schema_fix_t bingle_log = {5,{
	{"time", TYPE_DATETIME, 0},
	{"ip", TYPE_IP, 0},
	{"cached", TYPE_BOOL, 0},
	{"result", TYPE_INT, 0},
	{"key", TYPE_STRING, 0}
	}};

#define QUERY \
	"select ip, count(*), sum(result) from log where result > 5 and result < 10 and key = \'Hello\' group by ip"

int start_stream (void);
int stop_stream (void);

FILE *fin;

int bingle;
*/
int start_time;

int main ()
{
	argus = argus_connect("");
	start_time = TIME();
	udp_init();
	udp_register(ARGUS_SERVICE_CREATE_STREAM, service_create_stream, NULL);
	udp_register(ARGUS_SERVICE_DROP_STREAM, service_drop_stream, NULL);
	udp_register(ARGUS_SERVICE_CREATE_QUERY, service_create_query, NULL);
	udp_register(ARGUS_SERVICE_DROP_QUERY, service_drop_query, NULL);
	udp_register(ARGUS_SERVICE_SEND_TUPLE, service_tuple, NULL);
	udp_start(ARGUS_PORT);
/*	fix_schema((schema_t *)&bingle_log);
	bingle = argus_create_stream(argus, "log", (schema_t*)&bingle_log);
	assert(bingle >= 0);
	start_stream();*/
	for (;;)
	{
		getchar();
		break;
	}
/*	stop_stream();*/
	udp_stop();
	udp_cleanup();
	argus_shutdown(argus);
	return 0;
}

/*
DECLARE_THREAD(log_gen);


void reader (void *p)
{
	struct {
		datetime_t time;
		char ip[4];
		int cached;
		int result;
		char *key;
	} log;
	char buf[1024];
	int hour, min, sec, d0, d1, d2, d3, i, j;
	fin = fopen(FILE_NAME, "r");
	assert(fin != NULL);
	log.key = buf;
	log.time.nul = 0;
	log.time.day = 1;
	log.time.month = 12;
	log.time.year = 2002;
	for (;;)
	{
		fscanf(fin, "%*s%*s%*d%d:%d:%d%*d", &hour, &min, &sec);
		log.time.hour = hour;
		log.time.minute = min;
		log.time.second = sec;
		fscanf(fin, "%d.%d.%d.%d", &d0, &d1, &d2, &d3);
		log.ip[0] = d0;
		log.ip[1] = d1;
		log.ip[2] = d2;
		log.ip[3] = d3;
		fscanf(fin, "%s", buf);
		if (strcmp(buf, "Database") == 0)
			log.cached = 0;
		else
			log.cached = 1;
		while (fgetc(fin) != '\n');
		i = 0;
		for (;;)
		{
			j = fgetc(fin);
			if (j == '\n') break;
			buf[i++] = j;
		}
		buf[i] = 0;		
		fscanf(fin, "%d", &log.result);
		argus_insert_tuple(argus, bingle, TUPLE_INS, &log);
		SLEEP(1);
	}
	assert(0);
}

int start_stream (void)
{
	THREAD_CREATE(log_gen, reader, NULL);
	return 0;
}

int stop_stream (void)
{
	THREAD_DESTROY(log_gen);
	fclose(fin);
	return 0;
}
*/