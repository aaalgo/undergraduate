/* filename: table.c
   by Dong Wei */
#include "pascal.h"

/* definition of some bigger functions for table.h */

void table_destroy (table_t *table)
{
	entry_t *entry, *tmp;
	assert(table != NULL);
	entry = table->entries;
	while (entry != NULL)
	{
		tmp = entry;
		entry = entry->next;
		entry_free(tmp);
	}
	if (table->hash != NULL)
		hash_free(table->hash);
}

void table_append (table_t *table, entry_t *entry)
{
	assert(table != NULL && entry != NULL);
	entry->next = table->entries;
	table->entries = entry;
	if (entry->type == ENTRY_LABEL)
		assert(entry->a.label.label == 0);
	if (table->hash != NULL && entry->name != NULL)
		hash_insert(table->hash, entry->name, entry);
}

entry_t *table_lookup (table_t *table, char *name)
{
	entry_t *tmp;
	assert(table != NULL && name != NULL);
	if (table->hash != NULL)
	{
		return hash_lookup(table->hash, name);
	}
	tmp = table->entries;
	while (tmp != NULL)
	{
		if (strcmp(tmp->name, name) == 0) return tmp;
		tmp = tmp->next;
	}
	return NULL;
}


table_t *table_stack_grow (table_stack_t *stack)
{
	table_t *table;
	assert(stack != NULL);
	table = table_alloc(TABLE_HASH);
	table->next = stack->tables;
	stack->tables = table;
	return table;
}

void table_stack_push (table_stack_t *stack, table_t *table)
{
	assert(stack != NULL && table != NULL);
	table->next = stack->tables;
	stack->tables = table;
}

void table_stack_destroy (table_stack_t *stack)
{
	table_t *tmp1, *tmp2;
	assert(stack != NULL);
	tmp1 = stack->tables;
	while (tmp1 != NULL)
	{
		tmp2 = tmp1;
		tmp1 = tmp1->next;
		table_free(tmp2);
	}
}

void table_stack_hash_append (table_stack_t *t, entry_t *e)
{
	assert(t != NULL && e != NULL);
	assert(e->name != NULL);
	hash_insert(t->tables->hash, e->name, e);
}

