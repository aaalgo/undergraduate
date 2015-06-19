#ifndef __ARGUS_POOL__
#define __ARGUS_POOL__


typedef struct
{
	int i;
} pool_t;

int pool_init (pool_t *);

static __inline pool_t *pool_alloc (void)
{
	pool_t *pool = type_alloc(pool_t);
	pool_init(pool);
	return pool;
}

int pool_destroy (pool_t *);

static __inline int pool_free (pool_t *pool)
{
	pool_destroy(pool);
	free(pool);
	return 0;
}

#endif