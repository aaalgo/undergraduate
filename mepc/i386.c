/**
  * \file i386.c
  * \author Dong Wei
  *
  * The i386 assembly code generating functions.
  */
#include "pascal.h"
#define MAX_STACK 2048

char avail[MAX_STACK];	/* available memory space */
int temp_num;	/* number of temperary variable */
instruct_t **last;/* where the temparary variable last appears */
int *size;	/* size of temp */
int *offset;	/* offset of the variable */

int last_avail;	/* the last available memory space */
int stack;
stack_t *param_count; /* count the size of parameters */
instruct_t *ip;	/* current instruction */

/// Initializing process before code generation.
static void preproc (void)
{
	instruct_t *endp;
	int i, j, s;
	temp_num = 0;
	for (endp = ip; endp->op != OP_ENDP; endp++)
	{
		if (endp->op == OP_TEMP)
			if (endp->arg[0].temp > temp_num)
				temp_num = endp->arg[0].temp;
	}
	temp_num++;
	last = (instruct_t **)malloc(temp_num * sizeof(instruct_t *));
	assert(last != NULL);
	size = (int *)malloc(temp_num * sizeof(int));
	assert(size != NULL);
	offset = (int *)malloc(temp_num * sizeof(int));
	assert(offset != NULL);

	memset(offset, 0xff, temp_num * sizeof(int));
	offset[0] = 0;
	
	for (endp = ip; endp->op != OP_ENDP; endp++)
	{
		for (i = 0; i < 3; i++)
			if (endp->arg[i].flag == ARG_STACK)
			{
				last[endp->arg[i].temp] = endp;
			}		
	}
	memset(avail, 0, sizeof avail);
	last_avail = 0;
}
/// Cleaning up work after code generation.
static void postproc (void)
{
	free(last);
	free(offset);
	free(size);
}

int name;

static int alloc_temp (int s)
{
	int i, j, ret;
/*	printf("%d\n", s);
	assert(s <= 8);*/
	s = (s+3) / 4;
	for (i = 0; i < last_avail; i++)
	{
	/*		if (avail[i]) continue;
		if (s > 4 && avail[i+1]) continue; */
		for (j = 0; j < s; j++)
		{
				if (avail[i+j]) break;
		}
		if (j >= s) break;
	}
	/* must be ok */
	ret = - (i << 2) - (s << 2) - stack;
	for (j = 0; j < s; j++)
		avail[i++] = 1;
	if (i >= last_avail) last_avail = i;
	return ret;
}

static void clear_temp (void)
{
	int i, j, k, l, m;
	for (i = 0; i < 3; i++)
		if ((ip->arg[i].flag == ARG_STACK)
			&& (ip->arg[i].temp > 0)
			&& (last[ip->arg[i].temp] <= ip))
		{
			k = ip->arg[i].temp;
			j = offset[k];
			j += (size[k]+3) & ~3 + stack;
			j = -j;
			j = j >> 2;
			l = size[k];
			l = (l+3)/4;
			for (m = 0; m < l; m++)
				avail[j+m] = 0;
		}
}


#include "opcode.i386"
#include "opcode.inc"
static void gen_proc (void)
{
	preproc();
	for (;;)
	{
		gen_code[ip->op]();
		clear_temp();
		if (ip->op == OP_ENDP) break;
		ip++;
	}
	postproc();
	ip++;
}

/// The code generating function.
void i386_codegen (void)
{
	char *s;
	int i;
	ip = text->data;
	ip++;
	GEN("global main\n");
	for (;;)
	{
		s = dequeue(external);
		if (s == NULL) break;		
		GEN("extern %s\n", s);
		free(s);
	}
	GEN("\nsection .data\n");
	for (;;)
	{
		s = dequeue(string_const_queue);
		if (s == NULL) break;
		i = (int)hash_lookup(string_const, s);	
		assert(i > 0);
		GEN("gl#%d\tdb ", i);
		print_asm_string(output, s);
	}
	GEN("\nsection .code\n");
	GEN("main:\tpush ebp\n");
	GEN("\t;invoke %s\n", title);
	GEN("\tcall pp#1\n");
	GEN("\tpop ebp\n");
	GEN("\tret\n\n");
	param_count = stack_alloc();
	stack_push(param_count, 0);
	for (;;)
	{
		if (ip->op == OP_END) break;
		assert(ip->op == OP_PROC);
		gen_proc();	
	}
	stack_pop(param_count);
	stack_free(param_count);
}


void i386_optimize (void)
{
}
