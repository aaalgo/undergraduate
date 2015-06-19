#include <config.h>
#include <assert.h>
#include <stdlib.h>
#include <libtype.h>
#include <stdio.h>
#include <cmnhdr.h>
#include <schema.h>

#define TLIST_INC	0x10
#define FLIST_INC	0x10
#define BUF_SIZE 128

/* number of type, func registered */
static int ntype, nfunc;
/* size of the lists */
static int stype, sfunc;
static type_t **tlist;
static func_t **flist;
/*
static void **dllist;
*/

#ifdef LIBTYPE_REFLECT
#include <reflect.h>
#include <schema.h>
static schema_fix_t type_schema = {3, 
					{{0, "id", TYPE_INT, sizeof(int), 0},
					{1, "name", TYPE_STRING32, MAX_ID_LEN, sizeof(int)},
				   	{2, "size", TYPE_INT, sizeof(int), sizeof(int)+MAX_ID_LEN}}};
static schema_fix_t func_schema = {5,
					{{0, "id", TYPE_INT, sizeof(int), 0},
					{1, "name", TYPE_STRING32, MAX_ID_LEN, sizeof(int)},
					{2, "result", TYPE_PCHAR, sizeof(char *), MAX_ID_LEN + sizeof(int)},
					{3, "param1", TYPE_PCHAR, sizeof(char *), MAX_ID_LEN + sizeof(int)+sizeof(char *)},
					{4, "param2", TYPE_PCHAR, sizeof(char *), MAX_ID_LEN + sizeof(int)+sizeof(char *)*2}}};

int register_type_reflect ()
{
		table_register(TABLE_PARRAY|TABLE_SYSTEM, "@type", (schema_t*)&type_schema, tlist, &ntype, sizeof(type_t *));
		table_register(TABLE_PARRAY|TABLE_SYSTEM, "@func", (schema_t*)&func_schema, flist, &nfunc, sizeof(func_t *));
		return 0;
}
		

#endif
/*
static type_t type_void = {0, "void", 0, NULL, NULL, NULL, NULL};
*/
int type_init (void)
{
		stype = TLIST_INC;
		sfunc = FLIST_INC;
		tlist = type_calloc(stype, type_t *);
		flist = type_calloc(sfunc, func_t *);
		ntype = nfunc = 0;
/*		type_register(&type_void);*/
		return 0;
}

int type_cleanup (void)
{
		free(flist);
		free(tlist);
		flist = NULL;
		tlist = NULL;
		stype = sfunc = ntype = nfunc = 0;
		return 0;
}

int type_register (type_t *type)
{
		int i;
		for (i = 0; i < ntype; i++)
			if (strcmp(tlist[i]->name, type->name) == 0) return -1;
		if (ntype == stype)
		{
				stype += TLIST_INC;
				tlist = type_realloc(tlist, stype, type_t *);
		}
		tlist[ntype] = type;
		ntype++;
		return 0;
}

int func_register (func_t *func)
{
		int i;
		for (i = 0; i < nfunc; i++)
			if (strcmp(flist[i]->name, func->name) == 0 &&
				flist[i]->param1 == func->param1 &&
				flist[i]->param2 == func->param2) return -1;
		if (nfunc == sfunc)
		{
				sfunc += FLIST_INC;
				flist = type_realloc(flist, sfunc, func_t *);
		}
/*		func->tresult = func->result->name;
		func->tparam1 = func->param1->name;
		func->tparam2 = func->param2->name;*/
		flist[nfunc] = func;
		nfunc++;
		return 0;
}

type_t *type_load (char *name)
{
		int i;
		for (i = 0; i < ntype; i++)
			if (strcmp(tlist[i]->name, name) == 0)
			{
					return tlist[i];
			}
		fprintf(stderr, "Type \'%s\' not found.\n", name);
		return NULL;
}

int type_load_id (char *name)
{
		type_t *t = type_load(name);
		if (t == NULL) return -1;
		return t->id;
}

type_t *type_from_id (int id)
{
		int i;
		for (i = 0; i < ntype; i++)
				if (tlist[i] != NULL)
				if (tlist[i]->id == id) return tlist[i];
		assert(0);
		return NULL;
}

func_t *func_load (char *name, type_t *param1, type_t *param2)
{
	int i;
	for (i = 0; i < nfunc; i++)
	if (strcmp(flist[i]->name, name) == 0
		&& flist[i]->param1 == param1
		&& flist[i]->param2 == param2)
	{
		return  flist[i];
	}
	fprintf(stderr, "Function \'%s\' not found.\n", name);
	return NULL;
}

int func_load_id (char *name, type_t *param1, type_t *param2)
{
		func_t *f = func_load(name, param1, param2);
		if (f == NULL) return -1;
		return f->id;
}

func_t *func_from_id (int id)
{
	int i;
	for (i = 0; i < nfunc; i++)
		if (flist[i]->id == id) return flist[i];
	return NULL;
}

