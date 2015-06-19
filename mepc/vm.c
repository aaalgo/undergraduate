/* filename: vm.c
   by Dong Wei */
#include "pascal.h"

int vm_label = 1, vm_temp = 1, vm_global = 1, vm_proc = 1;


void vm_optimize (void)
{
}

static void gen_arg (arg_t *arg)
{
	if (arg->flag == 0) return;
	switch (arg->flag)
	{
		case ARG_LABEL: fprintf(output, "\t#%d",
				arg->offset);
				break;
		case ARG_STACK: fprintf(output, "\t$%d", arg->temp);
				if (arg->offset != 0)
					fprintf(output, "[%d]", arg->offset);
				break;
		case ARG_GLOBAL: fprintf(output, "\t@%d", arg->temp);
				 if (arg->offset != 0)
					 fprintf(output, "[%d]", arg->offset);
		case ARG_CONST: fprintf(output, "\t%d", arg->offset);
				break;
		case ARG_SYMBOL: fprintf(output, "\t%s",
				(char *)arg->offset);
				break;
		case ARG_REAL	: fprintf(output, "\t%g", 
					((r_arg_t *)arg)->real);
				break;
		default: fprintf(output, "\tERROR(%d)", arg->flag);
	}
}

void vm_codegen (void)
{
	int i, j;
	instruct_t *ins;
	char *s;
	INFO("Generating code.\n");
	for (;;)
	{
		s = dequeue(external);
		if (s == NULL) break;
		fprintf(output, "extern %s\n", s);
		free(s);
	}
	for (j = 0; j < text->last; j++)
	{
		ins = text->data + j;
		fprintf(output, "%-4d %s", j, opcode_symbol[ins->op]);
/*		ins->arg[0] = ins->arg[0];		
		ins->arg[1] = ins->arg[1];
		ins->arg[2] = ins->arg[2];*/
		gen_arg(&(ins->arg[0]));
		gen_arg(&(ins->arg[1]));
		gen_arg(&(ins->arg[2]));
		fprintf(output, "\n");
	}
}

void print_asm_string (FILE *f, char *c)
{
	char *t = c;
	for (;;)
	{
		if (*t == 0) break;
		fprintf(f, "%d, ", *t);
		t++;
	}
	fprintf(f, "0\n");
}

