/**
 * \file table.h
 * \author Dong Wei
 *
 * Functions and structures used in symbol table management.
 * Three types are used here:
 *	entry_t		entries used in the table, see into entry.h for details
 *	table_t		everything has a name defined in a procedure are
 *			saved in a table
 *	table_stack_t	a table stack is used to describe the nesting of
 *			procedures. The top of the stack is the table
 *			containing symbols defined in the most inside procedure.
 *			When a new procedure begins, the stack grows by
 *			a table, and when the definition of the procedure
 *			ends, the topmost table is poped and freed.
 *	
 *	Better not access table_t's by calling table functions,
 *	but do all these by calling table_stack functions.
 */


#ifndef __PASCAL_TABLE__
#define __PASCAL_TABLE__

struct entry;
/// The entry type (stuct entry).
typedef struct entry entry_t;
struct table;
/// The table type (struct table).
typedef struct table table_t;
struct table_stack;
/// The table stack type (struc table_stack).
typedef struct table_stack table_stack_t;

/// The table structure.
struct table
{
	/// Next table in the table stack.
	table_t *next;
	/// Entries of the table.
	entry_t *entries;
	/// Hash of the entry names.
	hash_t *hash;
	/// Reference count.
	/** when table are dynamically allocated, used to keep the
	  * reference count, and the table is released when ref == 0
	  */
	int ref;
	int extra;
};

#define TABLE_HASH 1
/// Initializing a table
/** If flag == TABLE_HASH, then the table keep a hash table
  * which may improve the efficient of searching symbols in the table;
  * otherwize, just pass 0. */
static inline void table_init (table_t *table, int flag)
{
	assert(table != NULL);
	table->next = NULL;
	table->entries = NULL;
/*	table->stack = NULL;*/
	table->extra = 0;
	table->hash = NULL;
	if (flag & TABLE_HASH)
	{
		table->hash = hash_alloc(0, 0);
	}
}

/// Allocate a table and initialize it; flag having the same meaning as above.
static inline table_t * table_alloc (int flag)
{
	table_t *table = (table_t *)malloc(sizeof (table_t));
	assert(table != NULL);
	table_init(table, flag);
	table->ref = 1;
	return table;
}
/// Destroy a table (without freeing it).
/**
  * \param table The table to destroy.
  * The memory taken by the table is not freed.
  */
void table_destroy (table_t *table);
/// Destroy and free a table.
/**
  * \param table The table to free.
  */
static inline void table_free (table_t *table)
{
	assert(table != NULL);
	table->ref --;
	if (table->ref == 0)
	{
		table_destroy(table);
		free(table);
	}
}
/// Append an entry to a table.
/**
  * \param table The to append to.
  * \param entry The entry to append.
  */
void table_append (table_t *table, entry_t *entry);

/// Append an entry to (the topmost table of) a table stack.
/**
  * \param t The table stack to append to.
  * \param e The entry to append.
  */
void table_stack_hash_append (table_stack_t *t, entry_t *e);
/// Search a table for an entry with the given name.
/**
  * \result The entry found, or NULL if failed.
  */
entry_t *table_lookup (table_t *table, char *name);

struct table_stack
{
	table_t *tables;
};

/// Initialize a table stack.
static inline void table_stack_init (table_stack_t *stack)
{
	assert(stack != NULL);
	stack->tables = NULL;
}

/// Allocate a table stack and initialize it.
table_t *table_stack_grow (table_stack_t *stack);

/// Push a table to a stack.
/** maybe useful when implementing the
  * 'with' statement in the Pascal language.
  */
void table_stack_push (table_stack_t *stack, table_t *table);

/// Get the top table of a symbol stack.
/**
  * \param The symbol stack.
  * \result The table at the top of the stack.
  */
static inline table_t *table_stack_top (table_stack_t *stack)
{
	assert(stack != NULL);
	return stack->tables;
}

/// Pop frees the table that is poped.
static inline void table_stack_pop (table_stack_t *stack)
{
	table_t *tmp;
	assert(stack != NULL);
	tmp = stack->tables;
	assert(tmp != NULL);
	stack->tables = tmp->next;
	table_free(tmp);
}

/// Destroy a symbol table stack.
void table_stack_destroy (table_stack_t *stack);

/// Allocate a symbol table stack.
static inline table_stack_t *table_stack_alloc (void)
{
	table_stack_t *stack = malloc(sizeof(table_stack_t));
	assert(stack != NULL);
	table_stack_init(stack);
	return stack;
}

/// Free a table stack.
static inline void table_stack_free (table_stack_t *stack)
{
	assert(stack != NULL);
	table_stack_destroy(stack);
	free(stack);
}

/// Append an entry to the top table of the stack.
/**
  * \param stack The table stack to be appended to.
  * \param entry The entry to append.
  */
static inline void table_stack_append (table_stack_t *stack, entry_t *entry)
{
	assert(stack != NULL && entry != NULL);
	table_append(stack->tables, entry);
}

/// Look up a symbol in the stack, and return the coresponding entry.
 /*
  * If the address of an integer variable is passed as level,
  * then the lavel of table containing the symbol is filled.
  * level 0 referes to the top of the stack, 1 the next and so on.
  * When nothing found, NULL is returned and level is not defined.
  * \param stack The stack to search.
  * \param name The name to search for.
  * \param level When the entry is found, *level is set to the level
  * of the table containing the entry in the symbol table stack.
  * \result The entry found.
  */
static inline entry_t *table_stack_lookup (table_stack_t *stack, char *name,
	int *level)
{
	table_t *tmp;
	entry_t *ret = NULL;
	int l = 0;
	assert(stack != NULL && name != NULL);
	tmp = stack->tables;
	while (tmp != NULL)
	{
		ret = table_lookup(tmp, name);
		if (ret != NULL) break;
		l++;
		tmp = tmp->next;
	}
	if (level != NULL) *level = l;
	return ret;
}

/// look up a symbol in the topmost table of the stack
/** \param stack The table stack to lookinto.
  * \param name The name to search for.
  * \result The entry of the name, NULL if nothing found.
  */
static inline entry_t *table_stack_lookup_top (table_stack_t *stack, char *name)
{
	assert(stack != NULL);
	if (name == NULL) return NULL;
	if (stack->tables == NULL) return NULL;
	return table_lookup(stack->tables, name);
}

#endif
