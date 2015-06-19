/* filename: pascal.y
   by Dong Wei
*/
%{
#include "pascal.h"
%}

%union
{
	char *text;
	int integer;
	double real;
	stack_t *stack;
	queue_t *queue;
	entry_t *entry;
	expression_t *expr;
}

%start program
/* Keywords */
%token K_AND
%token K_ARRAY
%token K_BEGIN
%token K_CASE
%token K_CDECL
%token K_CONST
%token K_DIV
%token K_DO
%token K_DOWNTO
%token K_ELSE
%token K_END
%token K_EXTERNEL
%token K_FALSE
%token K_FILE
%token K_FOR
%token K_FUNCTION
%token K_GOTO
%token K_IF
%token K_IN
%token K_NEG
%token K_NOT
%token K_OF
%token K_OR
%token K_LABEL
%token K_MOD
%token K_NIL
%token K_PASCAL
%token K_PACKED
%token K_POS
%token K_PROCEDURE
%token K_PROGRAM
%token K_RECORD
%token K_READ
%token K_READLN
%token K_REPEAT
%token K_SET
%token K_THEN
%token K_TO
%token K_TRUE
%token K_TYPE
%token K_UNTIL
%token K_VAR
%token K_WHILE
%token K_WITH
%token K_WRITE
%token K_WRITELN
%token K_XOR
/* Punctuation marks */
%token AT		/* @  */
%token CARET		/* '  */
%token COLON		/* :  */
%token COMMA		/* ,  */
%token DIVIDE		/* /  */
%token DOTDOT		/* .. */
%token EQUALS		/* =  */
%token GE		/* >= */
%token GT		/* >  */
%token IS		/* := */
%token LBRACKET		/* [  */
%token LE		/* <= */
%token LPAREN		/* (  */
%token LT		/* <  */
%token MINUS		/* -  */
%token NE		/* <> */
%token PERIOD		/* .  */
%token PLUS		/* +  */
%token RBRACKET		/* ]  */
%token RPAREN		/* )  */
%token SCOLON		/* ;  */
%token TIMES		/* *  */
%token IDENTIFIER
%token INTEGER
%token REAL
%token STRING
%token POS
%token NEG

%token <text> IDENTIFIER
%token <integer> INTEGER
%token <real> REAL
%token <text> STRING
%token <text> LABEL

%type <text> label
%type <queue> list_label list_identifier record_section list_type
%type <stack> list_expression
%type <entry> type structured_type scalar_type array_type record_type subrange function_heading type_def
%type <expr> expression sexpr term factor variable constant
%type <integer> relop function_property

%%
program			: K_PROGRAM IDENTIFIER
			{	
				SET_TITLE($2); 
				EMIT(OP_TITLE, SYMBOL_ARG($2),
					NULL_ARG, NULL_ARG);
				reset_global();
				reset_label();
				reset_proc();
			}
			SCOLON 
			{
				STACK_PUSH;
				stack_push(proc_stack, (int)$2);
				stack_push(proc_stack, 0);
				stack_push(record_stack, 0);
				stack_push(proc_stack, new_proc());
			}
			block
			{
				EMIT(OP_ENDP, NULL_ARG, NULL_ARG, NULL_ARG);
				STACK_POP;
			}
			PERIOD
			{
				EMIT(OP_END, NULL_ARG, NULL_ARG, NULL_ARG);
			}
			;

block			:list_declaration
			{
				EMIT(OP_PROC, SYMBOL_ARG((char *)stack_pop(proc_stack)), CONST_ARG(stack_pop(proc_stack)), CONST_ARG(stack_pop(proc_stack)));				
				reset_temp();
				emit_declaration(STACK_TOP);
				stack_pop(record_stack);
			}
			compound_statement
			;
			
list_declaration	: list_declaration declaration
			|
			;

declaration		: label_declaration_part
			| constant_definition_part
			| type_definition_part
			| variable_declaration_part
			| function_declaration
			| error
			{
					yyok = 0;
			}
			;
			
label_declaration_part	: K_LABEL list_label SCOLON
			;

list_label		: list_label COMMA label
			{ APPEND_LABEL($3); }
			| label
			{ APPEND_LABEL($1); }
			;

