/**
  * \file hash.h
  * \author Dong Wei
  *
  * Definitions of functions and structures used in hash table management.
  * Open hashing algorithm is used.
  *
  * The hash table manages a list of (key, data) pairs, where key are text
  * strings ended by zero character (\000) and data is a 32-bit value, or
  * of type void *, either a pointer to other data structure or simple an
  * integer.
  *
  * How to use it:
  *
  * The type of a hash table is hash_t, but most functions accessing hash
  * tables only accept pointer to a hash table, i.e. hash_t *. There are
  * two ways of declaring a hash table:
  * 
  * 1)	hash_t hash; 
  * hash_init(&hash, size, flag);
  *	....
  * hash_insert(&hash, "abc", data);
  *	....
  *	hash_destroy(&hash);
  *	
  * 2)	hash_t *hash;
  *	hash = hash_alloc(size, flag);
  *	....
  *	data = hash_lookup(hash, "abc");
  *	....
  *	hash_free(hash);
  *
  * Better not see into the details of the structures declared here,
  * just remember the type hash_t. The functions declared in this file
  * are mostly self-evident. The only explanation needed is the parameters
  * passed to hash_alloc/hash_init:
  *
  * size: size (bucket number) of the hash table, simply pass 0
  *		to use the default value.
  *	flag: can be 0 or HASH_STRDUP. A hash table does not save
  *		a copy of the string used as key by default, instead
  *		it just stores the pointer to the string, so
  *		1) you MUST NOT change the value of the string once
  *		you have passed it to hash_insert and before the
  *		hash table is destroyed.
  *		2) you have to release the memory taken by the string
  *		after the hash table is destroyed.
  *		
  *		But you have the choice of passing HASH_STRDUP as the
  *		flag to make hash table save a copy of the key string,
  *		and automatically free the memory when the hash table
  *		is destroyed, and the above two problems no longer
  *		exist. The problem is that it may take up a certain
  *		amount of memory to save the key strings.
  **/
	
#ifndef __PASCAL_HASH__
#define __PASCAL_HASH__

#define DEF_HASH_SIZE 128
#define HASH_STRDUP 1

///The hash entry structure.
typedef struct hash_entry
{
	/// Link to the entry of a different name.
	struct hash_entry *link; /* next of a different name */
	/// Link to the next entry of the same name.
	struct hash_entry *next; /* next of the same name */
	/// Name of the entry.
	char *name;
	/// Related data.
	void *data;
} hash_entry_t;

/// The hash table type.
typedef struct hash
{
	/// Type of the hash table.
	int flag;
	/// Size of the hash table.
	size_t size;
	/// Link to entries.
	hash_entry_t **entries;
} hash_t;


/// Initialize a static hash table.
static inline void hash_init (hash_t *hash, int size, int flag)
{
	assert(hash != NULL);
	assert(flag == 0 || flag == HASH_STRDUP);
	assert(size >= 0);
	hash->flag = flag;
	hash->size = (size > 0) ? size: DEF_HASH_SIZE;
	assert(hash->size != 0);
	hash->entries = (hash_entry_t **)calloc(hash->size, sizeof (hash_entry_t));
	assert(hash->entries != NULL);
}

/// Destroy a hash table(without freeing it).
void hash_destroy (hash_t *hash);

static inline hash_t *hash_alloc (int size, int flag)
{
	hash_t *hash = (hash_t *)malloc(sizeof(hash_t));
	assert(hash != NULL);
	hash_init(hash, size, flag);
	return hash;
}

/// Free a hash table.
static inline void hash_free (hash_t *hash)
{
	assert(hash != NULL);
	hash_destroy(hash);
	free(hash);
}

/// Insert a item to the hash table.
void hash_insert (hash_t *hash, char *name, void *data);
/// Lookup a item in the hash table.
void *hash_lookup (hash_t *hash, char *name);
/// Delete a item from the hash table.
void hash_remove (hash_t *hash, char *name);

#endif

