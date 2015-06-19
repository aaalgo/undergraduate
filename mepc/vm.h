/**
  * \file vm.h
  * \author Dong Wei
  *
  * Definition of the virtual machine.
  * The virtual machine accepts instructions with three arguments.
  * Each argument can be constant, memory address, label or
  * string (procedure name), or NULL.
  */

#ifndef __PASCAL_VM__
#define __PASCAL_VM__

#define DEF_TEXT_SIZE 0x8000

/// No argument.
#define ARG_NONE	0	/* temp = offset = 0 */
/// Constant argument.
#define ARG_CONST	1	/* temp = 0, offset = value */
/// Stack variable argument.
#define ARG_STACK	2	/* address = #temp + offset */
/// Global variable argument.
#define ARG_GLOBAL	4	/* not supported currently */
/// Symbol (procedure name) argument.
#define ARG_SYMBOL	8	/* offset: pointer to string */
/// Label argument.
#define ARG_LABEL	16
/// Real argument.
#define ARG_REAL	32	/* real constant use a special type: r_arg_t */
#define ARG_SADDR	64
/// Global address argument.
#define ARG_GADDR	128

/// Virtual machine instruction argument type.
typedef struct arg
{
	/// Type of the argument.
	int flag;
	/// Variable id (if have).
	int temp;
	/// offset of the variable (if have).
	int offset;
} arg_t;

typedef struct r_arg
{
	int flag;
   	double real;
} r_arg_t;

/// Virtual machine instruction type.
typedef struct instruct
{
	/// Opcode.
	int op;
	/// Three arguments.
	arg_t arg[3];
	/* arg[1] : result
	   arg[2] : arg1
	   arg[2] : arg2 */
} instruct_t;


typedef void (*func_t) ();

/// The generated virtual machine code(text segment).
typedef struct text
{
	/// size of the segment.
	int size;
	/// The last instruction.
	int last;
	/// Memory storage.
	instruct_t *data;
} text_t;

///  Init the text.
static inline void text_init (text_t *text, int size)
{
	assert(text != NULL);
	if (size <= DEF_TEXT_SIZE) size = DEF_TEXT_SIZE;
	text->size = size;
	text->last = 0;
	size *= sizeof(instruct_t);
	text->data = (instruct_t *)malloc(size);
	bzero(text->data, size);
	assert(text->data != NULL);
}
/// Allocate a text segment of given size.
static inline text_t *text_alloc (int size)
{
	text_t *t;
	t = (text_t *)malloc(sizeof(text_t));
	assert(t != NULL);
	text_init(t, size);
	return t;
}
/// Destroy a text segment.
static inline void text_destroy (text_t *text)
{
	int i, j;
	assert(text != NULL);
	free(text->data);
}
/// Free a text segment.
static inline void text_free (text_t *text)
{
	assert(text != NULL);
	text_destroy(text);
	free(text);
}
/// The address of the next instruction in the text segment.
static inline int text_next (text_t *text)
{
	assert(text != NULL);
	return text->last;
}

char *string_append (char  *);
/// Make a const argument.
#define CONST_ARG(n) 		((arg_t){ARG_CONST, 0, n})
/// Make a stack variable argument.
#define STACK_ARG(tmp, ofs) 	((arg_t){ARG_STACK, tmp, ofs})
/// Make a global variable argument.
#define GLOBAL_ARG(tmp, ofs)	((arg_t){ARG_GLOBAL, tmp, ofs})
/// Make a symbol argument.
#define SYMBOL_ARG(n) 		((arg_t){ARG_SYMBOL, 0, (int)append_string(n)})
/// Make a null argument.
#define NULL_ARG 		((arg_t){0,0,0})
/// Make a label argument.
#define LABEL_ARG(n) 		((arg_t){ARG_LABEL, 0, (int)n})
/// Make a real argument.
#define REAL_ARG(n)		((arg_t)(r_arg_t){ARG_REAL, n})
/// Make a global address argument.
#define GADDR_ARG(tmp, ofs)	((arg_t){ARG_GADDR, tmp, ofs})
/// Make a local address argument.
#define LADDR_ARG(tmp, ofs)	((arg_t){ARG_LADDR, tmp, ofs})

/// Make an argument from an (variable) expression
static inline arg_t VAR_ARG (expression_t *e)
{
	if ((e->flag & EXPR_STACK) || (e->flag & EXPR_POINTER))
	{
		return STACK_ARG(e->temp, e->offset);
	}
	else if (e->flag & EXPR_GLOBAL)
	{
		return GLOBAL_ARG(e->temp, e->offset);
	}
	INFO("%d", e->flag);
	assert(0);
}

/// Make an argument from an (variable or constant) expression.
static inline arg_t DAT_ARG (expression_t *e)
{
	if (HAS_VARIABLE(e))
	{
		return VAR_ARG(e);
	}
	else if (e->flag == EXPR_CONST)
	{
		return CONST_ARG(e->integer);
	}
/*	else if (e->flag == EXPR_REAL)
	{
		return REAL_ARG(e->real);
	}*/
	assert(0);
}

/// Emit a instruction to the given text segment.
static inline void text_emit (text_t *text, int op,
		arg_t a, arg_t b, arg_t c)
{
	int last;
	assert(text != NULL);
	last = text->last;
	assert(last < text->size);
	text->data[last].op = op;
	text->data[last].arg[0] = a;
	text->data[last].arg[1] = b;
	text->data[last].arg[2] = c;
	assert(abs(a.temp) < 1000);
	assert(abs(b.temp) < 1000);
	assert(abs(c.temp) < 1000);
	text->last++;
}

extern int vm_label, vm_temp, vm_global, vm_proc;

/// Reset the procedure/function counter.
static inline void reset_proc (void)
{
		vm_proc = 1;
}

/// Get a new procedure/function id.
static inline int new_proc (void)
{
		return vm_proc++;
}

/// Allocate a new label.
static inline int new_label (void)
{
	return vm_label++;
}
/// Get the id of the next label.
static inline int next_label (void)
{
	return vm_label;
}

extern text_t *text;

/// Reset the label counter.
static inline void reset_label (void)
{
	vm_label = 1;
}

/// Allocate a temparary variable.
static inline int new_temp (void)
{
	return vm_temp++;
}
/// ID of the next temparary variable.
static inline int next_temp (void)
{
	return vm_temp;
}
/// Reset the temparary variable counter.
static inline void reset_temp (void)
{
	vm_temp = 1;
}
/// Reset the global variable counter.
static inline void reset_global (void)
{
	vm_global = 1;
}
/// Allocate a new global variable.
static inline int new_global (void)
{
	return vm_global++;
}
/// Optimize in the virtual machine code level.
void vm_optimize (void);
/// Generate virtual machine code as output.
void vm_codegen (void);

void print_asm_string (FILE *, char *);
#endif