label			: INTEGER
			{ $$ = itoa($1); }
			| IDENTIFIER
			{ $$ = $1; }
			;

constant_definition_part: K_CONST list_constant_definition
			;

list_constant_definition: list_constant_definition constant_definition
			| constant_definition
			;

constant_definition	: IDENTIFIER EQUALS constant SCOLON
			{ 
				if ($3 != NULL) APPEND_CONST($1, $3);
				else free($1);
			}
			;

constant		: expression
			{
				if ($1 == NULL) $$ = NULL;
				else
				if (($1->flag != EXPR_CONST)
				&& ($1->flag != EXPR_GLOBAL
					|| $1->type != string_entry)) 
				{
					ERROR("Invalid constant definition.");
					expr_free($1);
					$$ = NULL;
				}
				else
				{
					$$ = $1;
				}
			}
			;
			

type_definition_part	: K_TYPE list_type_definition
			;

list_type_definition	: list_type_definition type_definition
			| type_definition
			;
			
type_definition		: IDENTIFIER EQUALS type SCOLON
			{
				if ($3 == NULL) free($1);
				else
				{
					if ($3->name != NULL)
					{
						$3 = entry_copy($3);
						free($3->name);
						$3->name = NULL;
						APPEND_TYPE($3);
					}
					$3->name = $1;
					STACK_HASH_APPEND($3);
				}
			}
			;

type			: type_def
			{
				if ($1 != NULL)
				{
					if ($1->name == NULL)
					{
						APPEND_TYPE($1);
					}
				}
				$$ = $1;
			}
			;
			
type_def		: IDENTIFIER
			{
				entry_t *e = STACK_LOOKUP($1, NULL);
				if (e == NULL)
				{
					ERROR("type %s not found.\n", $1);
					$$ = NULL;
				}
				else $$ = e;	
				free($1);
			}
			| scalar_type
			{ $$ = $1; }
			| subrange
			{ $$ = $1; }
			| structured_type
			{ $$ = $1; }
			| K_PACKED structured_type
			{ $$ = $2; }
			| CARET type
			{
				if ($2 != NULL)
				{
					$2->flag = $2->type;
					$2->type = ENTRY_POINTER;
					$$ = $2;
				}
				else $$ = NULL;
			}
			;

scalar_type		: LPAREN list_identifier RPAREN
			{
				$$ = scalar_alloc($2);
			}
			;

subrange		: expression DOTDOT expression
			{ 
				$$ = subrange_alloc($1, $3); 
			}
			;


structured_type		: array_type
			{ $$ = $1; }
			| record_type
			{ $$ = $1; }
			;

array_type		: K_ARRAY LBRACKET list_type RBRACKET K_OF
			  type
			{
				if ($6 != NULL)
				{
					$$ = array_alloc($6, $3);
				}
				else
				{
					queue_free_content($3);
					queue_free($3);
					$$ = NULL;
				}
			}
			;

list_type		: list_type COMMA type
			{
				if ($3 != NULL)
				{
					enqueue($1, (char*)$3);
				}
				$$ = $1;
			}
			| type
			{
				$$ = queue_alloc();
				if ($1 != NULL)
				{
					enqueue($$, (char *)$1);
				}
			}
			;

record_type		: K_RECORD 
			{
				stack_push(record_stack, 0);
				recstack_push();
			}
			field_list K_END
			{
				$$ = record_alloc(recstack_pop());
				stack_pop(record_stack);
			}
			;
			
field_list		: list_record_section scolon_or_none
			| list_record_section SCOLON variant_part
			| variant_part
			;

list_record_section	: list_record_section SCOLON record_section
			| record_section
			;
			
record_section		: list_identifier COLON type
			{
				int offset = stack_pop(record_stack);
				char *name;
				for (;;)
				{
					name = dequeue($1);
					if (name == NULL) break;
					table_append(recstack, 
						field_alloc($3, name, offset));
					offset += $3->size;
				}
				queue_free($1);
				stack_push(record_stack, offset);
			}
			;

variant_part		: K_CASE IDENTIFIER COLON type K_OF
			{
				int offset = stack_pop(record_stack);
				if ($4->type != ENTRY_ATOMIC &&
					$4->type != ENTRY_SUBRANGE &&
					$4->type != ENTRY_SCALAR)
				{
					ERROR("Invalid type.\n");
				}
				table_append(recstack,
					field_alloc($4, $2, offset));
				offset += $4->size;
				stack_push(record_stack, offset);
				INFO("VARIANT\n");
			}
			list_variant
			;

