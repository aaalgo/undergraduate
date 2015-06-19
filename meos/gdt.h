/* filename: gdt.h
   by Dong Wei */
#ifndef __MEOS_GDT__
#define __MEOS_GDT__

#define CODESEL 0x08
#define DATASEL 0x10

typedef unsigned short int sel_t;
typedef unsigned long long int desc_t;

extern int gdt_init (void);
extern sel_t gdt_insert (desc_t desc);
extern void gdt_remove (sel_t sel);

typedef struct
{
	u16 link, z0;
	u32 esp0;
	u16 ss0, z1;
	u32 esp1;
	u16 ss1, z2;
	u32 esp2;
	u16 ss2, z3;
	u32 cr3;
	u32 eip;
	u32 eflags;
	u32 eax;
	u32 ecx;
	u32 edx;
	u32 ebx;
	u32 esp;
	u32 ebp;
	u32 esi;
	u32 edi;
	u16 es, z4;
	u16 cs, z5;
	u16 ss, z6;
	u16 ds, z7;
	u16 fs, z8;
	u16 gs, z9;
	u16 ldt, z10;
	u16 tflag;
	u16 iomap;
} tss_t;

tss_t *tss_alloc();
desc_t make_tss_desc(tss_t *tss);

static inline switchto (sel_t sel)
{
	u32 s[2];
	s[1] = sel;
	asm("ljmp %0"::"m"(*s));
}


#endif
