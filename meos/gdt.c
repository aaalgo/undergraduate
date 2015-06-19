#include <io.h>
#include <clib.h>
#include <page.h>
#include <gdt.h>

#define GDT_PAGE 16
#define DEFAULT_EFLAGS 0x202

extern u16 gdtr_lim;
extern u32 gdtr_gdt;
static desc_t volatile *gdt = NULL;
static desc_t *sstart;
static desc_t *sguard;

int gdt_init (void)
{
	tss_t *tss;
	/*page_calloc(256);*/
	gdt = (desc_t *)page_calloc(GDT_PAGE);
	gdtr_lim = (u16)(GDT_PAGE*PAGE_SIZE-1);
	gdtr_gdt = (u32)gdt;
	CHECK(gdt != 0, "PAGE_ALLOC_FAIL.");
	bzero(gdt, GDT_PAGE * PAGE_SIZE);
	/* note that both data and code descriptor are exactly the same as the orignal
	   value, see entry.S */
	gdt[0] = 0x0;
	gdt[1] = 0x00cf9a000000ffff;
	gdt[2] = 0x00cf92000000ffff;
	tss = tss_alloc(NULL);
	asm("lgdt gdtr\n"
		"ljmp $8,$1f\n1:\n");
	sstart = &gdt[3];
	sguard = (desc_t *)((char *)gdt + GDT_PAGE*PAGE_SIZE);
	return 1;
}

sel_t gdt_insert (desc_t desc)
{
	while (*sstart != 0 && sstart < sguard) sstart++;
	if (sstart >= sguard) return 0;
	*sstart = desc;
	return (sel_t)((pchar)sstart - (pchar)gdt);
}

void gdt_remove (sel_t sel)
{
	desc_t *t = (desc_t *)((pchar)gdt + sel);
	*t = 0;
	if (t < sstart) sstart = t;
}

extern char *sysstack;

tss_t *tss_alloc (void *start)
{
	tss_t *tss;
	char *stack = page_alloc();
	tss = (tss_t *)page_alloc();
	bzero(tss, PAGE_SIZE);
	tss->cs = CODESEL;
	tss->ds = tss->es = tss->ss = tss->fs = tss->gs = DATASEL;
	tss->eip = (u32)start;
	tss->eflags = DEFAULT_EFLAGS;
	tss->esp = (u32)stack + PAGE_SIZE - 4;
	tss->ss0 = tss->ss1 = tss->ss2 = DATASEL;
	tss->esp0 = tss->esp1 = tss->esp2 = (u32)sysstack + PAGE_SIZE - 1;	
	return tss;
}

typedef union
{
	desc_t desc;
	struct
	{
		u16 limit1;
		u16 base1;
		u8 base2;
		u8 flags;
		u8 flase;
		u8 base3;
	} detail;
} tss_desc;

desc_t make_tss_desc (tss_t *tss)
{
	tss_desc desc;
	desc.detail.limit1 = sizeof(tss_t) - 1;
	desc.detail.base1 = (u32)tss;
	desc.detail.base2 = ((u32)tss >> 16) & 0xffff;
	desc.detail.flags = 0x89;
	desc.detail.flase = 0x0;
	desc.detail.base3 = ((u32)tss >> 24) & 0xff;
	return desc.desc;
}