list_variant		: list_variant variant
			| variant
			;

variant			: list_expression COLON LPAREN 
			{ 
				expression_t *e;
				while (!stack_empty($1))
				{
					e = (expression_t *)stack_pop($1);
					expr_free(e);
				}
				stack_free($1);
				stack_push(record_stack, stack_top(record_stack)); 
			}
			field_list
			{
				stack_pop(record_stack);
			}
			RPAREN SCOLON
			;


variable_declaration_part : K_VAR
			{ 
				INFO("K_VAR\n");
			}
			list_variable_declaration
			;

list_variable_declaration: list_variable_declaration variable_declaration
			| variable_declaration
			;
			
variable_declaration: list_identifier COLON type SCOLON
			{
				char *name;
				int i;
				i = stack_pop(record_stack);
				for (;;)
				{
					name = dequeue($1);
					if (name == NULL) break;
					i -= $3->size;
				STACK_APPEND(variable_alloc($3, name,i));
				}
				queue_free($1);
				stack_push(record_stack, i);
				INFO("variable of type %s\n", $3->name);
			}
			;

function_declaration	: function_heading
			{
				entry_t *e;
				INFO("FUNCTION BEGIN %s\n", $1->name);
				STACK_APPEND($1);
				INFO("A\n");
				STACK_PUSH;
				INFO("B\n");
				if ($1->a.procedure.rtype != NULL)
				{
					INFO("C\n");
					STACK_APPEND(
					variable_alloc(
					$1->a.procedure.rtype,
					strdup(make_ret_name($1->name)),
					-$1->a.procedure.rtype->size));
					stack_push(record_stack,
						-$1->a.procedure.rtype->size);
				}
				else stack_push(record_stack, 0);
				INFO("D\n");
				if ($1->a.procedure.param == NULL)
					e = NULL;
				else
					e = $1->a.procedure.param->entries;
				INFO("BEGIN WHILE\n");
				while (e != NULL)
				{
					STACK_APPEND(entry_copy(e));
					e = e->next;
				}
				INFO("END WHILE\n");
				stack_push(proc_stack, (int)$1->name);		
				stack_push(proc_stack, $1->a.procedure.psize);
				stack_push(proc_stack, $1->a.procedure.id);
			}
			block
			{
				if ($1->a.procedure.rtype != NULL)
				{
					EMIT(OP_RET, STACK_ARG(0,
					-$1->a.procedure.rtype->size),
					CONST_ARG($1->a.procedure.rtype->size),
					NULL_ARG);
				}
				EMIT(OP_ENDP, NULL_ARG, NULL_ARG, NULL_ARG);
				STACK_POP;
				INFO("FUNCTION END\n");
			}
			SCOLON
			| function_heading K_EXTERNEL
			SCOLON
			{
				$1->a.procedure.id = 0;
				STACK_APPEND($1);
				append_string($1->name);
				enqueue(external, strdup($1->name));
			}
			;

function_property:	K_CDECL SCOLON
			{
				$$ = PROCEDURE_CDECL;
			}
			| K_PASCAL SCOLON
			{
				$$ = PROCEDURE_PASCAL;
			}
			|
			{
				$$ = PROCEDURE_PASCAL;
			}
			;
			
function_heading	: K_PROCEDURE IDENTIFIER SCOLON
			function_property
			{
				$$ = proc_alloc($2, NULL, NULL, $4, 0);
			}
			| K_PROCEDURE IDENTIFIER LPAREN list_parameter_group 
			RPAREN SCOLON function_property
			{
				INFO("ENTER\n");
				$$ = proc_alloc($2, NULL, recstack_pop(), $7,
					stack_pop(record_stack));
				INFO("EXIT\n");
			}
			| K_FUNCTION IDENTIFIER COLON type SCOLON
			function_property
			{
				$$ = proc_alloc($2, $4, NULL, $6, 0);
			}
			| K_FUNCTION IDENTIFIER LPAREN list_parameter_group
			RPAREN COLON type SCOLON function_property
			{
				$$ = proc_alloc($2, $7, recstack_pop(), $9,
					stack_pop(record_stack));
			}
			;

