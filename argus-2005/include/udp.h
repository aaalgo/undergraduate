/**
  * \file udp.h
  * \author Dong Wei
  */

#ifndef __ARGUS_UDP__
#define __ARGUS_UDP__
#ifdef LINUX
#include <netinet/in.h>
#endif

typedef struct __package package_t;
struct __package
{
		int size; /* size of data */
		struct sockaddr_in addr;
		package_t *next;
		int type;
		char data[1];
};

/* this function shall not release the resource of package */
typedef int (*udp_func_f) (void *, package_t *);

int udp_init (void);
int udp_cleanup (void);
int udp_start (short int port);
int udp_stop (void);
int udp_send (package_t *package);
int udp_register (int type, udp_func_f func, void *data);
int udp_deregister (int type);

static __inline package_t *udp_alloc_package (struct sockaddr_in addr, int type, int size, void *data)
{
		package_t *p = (package_t *)xmalloc(sizeof(package_t) + size);
		p->size = size;
		p->addr = addr;
		p->type = type;
		memcpy(p->data, data, size);
		return p;
}

static __inline void udp_free_package (package_t *p)
{
		free(p);
}

#endif
