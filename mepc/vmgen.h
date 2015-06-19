/**
  * \file vmgen.h
  * \author Dong Wei
  *
  * Declaration of code generating functions.
  */

#ifndef __PASCAL_VMGEN__
#define __PASCAL_VMGEN__

/// Emit vm-code of 
void emit_declaration (table_t *);
/// Emit a label instruction.
void emit_label (char *l);
/// Emit vm-code compute a negative value of an expression.
expression_t *emit_neg (expression_t *);
/// Emit vm-code of assignment.
void emit_assign (expression_t *, expression_t *);
/// Emit vm-code compute the sum of the expressions.
expression_t *emit_plus (expression_t *, expression_t *);
/// Emit vm-code compute the difference of the expressions.
expression_t *emit_minus (expression_t *, expression_t *);
/// Emit the or instruction.
expression_t *emit_or (expression_t *, expression_t *);
/// Emit vm-code compute the product of the expressions.
expression_t *emit_times (expression_t *, expression_t *);
/// Emit vm-code compute the quotient of the real expressions.
expression_t *emit_divide (expression_t *, expression_t *);
/// Emit vm-code compute the quotient of the expressions.
expression_t *emit_div (expression_t *, expression_t *);
/// Emit vm-code compute the remainder of the division of two expressions.
expression_t *emit_mod (expression_t *, expression_t *);
/// Emit the and instruction.
expression_t *emit_and (expression_t *, expression_t *);
/// Emit the not instruction.
expression_t *emit_not (expression_t *);
/// Emit vm-code perform relational comparation.
expression_t *emit_relop (expression_t *e1, expression_t *e2, int);
/// Emit the value TRUE.
expression_t *emit_true (void);
/// Emit the value FALSE.
expression_t *emit_false (void);
/// Emit the code accessing a record field.
expression_t *emit_record_field (expression_t *r, char *f);
/// Emit code accessing a variable.
expression_t *emit_variable (char *text);
/// Emit code accessing an array element.
expression_t *emit_array_element (expression_t *a, queue_t *e);
/// Make program control from a bool expression.
expression_t *make_bool (expression_t *e);
expression_t *unmake_bool (expression_t *e);
/// Emit procedure invokation code.
expression_t *emit_invoke (char *, stack_t *);
/// Emit code for read operation.
void emit_read (stack_t *, int ln);
/// Emit code for write operation.
void emit_write (stack_t *, int ln);

#endif

