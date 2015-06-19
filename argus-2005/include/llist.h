#ifndef __ARGUS_LINKLIST__
#define __ARGUS_LINKLIST__

/* To declare a linked list, use the following declaration:
 * 	lnode_t list
 * when the function may modify the list, pass &list
 * otherwise, pass list
 */

typedef struct __lnode lnode_t;

/* to declare a linked list node, lnode_t must be the first field */
struct __lnode
{
	lnode_t *next;
};

static __inline void llist_init (lnode_t *head)
{
	head->next = NULL;
};

static __inline void *llist_next (lnode_t node)
{
	return node.next;
};

static __inline int llist_empty (lnode_t head)
{
	return head.next == NULL;
}

void llist_append (lnode_t *list, void *);
int llist_count (lnode_t list);
/* You should not use llist_free_lazy when you have dynamic allocated fields in the list node */
void llist_free_lazy (lnode_t *list);

#endif