list_parameter_group :  list_parameter_group SCOLON parameter_group
			|
			{
				recstack_push();
				stack_push(record_stack, machine_state_size);
			}
			parameter_group
			;

parameter_group		: list_identifier COLON type
			{
				entry_t *e;
				char *name;
				int offset;
				if ($3 != NULL)
				{
					offset = stack_pop(record_stack);
					for (;;)
					{
						name = dequeue($1);
						if (name == NULL) break;
						e = param_alloc($3, name,
						offset, PARAM_BYVALUE);
						offset += ($3->size + 3)
							& (~(int)3);
						table_append(recstack, e);
					}
					stack_push(record_stack, offset);
				}
				queue_free($1);
			}
			| K_VAR list_identifier COLON type
			{
				entry_t *e;
				char *name;
				int offset;
				if ($4 != NULL)
				{
					offset= stack_pop(record_stack);
					for (;;)
					{
						name = dequeue($2);
						if (name == NULL) break;
						e = param_alloc($4, name,
						offset, PARAM_BYREFERENCE);
						offset += 4;
						table_append(recstack, e);
					}
					stack_push(record_stack, offset);
				}
				queue_free($2);
			}
			;


variable		: IDENTIFIER
			{
				int l = new_label();
				EMIT_LABEL(l);
				$$ = emit_variable($1);
				if ($$ != NULL)
				{
					$$->label = l;
				}
			}
			| variable LBRACKET list_expression RBRACKET
			{
				if ($1 != NULL && $3 != NULL)
				{
					int l = $1->label;
					$$ = emit_array_element($1, stack2queue($3));
					if ($$ != NULL)
					{
						$$->label = l;
					}
				}
				else $$ = NULL;
			}
			| variable PERIOD IDENTIFIER
			{
				if ($1 != NULL)
				{
					int l = $1->label;
					$$ = emit_record_field($1, $3);
					if ($$ != NULL)
					{
							$$->label = l;
					}
				}
				else $$ = NULL;
			}
			;

list_expression		: list_expression COMMA expression
			{
					stack_push($1, (int)$3);
					$$ = $1;
			}
			| expression
			{
				stack_t *s;
				s = stack_alloc();
				assert($1 != NULL);
				stack_push(s, (int)$1);
				$$ = s;
			}
			;
			
expression	: sexpr
			{
				$$ = $1;
			}
			| sexpr relop sexpr
			{
				if ($1 != NULL && $3 != NULL)
				{
					$$ = emit_relop($1, $3, $2);
				}
				else
				{
						if ($1 != NULL) expr_free($1);
						if ($3 != NULL) expr_free($3);
						$$ = NULL;
				}
			}
			;

relop			: EQUALS { $$ = OP_JEQ; }
			| NE { $$ = OP_JNE; }
			| GT { $$ = OP_JGT; }
			| LT { $$ = OP_JLT; }
			| GE { $$ = OP_JGE; }
			| LE { $$ = OP_JLE; }
			;
			
sexpr			: term
			{
				$$ = $1;
			}
			| sexpr PLUS term
			{
				if ($1 != NULL && $3 != NULL)
				{
					$$ = emit_plus($1, $3);
				}
				else
				{
						expr_free($1);
						expr_free($3);
						$$ = NULL;
				}
			}
			| sexpr MINUS term
			{
				if ($1 != NULL && $3 != NULL)
				{
					$$ = emit_minus($1, $3);
				}
				else
				{
						expr_free($1);
						expr_free($3);
						$$ = NULL;
				}
			}
			| sexpr K_OR term
			{
				if ($1 != NULL && $3 != NULL)
				{
					$$ = emit_or($1, $3);
				}
				else
				{
						expr_free($1);
						expr_free($3);
						$$ = NULL;
				}
			}
			;
			
