/* filename: info.c
   by Dong Wei */
#include "pascal.h"

char *title;
table_stack_t symbol_stack;
table_t *recstack;
stack_t *record_stack, *proc_stack;
text_t *text;
hash_t *string_table;
hash_t *string_const;
queue_t *string_const_queue;
queue_t *external;

char *file_in;
char *file_out;

FILE *output;
int elf, assemble;

void (*md_optimize) (void);
void (*codegen) (void);

int O;

int tolowercase;

int yyok;
int yyline;

int machine_state_size;

void i386_optimize (void);
void i386_codegen (void);
void mips_optimize (void);
void mips_codegen (void);
void vm_optimize (void);
void vm_codegen (void);
void help (void);

entry_t *int_entry;
entry_t *bool_entry;
entry_t *char_entry;
entry_t *pointer_entry;
entry_t *real_entry;
entry_t *string_entry;

void pre_parse (void)
{
	char *p;
	title = NULL;
	yyok = 1;
	elf = assemble = 1;
	table_stack_init(&symbol_stack);
	table_stack_grow(&symbol_stack);
	string_table = hash_alloc(0, 0);
	string_const = hash_alloc(0, 0);
	string_const_queue = queue_alloc();
	external = queue_alloc();
	recstack = NULL;
	text = text_alloc(0);
	record_stack = stack_alloc();
	proc_stack = stack_alloc();
	/* add the three original thing */
	table_stack_append(&symbol_stack, int_entry = atomic_alloc(strdup("integer"), ATOMIC_INTEGER, 4, 0x80000000, 0x7FFFFFFF));
	table_stack_append(&symbol_stack, bool_entry = atomic_alloc(strdup("boolean"), ATOMIC_BOOL, 4, 0, 1));
	table_stack_append(&symbol_stack, char_entry = atomic_alloc(strdup("char"), ATOMIC_CHAR, 1, 0, 255));
	table_stack_append(&symbol_stack, pointer_entry = atomic_alloc(strdup("pointer"), ATOMIC_POINTER, 4, 0, 0xffffffff));
	table_stack_append(&symbol_stack, 
		real_entry = real_alloc(strdup("real")));
	table_stack_append(&symbol_stack, string_entry = atomic_alloc(strdup("string"), ATOMIC_STRING, 4, 0, 0xffffffff));
	p = strdup("scanf");
	hash_insert(string_table, p, p);
	p = strdup("printf");
	hash_insert(string_table, p, p);
	enqueue(external, strdup("printf"));
	enqueue(external, strdup("scanf"));
	yyline = 1;
}

void parse_args (int argc, char *argv[])
{
	int opt;
	file_in = NULL;
	file_out = NULL;
	O = 0;
	tolowercase = 1;
	md_optimize = i386_optimize;
	codegen = i386_codegen;
	machine_state_size = 12;
	for (;;)
	{
		opt = getopt(argc, argv, "chi:o:t:O:Sv");
		if (opt == -1) break;
		switch (opt)
		{
			case 'c': elf = 0; break;
			case 'h': help(); exit(0); break;
			case 'i': file_in = strdup(optarg); break;
			case 'o': file_out = strdup(optarg); break;
			case 'O': O = atoi(optarg); break;
			case 'S': assemble = 0; break;
			case 't': if (strcmp(optarg, "i386") == 0)
					{
						machine_state_size = 12;
						md_optimize = i386_optimize;
						codegen = i386_codegen;	
					}
				  else if (strcmp(optarg, "mips") == 0)
				  {
					  md_optimize = mips_optimize;
					  codegen = mips_codegen;
				  }
				  else if (strcmp(optarg, "vm") == 0)
				  {
					  md_optimize = vm_optimize;
					  codegen = vm_codegen;
				  }
				  else
				  {
					  fprintf(stderr, "Target not supported.\n");
					  exit(-1);
				  }				  
			case 'v': tolowercase = 0; break;
		}
	}
}

void cleanup (void)
{
	char *s;
	text_destroy(text);
	table_stack_destroy(&symbol_stack);
	free(file_in);
	free(file_out);
	free(title);
	stack_free(record_stack);
	stack_free(proc_stack);
	queue_free_content(string_const_queue);
	queue_free(string_const_queue);
	string_table->flag = HASH_STRDUP;
	hash_free(string_table);
	hash_free(string_const);
	for (;;)
	{
		s = dequeue(external);
		if (s == NULL) break;
		free(s);
	}
	queue_free(external);
}

static char castbuf[32];

char *itoa (int n)
{
	char *new;
	sprintf(castbuf, "%d", n);
	new = strdup(castbuf);
	assert(new != NULL);
	return new;
}

char *ftoa (double n)
{
	char *new;
	sprintf(castbuf, "%g", n);
	new = strdup(castbuf);
	assert(new != NULL);
	return new;
}

char *symbol_stack_append(entry_t *e)
{
	assert(e != NULL);
	if (STACK_CHECK(e->name))
		table_stack_append(&symbol_stack, e);
	else
	{
		ERROR("symbol %s already defined.\n", e->name);
		entry_free(e);
	}
}

int new_string_const (char *s)
{
	int i;
	assert(s != NULL);
	i = (int)hash_lookup(string_const, s);
	if (i == 0)
	{
		i = new_global();
	 	hash_insert(string_const, s, (void *)i);
		enqueue(string_const_queue, s);
	}
	else
	{
		free(s);
	}
	return i;
}

char *make_ret_name (char *b)
{
	static char buf[128];
	strcpy(buf, b);
	strcat(buf, "#ret");
	return buf;
}
