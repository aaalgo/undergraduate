/**
  * \file cmnhdr.h
  * \author Dong Wei
  */

#ifndef __CMNHDR__
#define __CMNHDR__

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef GCC
#define info(s...) do { printf(s); fflush(stdout); } while (0)
#define warn(s...) do { fprintf(stderr, s); fflush(stdout); } while (0)
#define fatal(s...) do { fprintf(stderr, s); exit(-1); } while (0)
#else
#include <stdarg.h>

static __inline int info (char *fmt, ...)
{
	va_list argptr;
	int cnt;
	va_start(argptr, fmt);
	cnt = vprintf(fmt, argptr);
	va_end(argptr);
	return(cnt);
}

static __inline int warn (char *fmt, ...)
{
	va_list argptr;
	int cnt;
	va_start(argptr, fmt);
	cnt = vfprintf(stderr, fmt, argptr);
	va_end(argptr);
	return(cnt);
}

static __inline int fatal (char *fmt, ...)
{
	va_list argptr;
	int cnt;
	va_start(argptr, fmt);
	cnt = vfprintf(stderr, fmt, argptr);
	va_end(argptr);
	exit(-1);
	return(cnt);
}

#endif

#define mark	do {printf("%s:%d\n", __FILE__, __LINE__); fflush(stdout); } while (0)

#ifdef BOUNDSCHECKER

#define xmalloc(n)		malloc(n)
#define xcalloc(m,n)	(m == 0 ? NULL : calloc(m, n))
#define xrealloc(t,n)	realloc(t, n);

#else
static __inline void *xmalloc (size_t n)
{
	void *r = malloc(n);
	if (r == NULL) fatal(strerror(errno));
	return r;
}

static __inline void *xcalloc (size_t n, size_t s)
{
	void *r; 
	if (n == 0) return NULL;
	r = calloc(n, s);
	if (r == NULL) fatal(strerror(errno));
	return r;
}

static __inline void *xrealloc (void *t, size_t n)
{
	void *r = realloc(t, n);
	if (r == NULL) fatal(strerror(errno));
	return r;
}
#endif

#define type_alloc(type) (type *)xmalloc(sizeof(type))

#define type_calloc(n, type) (type *)xcalloc(n, sizeof(type))

#define type_realloc(p, n, type) (type *)xrealloc(p, n * sizeof(type))

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#define SUCCESS 0

#endif
