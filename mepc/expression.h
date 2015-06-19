/**
  * \file expression.h
  * \author Dong Wei
  *
  * Header file for expression handling.
  */

#ifndef __PASCAL_EXPRESSION__
#define __PASCAL_EXPRESSION__

/* typedef struct expression expression_t; */

/// Const expression.
#define EXPR_CONST	1
/// Boolean expression.
#define EXPR_BOOL	2
/// Local variable expression.
#define EXPR_STACK	4
/// Global variable expression.
#define EXPR_GLOBAL	8
/// Pointer expression.
#define EXPR_POINTER	16
/// Real expression.
#define EXPR_REAL	32
/// String expression.
#define EXPR_STRING	64

/// Decide whether the expression e has a constant in it.
#define HAS_CONST(e) ((e->flag & EXPR_CONST) != 0)
/// Decide whether the expression e has a variable in it.
#define HAS_VARIABLE(e) ((e->flag & (EXPR_STACK | EXPR_GLOBAL)) != 0)
/// Decide whether the expression e has a pointer in it.
#define HAS_POINTER(e) ((e->flag & EXPR_POINTER) != 0)

/// The expression structure.
/**
  * The expression has a number of value fields, such as real, integer,...
  * A expression often has only one type, so only one value field is used.
  * Which one used is determined by the type of the expression.
  * \see expression_t Which is actually defined as struct expression.
  */
struct expression
{
	/// Information of the expression.
	/** Combination of EXPR_XXX. */
	int flag;
	/// Type of the expression.
	entry_t *type;
	/// Real value.
	double real;
	/// Integer value.
	int integer;
	/// Temp variable id.
	int temp;
	/// Offset of the variable.
	int offset;
	/// Label value.
	int label;
	/// True patch list of the label.
	queue_t *true_list;
	/// False patch list of the label.
	queue_t *false_list;
	/// address of code if exist
	int address;
};

/// The expression type.
typedef struct expression expression_t;

/// Duplicate a expression.
/**
  * \param e The source expression.
  * \result The expression copied.
  */
static inline expression_t *expr_copy (expression_t *e)
{
	expression_t *n;
	assert(e->true_list == NULL && e->false_list == NULL);
	n = (expression_t *)malloc(sizeof(expression_t));
	*n = *e;
	return n;
}

/// Allocate an arbituary expression.
/** 
  * \result The expression created.
  */
static inline expression_t *expr_alloc (void)
{
	expression_t *exp;
	exp = (expression_t *)malloc(sizeof(expression_t));
	assert(exp != NULL);
	bzero(exp, sizeof(expression_t));
	return exp;
}

/// Free a expression.
/**
  * \param e The expression to free.
  */
static inline void expr_free (expression_t *e)
{
	if (e != NULL)
	{
	/* assert(e->true_list == NULL && e->false_list == NULL); */
		free(e);
	}
}

extern entry_t *int_entry, *bool_entry, *real_entry, *string_entry, *char_entry;

/// Create a integer type expression.
/**
  * \param i Value of the expression.
  * \result The expression created.
  */
static inline expression_t *make_int_expr (int i)
{
	expression_t *exp;
	exp = expr_alloc();
	exp->flag = EXPR_CONST;
	exp->type = int_entry;
	exp->integer = i;
	return exp;
}

/// Create a real type expression.
/**
  * \param r Value of the expression.
  * \result The expression created.
  */
static inline expression_t *make_real_expr (double r)
{
	expression_t *exp;
	exp = expr_alloc();
	exp->flag = EXPR_CONST;
	exp->type = real_entry;
	exp->real = r;
	return exp;
}

/// Create a string type expression.
/**
  * \param s Value of the expression.
  * \result The expression created.
  */
static inline expression_t *make_string_expr (char *s)
{
	expression_t *exp;
	exp = expr_alloc();
	exp->flag = EXPR_GLOBAL;
	exp->type = string_entry;
	exp->temp = new_string_const(s);
	return exp;
}

/// Create a char type expression.
/**
  * \param c Valud of the expression.
  * \result The expression created.
  */
static inline expression_t *make_char_expr (char c)
{
	expression_t *exp;
	exp = expr_alloc();
	exp->flag = EXPR_CONST;
	exp->type = char_entry;
	exp->integer = c;
	return exp;
}

#endif

