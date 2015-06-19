/**
  * \file info.h
  * \author Dong Wei
  *
  * Though the low level components of the compiler already provid
  * sufficient function, they are a little too complicated for frequent using.
  * This file defines a list of macros and declares a list of functions for
  * fast processing.
  */
#ifndef __PASCAL_INFO__
#define __PASCAL_INFO__

/// Set the title of the program.
#define SET_TITLE(n)	do { title = n ;}while(0);
/// Push a empty table to the symbol table stack.
#define STACK_PUSH	table_stack_grow(&symbol_stack)
/// Pop the symbol table stack.
#define STACK_POP	table_stack_pop(&symbol_stack)
/// Get the top table of the symbol table stack.
#define STACK_TOP	table_stack_top(&symbol_stack)
/// Look up a name in the symbol table stack, in a topdown manner.
#define STACK_LOOKUP(n, m)	table_stack_lookup(&symbol_stack, n, m)
/// Look up a name in the top table of the symbol table stack.
#define STACK_LOOKUP_TOP(n) table_stack_lookup_top(&symbol_stack, n)
/// Check that a name has not been in the top table of the symbol table stack.
#define STACK_CHECK(n) (table_stack_lookup_top(&symbol_stack, n) == NULL)
/// Append a entry to the (top table) of the symbol table stack.
#define STACK_APPEND(e) symbol_stack_append(e)
/// Append a entry to the (top table) of the symbol table stack, updating the hash table.
#define STACK_HASH_APPEND(e) table_stack_hash_append(&symbol_stack, e)
/// Append a label entry to the symbol table stack.
#define APPEND_LABEL(t)	STACK_APPEND(label_alloc(t))
/// Append a constant entry to the symbol table stack.
#define APPEND_CONST(n,t) STACK_APPEND(const_alloc(n,t))
/// Append a type entry to the symbol table stack.
#define APPEND_TYPE(n)	STACK_APPEND(n)
/// Emit a three-addressed vm-instruction.
#define EMIT(op, result, arg1, arg2) text_emit(text, op, result, arg1, arg2)
/// Get the address of the next instruction.
#define TEXT_NEXT	text_next(text)
/// Emit a label insruction.
#define EMIT_LABEL(n) EMIT(OP_LABEL,LABEL_ARG(n),NULL_ARG,NULL_ARG)
/// Emit a integer temparary variable allocation instruction
#define EMIT_INT_TEMP(n) EMIT(OP_TEMP, STACK_ARG(n, 0), CONST_ARG(4), NULL_ARG)
/// Emit a bool temparary variable allocation instruction.
#define EMIT_BOOL_TEMP(n) EMIT(OP_TEMP, STACK_ARG(n, 0), CONST_ARG(4), NULL_ARG)
/// Emit a real temparary variable allocation instruction.
#define EMIT_REAL_TEMP(n) EMIT(OP_TEMP, STACK_ARG(n, 0), CONST_ARG(8), NULL_ARG)
/// Emit a instruction allocating m bytes.
#define EMIT_N_TEMP(n, m) EMIT(OP_TEMP, STACK_ARG(n, 0), CONST_ARG(m), NULL_ARG)
/// Generate real machine code, work in the way as printf.
#define GEN(n...) fprintf(output, n)

extern char *title;
extern table_stack_t symbol_stack;
extern table_t *recstack;

extern char *file_in;
extern char *file_out;
extern FILE *output;

extern void (*md_optimize) (void);
extern void (*codegen) (void);

extern int O;
extern text_t *text;

extern int machine_state_size;

extern stack_t *record_stack, *proc_stack;

extern entry_t *int_entry, *char_entry, *bool_entry, *pointer_entry, *string_entry;
extern entry_t *real_entry;

extern hash_t *string_table;

extern hash_t *string_const;

extern queue_t *string_const_queue;
extern queue_t *external;

extern int elf, assemble;

extern int tolowercase;

char *make_ret_name (char *);
/// Append a string to the global string hash table.
static inline char *append_string (char *s)
{
	char *r = hash_lookup(string_table, s);
	if (r != NULL) return r;
	s = strdup(s);
	hash_insert(string_table, s, s);
	return s;
}

/// Push a empty entry to the temparary stack.
static inline void recstack_push()
{
	table_t *n = table_alloc(0);
	n->next = recstack;
	recstack = n;	
}


char *symbol_stack_append(entry_t *e);

/// Push a empty entry to the temparary stack.
static inline table_t *recstack_pop()
{
	if (recstack == NULL)
	{
		return NULL;
	}
	else
	{
		table_t *tmp = recstack;
		recstack = tmp->next;
		return tmp;
	}
}

/// Initializing work to do before parsing the source code.
void pre_parse (void);
/// Recognize the program arguments.
void parse_args (int argc,char *argv[]);
/// Free all resources allocated so far.
void cleanup (void);

char *itoa (int);
char *ftoa (double);

int new_string_const(char *);

#define CHECK_SYMBOL(s)
#define ADD_SYMBOL(s)
#define REM_SYMBOL(s)

#endif

