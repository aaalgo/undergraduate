#ifndef __MEOS_IO__
#define __MEOS_IO__

#define BUILDIO(bwl,bw,type) \
static inline void out##bwl(int port, unsigned type value) { \
	__asm__ __volatile__("out" #bwl " %" #bw "0, %w1" : : "a"(value), "Nd"(port)); \
} \
static inline unsigned type in##bwl(int port) { \
	unsigned type value; \
	__asm__ __volatile__("in" #bwl " %w1, %" #bw "0" : "=a"(value) : "Nd"(port)); \
	return value; \
} \
static inline void outs##bwl(int port, const void *addr, unsigned long count) { \
	__asm__ __volatile__("rep; outs" #bwl : "+S"(addr), "+c"(count) : "d"(port)); \
} \
static inline void ins##bwl(int port, void *addr, unsigned long count) { \
	__asm__ __volatile__("rep; ins" #bwl : "+D"(addr), "+c"(count) : "d"(port)); \
}

BUILDIO(b,b,char)
BUILDIO(w,w,short)
BUILDIO(l,,int)

static inline void cli (void)
{
	asm("cli");
}

static inline void sti (void)
{
	asm("sti");
}

#endif
