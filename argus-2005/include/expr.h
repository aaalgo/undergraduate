/* Filename: expr.h
   by Dong Wei
 */

#ifndef __ARGUS_EXPR__
#define __ARGUS_EXPR__

#define NOPATCH -1

#define OPR_INC 4
#define BUF_INC 32

/* this structure describes an operator in the expression.
   An operator is made up of
   	A result
	One or two operands
	A function that do the operation
   And a expression is made up of a number of such operators.
   When the expression is evaluated, all the operators stored
   in the expression are evaluated one by one, and the result
   of the last operator is used as the result of the expression.
*/
typedef struct
{
		int patch;
		void *addr;
} pdpair_t;

typedef struct
{
/* pXXX indicates whether XXX has to be patched */
/* Order of the fields of this structure is hard coded in
   expr.c, so DO NOT touch them. */
	union {
	int	func_id;
	func_f func;
	};
	pdpair_t data[3];
} opr_t;

/* Why we have to patch an expression before evaluating it?

   An expression consists of a number of consts, operators, and
   tuple fields. Unlike consts which are fixed when the expression
   is given, the tuple fields have meaning only when an perticular
   tuple is given. So tuple fields in the expr_t structure only
   store the offset of the field in a tuple. The offsets surely
   can not be used to evaluate an expression. So we have to patch
   the expression, that is add the address of a tuple to the offsets
   , which makes the real memory address of the fields in the given
   tuple. But once you have patched an expression, the address
   stored for fields are not the original offsets. So when you
   patch the expression a second time, you can not simply add a
   new tuple address to them, but have to substract the tuple address
   previos added to the offset.
   So when you call the function PatchExpr, you give two addresses,
   the old tuple address and the new tuple address. When you first
   call the function, simply pass NULL to the old address.

   There's a another problem. Sometimes a expression has something to
   do with more than ONE tuples (this happens in the `join' process).
   So what passed to PatchExpr are actually two array of addresses.
   The pXXX value is the index of the address in the array that should
   be used. When only one tuple is involved, just pass 0 as pXXX,
   and address of the tuple address as the array.
   
example:
	you have two tuples
		void *s, *t;
	and an expression
		expr_t *e
	you patch the expression as follow to evaluate it on s
		void *r = NULL;
		expr_patch(e, &r, &s);
	again you want to evaluate the expression on t
		expr_patch(e, &s, &t);
*/

typedef struct
{
	void *result;
	int presult;
	type_t *tresult;	/* type of the result */
	int nopr;		/* # of operators */
	int sopr;		/* size of the operator list */
	opr_t *opr;
#ifdef MANAGE_CONST
	size_t sbuf;		/* size of the data buf */
	size_t bufend;		/* size of data in buf */
	char *buf; 		/* constant buffer */
#endif
} expr_t;

expr_t *expr_create (void);

/* Create an expression whose value is always TRUE */
/*
expr_t *CreateTrueExpr (void);
*/
/* remember to call expr_preevaluate before patch/evaluate.*/
int expr_preevaluate (expr_t *expr);
int expr_evaluate (expr_t *expr);

void expr_destroy (expr_t *expr);

/* Append a constant to the expression.
   The returned values is the address where the constant is 
   stored in the expression's buffer.
   If the constant has no specific value, which is the case
   when you have to reserve space for the result of an operator,
   just pass NULL as buf. */
#ifdef MANAGE_CONST
void *expr_append_const (expr_t *expr, size_t size, void *buf);
#endif

/* Append an operator to the expression.
   Three addresses involves in a operator -- address of the result
   and two operands. A address can be of three types.
   1. An address is returned by AppendConst. then pXXX is passed NOPATCH.
   2. An address is the offset in a tuple, then pXXX is 0 or a positive number.
   3. The address of the second oprand of an unary operator should always be
   	NULL, and pXXX be NOPATCH.
*/
int expr_append_opr (expr_t *expr, int func_id,
				void *result,
				void *opr1,
				void *opr2,
				int presult,
				int popr1,
				int popr2);

int expr_patch (expr_t *expr, void *old[], void *new[]);

/* Set the result of an expression. */

int expr_set_result (expr_t *expr, void *result, int patch, type_t *type);

#endif
