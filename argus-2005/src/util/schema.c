#include <argus.h>

int fix_schema (schema_t *sch)
{
	int ofs, i;
	type_t *type;
	ofs = 0;
	for (i = 0; i < sch->nof; i++)
	{
		type = sch->field[i].type;
		assert(type != NULL);
		sch->field[i].offset = ofs;
		ofs += type->size;
	}
	return 0;
}

int schema_field (schema_t *s, char *name)
{
	int i;
	for (i = 0; i < s->nof; i++)
		if (strcmp(s->field[i].name, name) == 0) return i;
	return -1;
}