term			: factor
			{
				$$ = $1;
			}
			| term TIMES factor
			{
				if ($1 != NULL && $3 != NULL)
				{
					$$ = emit_times($1, $3);
				}
				else
				{
						expr_free($1);
						expr_free($3);
						$$ = NULL;
				}
			}
			| term DIVIDE factor
			{
				if ($1 != NULL && $3 != NULL)
				{
					$$ = emit_divide($1, $3);
				}
				else
				{
						expr_free($1);
						expr_free($3);
						$$ = NULL;
				}
			}
			| term K_DIV factor
			{
				if ($1 != NULL && $3 != NULL)
				{
					$$ = emit_div($1, $3);
				}
				else
				{
						expr_free($1);
						expr_free($3);
						$$ = NULL;
				}
			}
			| term K_MOD factor
			{
				if ($1 != NULL && $3 != NULL)
				{
					$$ = emit_mod($1, $3);
				}
				else
				{
						expr_free($1);
						expr_free($3);
						$$ = NULL;
				}
			}
			| term K_AND factor
			{
				if ($1 != NULL && $3 != NULL)
				{
					$$ = emit_and($1, $3);
				}
				else
				{
						expr_free($1);
						expr_free($3);
						$$ = NULL;
				}
			}
			;

factor		: variable
			{
				$$ = $1;
			}
			| INTEGER
			{
				$$ = make_int_expr($1);
			}
			| STRING
			{
				if (strlen($1) == 1)
				{
					$$ = make_char_expr(*$1);
					free($1);
				}
				else
				{
					$$ = make_string_expr($1);
				}
			}
			| LPAREN expression RPAREN
			{
				$$ = $2;
			}
			| IDENTIFIER LPAREN list_expression RPAREN
			{
				$$ = emit_invoke($1, $3);
				if ($$ == NULL)
				{
					ERROR("Error invoking function.\n");
				}
			}
			| POS factor
			{
					$$ = $2;
			}
			| NEG factor
			{
					$$ = emit_neg($2);
			}
			| K_NOT factor
			{
				$$ = emit_not($2);
			}
			| LBRACKET list_element RBRACKET
			{
				$$ = NULL;
				ERROR("Set not supported.\n");
			}
			| K_TRUE
			{
				$$ = emit_true();
			}
			| K_FALSE
			{
				$$ = emit_false();
			}
			;

list_element		: list_element COMMA element
			| element
			;
element			: expression
			| subrange
			;	

statement		: unlabelled_statement
			{
				INFO("STATEMENT\n");
			}
			| label
			{
				emit_label($1);
			}
			COLON unlabelled_statement
			| error
			{
					yyok = 0;
			}
			;

