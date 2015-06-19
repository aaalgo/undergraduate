/* filename: expr.c
   by Dong Wei */
#include <config.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <libtype.h>
#include <expr.h>

expr_t *expr_create (void)
{
	expr_t *expr;
	expr = (expr_t *)malloc(sizeof(expr_t));
	assert(expr != NULL);
/*	if (expr == NULL) return NULL; */
#if 0
	expr->result = 0;
	expr->presult = NOPATCH;
	expr->tresult = NULL;
#endif
	expr->nopr = 0;
	expr->sopr = 0;
	expr->opr = NULL;
#ifdef MANAGE_CONST
	expr->sbuf = 0;
	expr->bufend = 0;
	expr->buf = NULL;
#endif
	return expr;
}
/*
expr_t *expr_create_true (void)
{
	int i = TRUE;
	expr_t *expr = CreateExpr();
	if (expr == NULL) return NULL;
	expr->result = AppendConst(expr, sizeof(int), &i);
	expr->presult= NOPATCH;
	return expr;
}
*/
void expr_destroy (expr_t *expr)
{
	assert(expr != NULL);
	free(expr->opr);
#ifdef MANAGE_CONST
	free(expr->buf);
#endif
	free(expr);
}

int expr_preevaluate (expr_t *expr)
{
	int i;
	func_t *func;
	assert(expr != NULL);
	for (i = 0; i < expr->nopr; i++)
	{
/*		for (j = 0; j < 3; j++)
		{
			if (expr->opr[i].data[j].patch == NOPATCH)
			{
				expr->opr[i].data[j].addr += (unsigned)expr->buf;
			}
		}*/
		func = func_from_id(expr->opr[i].func_id);
		assert(func != NULL);
		expr->opr[i].func = func->func;
	}
#if 0
	if (expr->presult == NOPATCH)
	{
			expr->result += (unsigned)expr->buf;
	}
	expr->tresult = type_from_id(expr->tresult_id);
	assert(expr->tresult != NULL);
#endif
	return 0;
}

/* always remember to patch an expression before evaluate it */
int expr_evaluate (expr_t *expr)
{
	int i;
/*	assert(expr != NULL && result != NULL);*/
	for (i = 0; i < expr->nopr; i++)
	{
		expr->opr[i].func(expr->opr[i].data[0].addr,
				expr->opr[i].data[1].addr,
				expr->opr[i].data[2].addr);
	}
#if 0
	*result = expr->result;
#endif
	return 0;
}

#ifdef MANAGE_CONST
void *expr_append_const (expr_t *expr, size_t size, void *buf)
{
	void *res;
	assert(expr != NULL);
	if (expr->bufend + size >= expr->sbuf)
	{
			for (;;)
			{
					expr->sbuf += BUF_INC;
					if (expr->bufend + size < expr->sbuf) break;
			}
			expr->buf = (char *)realloc(expr->buf, expr->sbuf);
			assert(expr->buf != NULL);
	}
	if (buf != NULL)
	{
		memcpy(expr->buf + expr->bufend, buf, size);
	}
	res = (void *)expr->bufend;
	expr->bufend += size;
	return res;
}
#endif

int expr_append_opr (expr_t *expr, int func,
				void *result,
				void *opr1,
				void *opr2,
				int presult,
				int popr1,
				int popr2)
{
	int nopr;
	assert(expr != NULL && func != 0);
	nopr = expr->nopr;
	if (nopr >= expr->sopr)
	{
			expr->sopr += OPR_INC;
			expr->opr = (opr_t *)realloc(expr->opr, expr->sopr * sizeof(opr_t));
	}
	expr->opr[nopr].func_id = func;
	expr->opr[nopr].data[0].addr = result;
	expr->opr[nopr].data[1].addr = opr1;
	expr->opr[nopr].data[2].addr = opr2;
	expr->opr[nopr].data[0].patch = presult;
	expr->opr[nopr].data[1].patch = popr1;
	expr->opr[nopr].data[2].patch = popr2;
	expr->nopr++;
	return 0;
}

int expr_patch (expr_t *expr, void *old[], void *new[])
{
	int i, j, p;
	pdpair_t *pd;
	assert(expr != NULL);
	for (i = 0; i < expr->nopr; i++)
	{
		pd = expr->opr[i].data;
		for (j = 0; j < 3; j++)
		{
			p = pd[j].patch;
			if (p >= 0)
			{
				(char *)(pd[j].addr)
					+= (unsigned)new[p] - (unsigned)old[p];
			}
		}
	}
	if (expr->presult >= 0)
	{
		(char *)expr->result += (unsigned)new[expr->presult]
		       	- (unsigned)old[expr->presult];
	}
	return 0;
}

int expr_set_result (expr_t *expr, void *result, int patch, type_t *type)
{
	assert(expr != NULL);
	expr->result = result;
	expr->presult = patch;
	expr->tresult = type;
	return 0;
}
