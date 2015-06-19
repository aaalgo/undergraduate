/* filename: dma.c
   by Dong Wei */
#include <clib.h>
#include <io.h>
#include <dma.h>
static u16 address_port[]={0x00, 0x02, 0x04, 0x06,0xc0, 0xc2, 0xc4, 0xc6};
static u16 count_port[] = {0x01, 0x03, 0x05, 0x07,0xc1, 0xc3, 0xc5, 0xc7};
static u16 page_port[] = {0x87, 0x83, 0x81, 0x81,
0x8f, 0x8b, 0x89, 0x8a};
static u16 mode_port[] = {0x0b, 0x0b, 0x0b, 0x0b,
0xd6, 0xd6, 0xd6, 0xd6};
static u16 mask_port[] = {0x0a, 0x0a, 0x0a, 0x0a, 0xd4, 0xd4, 0xd4, 0xd4};
static u16 flip_port[] = {0x0c, 0x0c, 0x0c, 0x0c, 0xd8, 0xd8, 0xd8, 0xd8};

static inline void DMA_clearflip (unsigned channel)
{
	outb(flip_port[channel], 0);
}

static inline void DMA_enable (unsigned channel)
{
	outb(mask_port[channel], channel);
}

static inline void DMA_disable (unsigned channel)
{
	outb(mask_port[channel], channel | 4);
}

void DMA_setup (unsigned channel,
		uchar mask,
		void *address,
		size_t size)
{
	assert(channel < 8);
	assert(size > 0);
	cli();
	outb(0x0D, 0);
	DMA_disable(channel);
	DMA_clearflip(channel);
	outb(page_port[channel], (u32)address >> 16);
	(u32)address &= 0xffff;
	outb(address_port[channel], (u32)address & 0xff);
	outb(address_port[channel], ((u32)address >> 8) & 0xff);
	size--;
	outb(count_port[channel], size & 0xff);
	outb(count_port[channel], size >> 8);
	outb(mode_port[channel], (channel & 0xF) | mask);
	sti();
	DMA_enable(channel);
}

