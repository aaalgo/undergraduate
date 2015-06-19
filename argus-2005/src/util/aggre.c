#include <argus.h>

int *int_sum_init (void)
/* also used as count_init */
{
	int *i = type_alloc(int);
	*i = 0;
	return i;
}

void int_sum_update (int *i, int *j, int flag)
{
	if (flag == TUPLE_INS)
	{
		*i += *j;
	}
	else if (flag == TUPLE_DEL)
	{
		*i -= *j;
	}
}

void int_sum_value (int *i, int *j)
{
	*j = *i;
}

void int_sum_free (int *i)
{
	free(i);
}

float *float_sum_init (void)
{
	float *i = type_alloc(float);
	*i = 0.0;
	return i;
}

void float_sum_update (float *i, float *j, int flag)
{
	if (flag == TUPLE_INS)
	{
		*i += *j;
	}
	else if (flag == TUPLE_DEL)
	{
		*i -= *j;
	}
}

void float_sum_value (float *i, float *j)
{
	*j = *i;
}

void float_sum_free (float *i)
{
	free(i);
}


/* count_init is int_sum_init */
void count_update (int *i, void *p, int flag)
{
	if (flag == TUPLE_INS) (*i)++;
	else if (flag == TUPLE_DEL) (*i)--;
}

void count_value (int *i, int *j)
{
	*j = *i;
}

/* count_free is int_sum_free */


aggre_t aggre[] =
	{{TYPE_VOID, TYPE_INT,
		(aggre_init_f)int_sum_init,
		(aggre_update_f)count_update,
		(aggre_value_f)int_sum_value,
		(aggre_cleanup_f)int_sum_free,
	 	"count"},
	{TYPE_INT, TYPE_INT,
		(aggre_init_f)int_sum_init,
		(aggre_update_f)int_sum_update,
		(aggre_value_f)int_sum_value,
		(aggre_cleanup_f)int_sum_free,
		"sum"},
	{TYPE_VOID, TYPE_VOID, NULL, NULL, NULL, NULL, ""}};

aggre_t *aggre_load (char *name, type_t *itype)
{
	int i = 0;
	for (;;)
	{
		if (aggre[i].otype == TYPE_VOID) return NULL;
		if (strcmp(aggre[i].name, name) == 0)
		{
			if (aggre[i].itype == TYPE_VOID) return &aggre[i];
			if (aggre[i].itype == itype) return &aggre[i];
		}
		i++;
	}
}

int is_aggre (char *name)
{
	int i = 0;
	for (;;)
	{
		if (aggre[i].otype == TYPE_VOID) return 0;
		if (strcmp(aggre[i].name, name) == 0) return 1;
		i++;
	}
	return 0;
}
