/**
 * \file schema.h
 * \author Dong Wei
 * \brief Definitions related to schema manipulation.
 */

#ifndef __DSMS_SCHEMA__
#define __DSMS_SCHEMA__
#ifndef __ARGUS_CLIENT__
#include <libtype.h>
#endif
/** Field descriptor. */
typedef struct
{
	char name[MAX_ID_LEN];
	type_t *type;
	/** Offset in record. */
	int offset;
} field_t;

/** Schema descriptor. */
typedef struct
{
	/** Number of fields. */
	int nof;
	/** A list of field descriptors. */
	field_t field[1];
} schema_t;

typedef struct
{
		int nof;
		field_t field[MAX_STATIC_FIELD];
} schema_fix_t;

static __inline schema_t *schema_alloc (int nof)
{
	return (schema_t *)xmalloc(sizeof(schema_t) + (nof-1) * sizeof(field_t));
}

static __inline int schema_size (schema_t *s)
{
		return sizeof(schema_t) + (s->nof-1) * sizeof(field_t);
}

static __inline int schema_data_size (schema_t *s)
{
		int i, t = 0;
		for (i = 0; i < s->nof; i++)
				t += s->field[i].type->size;
		return t;
}

static __inline int schema_extra_size (schema_t *s)
{
		return (s->nof-1) * sizeof(field_t);
}

static __inline schema_t *schema_dup (schema_t *s)
{
		int c = schema_size(s);
		schema_t *t = (schema_t *)xmalloc(c);
		memcpy(t, s, c);
		return t;
}

static __inline void schema_dump (schema_t *s)
{
		int i;
		for (i = 0; i < s->nof; i++)
		{
				printf("%4d:\t%s\t%s\n", i, s->field[i].type->name, s->field[i].name);
		}
}

int fix_schema (schema_t *);

int schema_field (schema_t *, char *);

#endif
