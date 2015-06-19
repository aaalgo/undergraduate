/* filename: hash.c
   by Dong Wei */

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

/* a most simple hash function */

int hash_fun (char *name)
{
	int ret = 0;
	while (*name)
	{
		ret <<= 1;
		ret += 	*name;
		name++;
	}
	return ret;
}


void hash_destroy (hash_t *hash)
{
	int i;
	hash_entry_t *tmp1, *tmp2, *tmp3;
	assert(hash != NULL);
	for (i = 0; i < hash->size; i++)
	{
		tmp1 = hash->entries[i];
		while (tmp1 != NULL)
		{
			tmp2 = tmp1;
			tmp1 = tmp1->link;
			while (tmp2 != NULL)
			{
				tmp3 = tmp2;
				tmp2 = tmp2->next;
				if ((hash->flag & HASH_STRDUP) != 0)
				{
					free(tmp3->name);
				}
				free(tmp3);
			}
		}
	}
	free(hash->entries);
}

void hash_insert (hash_t *hash, char *name, void *data)
{
	hash_entry_t *entry;
	hash_entry_t **tmp;
	int i;
	entry = malloc(sizeof (hash_entry_t));
	assert(entry != NULL);
	if ((hash->flag & HASH_STRDUP) != 0)
	{
		entry->name = strdup(name);
	}
	else
	{
		entry->name = name;
	}
	entry->data = data;
	entry->link = entry->next = NULL;
	i = hash_fun(name) % hash->size;
	tmp = &(hash->entries[i]);
	/* search the bucket */
	while (*tmp)
	{
		if (strcmp((*tmp)->name, name) == 0)
		{
			entry->next = *tmp;
			entry->link = (*tmp)->link;
			*tmp = entry;
			return;
		}
		tmp = &((*tmp)->link);
	}
	*tmp = entry;
}

void hash_remove (hash_t *hash, char *name)
{
	int i;
	hash_entry_t **tmp, *entry;
	i = hash_fun(name) % hash->size;
	tmp = &(hash->entries[i]);
	for (;;)
	{
		assert(*tmp != NULL);
		if (strcmp((*tmp)->name, name) == 0)
		{
			entry = *tmp;
			*tmp = (*tmp)->next;
			break;
		}
		tmp = &((*tmp)->link);
	}
	free(entry);
}

void *hash_lookup (hash_t *hash, char *name)
{
	int i;
	hash_entry_t **tmp, *entry;
	assert(hash != NULL);
	i = hash_fun(name) % hash->size;
	tmp = &(hash->entries[i]);
	for (;;)
	{
		if (0 == *tmp) return NULL;
		if (strcmp((*tmp)->name, name) == 0)
		{
			return (*tmp)->data;
		}
		tmp = &((*tmp)->link);
	}
}

/* dump the hash table, used in debugging */
void hash_dump (hash_t *hash, int detail)
{
	int i, cnt, entry;
	hash_entry_t *tmp1, *tmp2, *tmp3;
	assert(hash != NULL);
	cnt = 0;
	entry = 0;
	for (i = 0; i < hash->size; i++)
	{
		if (hash->entries[i] == NULL) continue;
		cnt++;
		tmp1 = hash->entries[i];
		while (tmp1 != NULL)
		{
			tmp2 = tmp1;
			tmp1 = tmp1->link;
			while (tmp2 != NULL)
			{
				tmp3 = tmp2;
				tmp2 = tmp2->next;
				if (detail)
				{
					printf("%d %s\n", tmp3->data, tmp3->name);
				}
				entry++;
			}
		}
	}
	printf("\n%d buckets out of %d are used.\n", cnt, hash->size);
	printf("%d entries in all.\n", entry);
}

