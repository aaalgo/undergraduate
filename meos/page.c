/* filename: page.c
   by Dong Wei */

#include <clib.h>
#include <io.h>
#include <vga.h>
#include <entry.h>
#include <page.h>

#define MEGABYTE (1024*1024)

char *memtop = NULL;
char *talloc = NULL;
size_t tsize = 0;
char *sstart = NULL;
char *sysstack = NULL;

#define PAGESHIFT 12
#define BYTESHIFT 3
#define MBITSHIFT (PAGESHIFT + BYTESHIFT)

int page_init (void)
{
	int i;
	for (i = 0; i < nmmap; i++)
	{
/*		vt_puts(vt_cur, itoa(mmap[i].base));
		vt_puts(vt_cur, itoa(mmap[i].size));*/
		if (mmap[i].base + mmap[i].size > memtop)
		{
			memtop = mmap[i].base + mmap[i].size;
		}
	}
	tsize = (size_t)memtop >> MBITSHIFT; /* tsize = high / 4096 / 8 */
	/* we shall check the size of the last block of available memory is bigger than tsize */
	talloc = memtop - tsize;
	bzero(talloc, tsize);
	for (i = 0; i < nmmap; i++)
		if ((size_t)mmap[i].base >= MEGABYTE)
		{
			memset(talloc + ((size_t)mmap[i].base >> MBITSHIFT), 0xff, mmap[i].size >> MBITSHIFT);
		}
	bzero(talloc + ((u32)talloc >> MBITSHIFT), (memtop - talloc) >> MBITSHIFT + 1);
	sstart = talloc;
	sysstack = page_alloc();
	return TRUE;
}


void * page_alloc (void)
{
	int i;
	void *p;
	while ((*sstart == 0) && (sstart < memtop)) sstart++;
	if (sstart >= memtop) return NULL;
	i = 0;
	while ((*sstart & (1 << i))== 0) i++;
/*	i = ffs(*start);*/
	*sstart &= ~(char)(1 << i);
	p = (void *)((((sstart - talloc) << BYTESHIFT) + i) << PAGESHIFT);
	return p;
}

void page_free (void *p)
{
	size_t i;
	char *b;
	i = (size_t)p >> PAGESHIFT;
	b = talloc + (i >> BYTESHIFT);
	i = i % 8;
	*b |= 1 << i;
	if (b < sstart) sstart = b;
}

static inline int ttestc (off_t ofs, size_t cnt)
{
	off_t bofs, sofs;
	int ll, lr, i, ocnt;
	char mask;
	ll = ofs & 0x7;
	mask = ~((char)1 << ll - 1);
	bofs = ofs >> 3;
	ocnt = cnt;
	if (ll + cnt <= 8)
	{
		mask &= 1 << (ll + cnt) - 1;
		if (talloc[bofs] & mask == mask)
		{
			talloc[bofs] &= ~mask;
			return 1;
		}
	}
	else
	{
		if (talloc[bofs] & mask != mask) return 0;
		sofs= bofs;
		bofs++;
		cnt -= 8-ll;
		lr = cnt >> 3;
		for (i = 0; i < lr; i++)
			if (talloc[bofs] != (char)0xff) break;
			else bofs++;
		if (i < lr) return 0;
		lr = cnt & 7;
		mask = 1 << lr - 1;
		if (talloc[bofs] & mask != mask) return 0;
		cnt = ocnt;
		ll = ofs & 7;
		mask = ((char)1 << ll - 1);
		sofs = ofs >> 3;
		talloc[sofs] &= mask;
		sofs++;
		cnt -= 8 - ll;
		lr = cnt >> 3;
		for (i = 0; i < lr; i++)
			talloc[sofs++] = 0;
		lr = cnt & 7;
		talloc[sofs] &= ~(1 << lr - 1);
		return 1;
	}
}

static inline void tset1 (off_t ofs, size_t cnt)
{
	int bofs;
	int ll, lr, i;
	char mask;
	bofs = ofs >> 3;
	ll = ofs & 7;
	mask = ~((char)1 << ll - 1);
	if (ll + cnt <= 8)
	{
		mask &= 1 << (ll + cnt) -1;
		talloc[bofs] |= mask;
	}
	else
	{
		talloc[bofs++] |= mask;
		cnt -= (8-ll);
		lr = cnt >> 3;
		for (i = 0; i < lr; i++)
			talloc[bofs++] = 0xff;
		lr = cnt % 7;
		talloc[bofs] |= (1 << lr) - 1;
	}
}

void *page_calloc (int n)
{
	off_t ofs;
	off_t guard;
	while (*sstart == 0 && sstart < memtop) sstart++;
	if (sstart >= memtop) return NULL;
	ofs = (sstart - talloc) << 3;
	guard = (memtop - talloc) << 3;
	for (;;)
	{
		if (ttestc(ofs, n))
			return (void *)(ofs << PAGESHIFT);
		ofs++;
		if (ofs >= guard) break;
	}
	return NULL;
}

void page_cfree (void *p, int n)
{
	tset1 ((off_t)p >> PAGESHIFT, n); 
}

