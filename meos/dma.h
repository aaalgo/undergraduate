/* filename: dma.h
   by Dong Wei */
#ifndef __MEOS_DMA__
#define __MEOS_DMA__
/* Control Byte Bit Definitions
   Mode Selection */
#define DMA_DEMAND	0x0
#define DMA_SINGLE	0x40
#define DMA_BLOCK	0x80
#define DMA_CASCADE	0xC0
/* Address Increment/Decrement */
#define DMA_INC		0x0
#define DMA_DEC		0x20
/* AutoInitialization enable bit */
#define DMA_AUTOINIT	0x10
#define DMA_SINGLECYCLE	0x0
/* Transfer Type Bits */
#define DMA_VERIFY	0x0
#define DMA_WRITE	0x4
#define DMA_READ	0x8

void DMA_setup (unsigned channel, uchar mask, void *, size_t);
/* void DMA_enable (unsigned channel);*/
/*void DMA_disable (unsigned channel);*/


#endif
