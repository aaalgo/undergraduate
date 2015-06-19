#include <argus.h>

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

int argus_callback (void *, int msg, int, void *);

ARGUS *argus;
int bingle;
FILE *fin;
int start_time;
int query_ok;

int main ()
{
	char buf[1024];
	int query;
	start_time = TIME();
	fix_schema((schema_t *)&bingle_log);
	argus = argus_connect(NULL);
	bingle = argus_create_stream(argus, "log", (schema_t*)&bingle_log);
	assert(bingle >= 0);
	query = -1;
	for (;;)
	{
		schema_dump((schema_t *)&bingle_log);
		printf("OK> ");
		gets(buf);
		/* if (query >= 0) argus_drop_sql(argus, query); */
		query = argus_exec_sql(argus, buf, argus_callback, NULL);
		if (!query_ok) break;
		printf("Press <ENTER> to start stream...");
		getchar();
		start_stream();
		getchar();
		/* argus_drop_sql(argus, query); */
		break;
	}
	if (query_ok) stop_stream();
	argus_drop_stream(argus, bingle);
	argus_shutdown(argus);
	return 0;
}

int print_tuple (int type, tuple_t *tup)
{
	char buf[1024];
	char *p;
	int i;
	switch (type)
	{
		case TUPLE_INS:
			printf("+ ");
			break;
		case TUPLE_DEL:
			printf("- ");
			break;
		case TUPLE_REPLACE:
			printf("# ");
			break;
		case TUPLE_TIME:
			printf("TIME\n");
			return 0;
		case TUPLE_UPDATE:
			printf("UPDATE\n");
			return 0;
		case TUPLE_CLEAN:
			printf("CLEAN\n");
			return 0;
		case TUPLE_ADDED:
			printf("ADDED\n");
			return 0;
	}
	/*printf("%d\t%d :", tup->id, tup->time - start_time);*/
	p = tup->data;
	for (i = 0; i < tup->schema->nof; i++)
	{
		tup->schema->field[i].type->to_string(p, buf, 1024);
		printf("\t%s", buf);
		p += tup->schema->field[i].type->size;
	}
	printf("\n");
	tuple_unlock(tup);
	return 0;
}

int argus_callback (void *p, int msg, int int_p, void *p_p)
{
	switch (msg)
	{
		case ARGUS_REGISTERED:
			query_ok = 1;
			printf("Query registered.\n");
			return 0;
		case ARGUS_TUPLE:
			print_tuple(int_p, (tuple_t *)p_p);
			return 0;
		case ARGUS_DEREGISTERED:
			printf("Query deregistered.\n");
			return 0;
		case ARGUS_ERROR:
			query_ok = 0;
			printf("Error - %d\n", int_p);
			return 0;
		default:
			assert(0);
	}
	return 0;
}

DECLARE_THREAD(log_gen);


int reader (void *p)
{
	struct {
		datetime_t time;
		char ip[4];
		int cached;
		int result;
		char *key;
	} log;
	char buf[1024];
	int hour, min, sec, d0, d1, d2, d3;
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
		fgets(buf, 1024, fin);
		fgets(buf, 1024, fin);
		buf[strlen(buf)] = 0;
		fscanf(fin, "%d", &log.result);
		argus_insert_tuple(argus, bingle, TUPLE_INS, &log);
		SLEEP(2);
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