unlabelled_statement	: variable IS expression
			{
				emit_assign($1, $3);
			}
			| K_READ LPAREN list_expression RPAREN
			{
				emit_read($3, 0);
			}
			| K_READLN
			{
				emit_read(NULL, 1);
			}
			| K_READLN LPAREN list_expression RPAREN
			{
				emit_read($3, 1);
			}
			| K_WRITE LPAREN list_expression RPAREN
			{
				emit_write($3, 0);
			}
			| K_WRITELN LPAREN list_expression RPAREN
			{
				emit_write($3, 1);
			}
			| IDENTIFIER LPAREN list_expression RPAREN
			{
				expression_t *e;
				e = emit_invoke($1, $3);
				if (e != NULL) expr_free(e);
			}
			| IDENTIFIER
			{
				expression_t *e;
				e = emit_invoke($1, NULL);
				if (e != NULL) expr_free(e);
			}
			| K_GOTO label
			{
				emit_goto($2);
			}
			| K_IF expression K_THEN 
			{
				$2 = make_bool($2);
				if (($2 == NULL) || ($2->type != bool_entry) 
					|| ($2->flag != EXPR_BOOL))
				{

					ERROR("invalid branch condition.\n");
					expr_free($2);
					$2 = NULL;
				}
				else
				{
					int label = new_label();
					EMIT_LABEL(label);
					if ($2->true_list != NULL)
					{
					patch_label($2->true_list, label);
					}
					
				}
			}
			statement
			{
				stack_push(proc_stack, (int)$2);
			}
			else_part
			| K_CASE expression K_OF list_case_list_element K_END
			{
				ERROR("Case statement supported.\n");
			}
			| K_WHILE 
			{
				int l = new_label();
				stack_push(record_stack, l);
				EMIT_LABEL(l);
			}
			expression
			{
				int l = new_label();
				$3 = make_bool($3);
				patch_label($3->true_list, l);
				EMIT_LABEL(l);
			}
			K_DO statement
			{
				int l = new_label();			
				EMIT(OP_JMP, LABEL_ARG(stack_pop(record_stack)),
							NULL_ARG, NULL_ARG);
				patch_label($3->false_list, l);
				EMIT_LABEL(l);
				expr_free($3);
			}
			| K_REPEAT
			{
				int l = new_label();
				stack_push(record_stack, l);
				EMIT_LABEL(l);
			}
			list_statement K_UNTIL expression
			{
				int l = new_label();
				$5 = make_bool($5);
				patch_label($5->false_list,
						stack_pop(record_stack));
				patch_label($5->true_list, l);
				EMIT_LABEL(l);
				expr_free($5);
			}
			| K_FOR variable IS expression K_TO expression K_DO
			{
				int l = new_label();
				int m = new_label();
				emit_assign(expr_copy($2), $4);
				EMIT_LABEL(l);
				$4 = emit_relop(expr_copy($2), $6, OP_JLE);	
				EMIT_LABEL(m);
				patch_label($4->true_list, m);
				$6 = (expression_t *)l;
			}
			statement
			{
				int l = new_label();
				expression_t *e = make_int_expr(1);
				emit_assign($2, emit_plus(expr_copy($2), e));
				EMIT(OP_JMP, LABEL_ARG((int)$6), NULL_ARG,
						NULL_ARG);
				EMIT_LABEL(l);
				patch_label($4->false_list, l);
				expr_free($4);
			}
			| K_FOR variable IS expression K_DOWNTO expression K_DO
			{
				int l = new_label();
				int m = new_label();
				emit_assign(expr_copy($2), $4);
				EMIT_LABEL(l);
				$4 = emit_relop(expr_copy($2), $6, OP_JGE);	
				EMIT_LABEL(m);
				patch_label($4->true_list, m);
				$6 = (expression_t *)l;
			}
		       	statement
			{
				int l = new_label();
				expression_t *e = make_int_expr(1);
				emit_assign($2, emit_minus(expr_copy($2), e));
				EMIT(OP_JMP, LABEL_ARG((int)$6), NULL_ARG,
						NULL_ARG);
				EMIT_LABEL(l);
				patch_label($4->false_list, l);
				expr_free($4);
			}
			| K_WITH variable K_DO statement
			{
				ERROR("With statement not supported.\n");
			}
			| compound_statement
			;

else_part		: K_ELSE 
			{
				int label = new_label();
				expression_t *c = (expression_t *)stack_pop(proc_stack);
				stack_push(record_stack, label);
				EMIT(OP_JMP, LABEL_ARG(label), NULL_ARG,
						NULL_ARG);
				if (c != NULL && c->false_list != NULL)
				{
					label = new_label();
					EMIT_LABEL(label);
					patch_label(c->false_list, label);
				}
				expr_free(c);
			}
			statement
			{
				EMIT_LABEL(stack_pop(record_stack));
			}
			|
			{
				int label;
				expression_t *c = (expression_t *)stack_pop(proc_stack);
				if (c != NULL && c->false_list != NULL)
				{
					label = new_label();
					EMIT_LABEL(label);
					patch_label(c->false_list, label);
				}
				expr_free(c);				
			}
			;
		
compound_statement	: K_BEGIN 
			{
				INFO("BEGIN\n");
			}
			list_statement K_END
			{
				INFO("END\n");
			}
			;
			
list_statement	:
			| real_list_statement scolon_or_none
			;

			
scolon_or_none :
			| SCOLON
			;
			
real_list_statement: statement
			| real_list_statement SCOLON statement
			;

list_case_list_element	: list_case_list_element SCOLON case_list_element
			| case_list_element
			;

case_list_element	: list_expression COLON statement	
			{
				assert(0);
			}
			;

list_identifier		: list_identifier COMMA IDENTIFIER
			{
				enqueue($1, $3);
				$$ = $1;
			}
			| IDENTIFIER
			{
				queue_t *tmp = queue_alloc();
				enqueue(tmp, $1);
				$$ = tmp;
				INFO("%s\n", $1);
			}
			;

%%

extern char *yytext;
int yyerror (char *msg)
{
	ERROR("%s near `%s\'\n", msg, yytext);
	return 0;
}

