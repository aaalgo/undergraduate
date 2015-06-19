#ifndef __MEOS_STRING__
#define __MEOS_STRING__


static inline void *memcpy (void *dest, const void *src, size_t n)
{
	char *d, *s;
	int i;
	d = dest; s = (char *)src;
	for (i = 0; i < n; i++)
	{
		*d = *s;
		d++;
		s++;
	}
	return dest;
}

static inline char *strcpy (char *dest, const char *src)
{
	char *d;
	const char *s;
	d = dest; s = src;
	for (;;)
	{
		*d = *s;
		if (*d == 0) break;
		s++;
		d++;
	}
	return dest;
}

static inline void *memset (void *dest, int t, size_t n)
{
	char *d;
	int i;
	d = dest;
	for (i = 0; i < n; i++)
	{
		*d = (char)t;
		d++;
	}
	return dest;
}

#define bzero(a,b)  memset(a, 0, b)

static inline void *memsetw (void *dest, int t, size_t n)
{
	unsigned short *d;
	int i;
	d = dest;
	for (i = 0; i < n; i++)
	{
		*d = (unsigned short)t;
		d++;
	}
	return dest;
}


static inline int ffs (int n)
{
	asm("bsfl %0,%%eax"::"g"(n));
	
}

#endif

