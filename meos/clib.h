/* filename: clib.h
   by Dong Wei */

#ifndef	__MEOS_CLIB__
#define __MEOS_CLIB__

#ifdef ASSERT

void AssertionFailure(char *exp, char *file, char *baseFile, int line);

#define assert(exp)  if (exp) ; \
        else AssertionFailure( #exp, __FILE__, __BASE_FILE__, __LINE__ )
#else
#define assert(exp)
#endif
	

#define NULL (void *)0
#define TRUE 1
#define FALSE 0

#define isdigit(x) (x >= '0' && x <= '9')
#define islower(x) (x >= 'a' && x <= 'z')
#define isupper(x) (x >= 'A' && x <= 'Z')
#define isalpha(x) (islower(x)||isupper(x))
#define isblank(x) (x ==' ' || x == '\t')
#define toupper(x) (islower(x)? x - 'a' + 'A' : x)
#define tolower(x) (isupper(x)? x - 'A' + 'a' : x)


typedef unsigned long size_t;
typedef char *pchar;
typedef unsigned long off_t;
typedef unsigned char uchar;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;
typedef unsigned char __u8;
typedef signed char __s8;
typedef unsigned short __u16;
typedef signed short __s16;
typedef unsigned int __u32;
typedef signed int __s32;
typedef unsigned long long __u64;
typedef signed long long __s64;

extern int atoi (const char *nptr);
extern char *itoa (int x);
extern char *ltox (long x);
/* Allocate SIZE bytes on a page boundary.  The storage cannot be freed.  */

#define abs(x) (x>=0?x:-x)
#include <string.h>

#ifndef __MEOS_VGA__
#include <vga.h>
#endif
#define CHECK(a,b) do{if(!a)vt_puts(vt_cur, b);}while(0)

extern void vtprinf(int vt, const char *format, ...);

#endif
