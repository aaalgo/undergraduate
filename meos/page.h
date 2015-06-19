/* filename: page.h
   by Dong Wei */

#ifndef __MEOS_PAGE__
#define __MEOS_PAGE__
#define PAGE_SIZE 4096
extern int page_init (void);
extern void *page_alloc (void);
extern void page_free (void *);

#endif
