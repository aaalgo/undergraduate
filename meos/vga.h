#ifndef __MEOS_VGA__
#define __MEOS_VGA__

/* filename: vga.h
   by Dong Wei */
#define TERMNUM		4	
#define VIDEOBUF	(char *)0xB8000
#define SRC_WIDTH	80
#define SRC_HEIGHT	25
#define SRC_SIZE	(25*80)
#define PAGESIZE	8192
#define PAGEEND		(25*80*2)

#define CRTC_PORT	0x3D4
#define DATA_PORT	0x3D5
#define VT_OFS_HIGH	0x0C
#define VT_OFS_LOW	0x0D
#define VT_CUR_HIGH	0x0E
#define VT_CUR_LOW	0x0F

#define COLOR_BLACK		0x0
#define COLOR_BLUE		0x01
#define COLOR_GREEN		0x02
#define COLOR_CYAN		0x03
#define COLOR_RED		0x04
#define COLOR_MAGENTA		0x05 push   %ebp

#define COLOR_BROWN		0x06
#define COLOR_WHITE		0x07
#define COLOR_LIGHT		0x08
#define COLOR_BG_BLUE		0x10
#define COLOR_BG_GREEN		0x20
#define COLOR_BG_RED		0x40
#define COLOR_BLINK		0x80


typedef struct
{
	char *orig;
	unsigned short start;
	unsigned short current;
	unsigned short cursor;
	char color;
} vt_t;

extern vt_t vt[TERMNUM];
extern int vt_cur;

#define set_vga_reg(i, d) outb(CRTC_PORT, i); outb(DATA_PORT, d)

/* set virtual terminal color */
static inline void vt_color (int i, char color)
{
	vt[i].color = color;
}

static inline void vt_hidecursor ()
{
	short cursor = -1;
	set_vga_reg(VT_CUR_LOW, cursor);
	set_vga_reg(VT_CUR_HIGH, cursor >> 8);
}

static inline void vt_cursor (int i)
{
	unsigned short cursor = vt[i].cursor + i * PAGESIZE / 2;
	set_vga_reg(VT_CUR_LOW, cursor);
	set_vga_reg(VT_CUR_HIGH, cursor >> 8);
}

static inline void vt_scroll (int i)
{
	unsigned short start = vt[i].start + i * PAGESIZE / 2;
	set_vga_reg(VT_OFS_LOW, (char)start);
	set_vga_reg(VT_OFS_HIGH, start >> 8);
}

static inline void vt_show (int i)
{
	vt_cur = i;
	vt_scroll(i);
	vt_cursor(i);
}

/* reset virtual terminal */
static inline void vt_reset (int i)
{
	vt[i].orig = VIDEOBUF + i * PAGESIZE;
	vt[i].start = 0;
	vt[i].current = 0;
	vt[i].color = 0x07;
	vt[i].cursor = 0;
	if (i == vt_cur)
		vt_show(i);
}

static inline void vt_init (void)
{
	int i;
	vt_cur = 0;
	for (i = 0; i < TERMNUM; i++)
		vt_reset(i);
}

static inline void vt_clear (int i)
{
	char *c = vt[i].orig;
	memsetw(vt[i].orig, ' ' | 0x0700, SRC_SIZE * 2);
	vt_reset(i);
}

extern void vt_adjust (int i);

static inline void vt_put (int i, char c)
{
	char *p;
	p = vt[i].orig + vt[i].current;
	*p = c;
	p++;
	*p = vt[i].color;
	vt[i].current += 2;
	vt[i].cursor++;
	vt_adjust(i);
	if (i == vt_cur) vt_cursor(i);
}

static inline void vt_back (int i)
{
	if (vt[i].current % (SRC_WIDTH * 2) == 0) return;
	vt[i].current -= 2;
	vt[i].cursor--;
	*(vt[i].orig + vt[i].current) = ' ';
	if (i == vt_cur) vt_cursor(i);
}

static inline void vt_ln (int i)
{
	unsigned short l;
	l = vt[i].current % (SRC_WIDTH * 2);
	vt[i].current += SRC_WIDTH * 2 - l;
	vt[i].cursor += SRC_WIDTH - (l >> 1);
	vt_adjust(i);
	if (i == vt_cur) vt_cursor(i);
}

static inline void vt_puts (int i, char *dat)
{
	while (*dat)
	{
		vt_put(i, *dat);
		dat++;
	}
	vt_ln(i);
}
#endif
