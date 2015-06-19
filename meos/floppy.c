/* filename: floppy.c
   by Dong Wei */
#include <io.h>
#include <clib.h>
#include <vga.h>
#include <gdt.h>
#include <process.h>
#include <dma.h>

static sem_t sem_floppy = SEM_INIT;
static sem_t wait_floppy = SEM_INIT;

#define PORT_MSR	0x3f4	/* r */
#define PORT_DATA	0x3f5	/* wr */
#define PORT_DOR	0x3f2	/* w */
#define PORT_DCR	0x3f7	/* w */
#define PORT_DIR	0x3f7	/* r */

#define MSR_BUSYMASK	0x0f
#define MSR_BUSY	0x10
#define MSR_DMA		0x20
#define MSR_DIR		0x40
#define MSR_READY	0x80

#define ST0_DS		0x03
#define ST0_HA		0x04
#define ST0_NR		0x08
#define ST0_ECE		0x10
#define ST0_SE		0x20
#define ST0_INTR	0xC0

#define ST1_MAM		0x01
#define ST1_WP		0x02
#define ST1_ND		0x04
#define ST1_OR		0x10
#define ST1_CRC		0x20
#define ST1_EOC		0x80

#define ST2_MAM		0x01
#define ST2_BC		0x02
#define ST2_SNS		0x04
#define ST2_SEH		0x08
#define ST2_WC		0x10
#define ST2_CRC		0x20
#define ST2_CM		0x40

#define ST3_HA		0x04
#define ST3_TZ		0x10
#define ST3_WP		0x40

#define FD_RECALIBRATE	0x07
#define FD_SEEK		0x0f
#define FD_READ		0xE6
#define FD_WRITE	0xc5
#define FD_SENSEI	0x08
#define FD_SPECIFY	0x03
#define FD_FORMAT	0x40
#define FD_VERSION	0x10
#define FD_CONFIGURE	0x13
#define FD_PERPENDICULAR 0x12

/*#define PORT_DKR	*/

int floppy_change (void)
{
	return inb(PORT_DIR)& 0x80 == 0x80;
}

static inline void floppy_cmd (char c)
{
	uchar stat;
	for (;;)
	{
		stat = inb(PORT_MSR);
		stat &= 0xc0;
		if (stat == 0x80) break;
	}
	outb(PORT_DATA, c);
}

static inline char floppy_ret (void)
{
	char stat;
	for (;;)
	{
		stat = inb(PORT_MSR);
		if (!(stat & 0x80)) continue;
		if (stat & 0x40) break;
	}
	return inb(PORT_DATA);
}

#define moto_on() outb(PORT_DOR, 0x1c)


#define moto_off() outb(PORT_DOR, 0)


int floppy_init ()
{
	sem_init(&sem_floppy);
	sem_init(&wait_floppy);
	sem_v(&sem_floppy);
}

void do_floppy (void)
{
	vt_puts(3, "INT_FLOPPY");
	outb(0x20, 0x20);
	sem_v(&wait_floppy);
}

#define TERM_FD 0

int floppy_read (u32 index, void *buf)
{
	u8 sector;
	u8 track;
	u8 head;
	sector = index % 18;
	sector++;
	index /= 18;
	head = index % 2;
	index /= 2;
	track = index;
	sem_p(&sem_floppy);
	moto_on();
	sleep(4);
	DMA_setup(2, DMA_WRITE, buf, 512);
	floppy_cmd(0x66);
	floppy_cmd(head << 2);
	floppy_cmd(track);
	floppy_cmd(head);
	floppy_cmd(sector);
	floppy_cmd(2);
	floppy_cmd(18);
	floppy_cmd(27);
	floppy_cmd(0xff);
	sem_p(&wait_floppy);
	floppy_ret();
	floppy_ret();
	floppy_ret();
	floppy_ret();
	floppy_ret();
	floppy_ret();
	floppy_ret();
	sem_v(&sem_floppy);
	return TRUE;
}

void floppy_write (u32 index, void *buf)
{
	u8 sector;
	u8 track;
	u8 head;
	sector = index % 18;
	sector++;
	index /= 18;
	head = index % 2;
	index /= 2;
	track = index;
	sem_p(&sem_floppy);
	moto_on();
	sleep(4);
	DMA_setup(2, DMA_READ, buf, 512);
	floppy_cmd(0x65);
	floppy_cmd(head << 2);
	floppy_cmd(track);
	floppy_cmd(head);
	floppy_cmd(sector);
	floppy_cmd(2);
	floppy_cmd(18);
	floppy_cmd(27);
	floppy_cmd(0xff);
	sem_p(&wait_floppy);
	floppy_ret();
	floppy_ret();
	floppy_ret();
	floppy_ret();
	floppy_ret();
	floppy_ret();
	floppy_ret();
	sem_v(&sem_floppy);
	return TRUE;
}

