#include <stdlib.h>
#include <llist.h>

void llist_append (lnode_t *list, void *__node)
{
	lnode_t *node = (lnode_t *)__node;
	while (list->next != NULL) list = list->next;
	list->next = node;
	node->next = NULL;
}

int llist_count (lnode_t list)
{
	int c = 0;
	lnode_t *l = list.next;
	while (l != NULL)
	{
		c++;
		l = l->next;
	}
	return c;
}

void llist_free_lazy (lnode_t *list)
{
	lnode_t *l;
	l = list->next;
	list->next = NULL;
	while (l != NULL)
	{
		list = l;
		l = list->next;
		free(list);
	}
}

