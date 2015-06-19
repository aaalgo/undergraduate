/* filename: key.c
   by Dong Wei */
#include <io.h>
#include <clib.h>
#include <key.h>
#include <gdt.h>
#include <process.h>

#define KEY_NULL 0
#define KEY_ESC -5
#define KEY_BKSP -2
#define KEY_TAB -3
#define KEY_ENTER -4
#define KEY_PAUSE -1
#define KEY_LSHIFT -6
#define KEY_RSHIFT -7
#define KEY_RALT -8
#define KEY_CAPS -9
#define KEY_F1 -10
#define KEY_F2 -11
#define KEY_F3 -12
#define KEY_F4 -13
#define KEY_F5 -14
#define KEY_F6 -15
#define KEY_F7 -16
#define KEY_F8 -17
#define KEY_F9 -18
#define KEY_F10 -19
#define KEY_SCROLL -20
#define KEY_HOME -21
#define KEY_UP -22
#define KEY_PGUP -23
#define KEY_KPSUB -24
#define KEY_KP4 -25
#define KEY_KP5 -26
#define KEY_KP6 -27
#define KEY_KPADD -28
#define KEY_KP1 -29
#define KEY_KP2 -30
#define KEY_KP3 -31
#define KEY_INSERT -34
#define KEY_DELETE -35
#define KEY_F11 -36
#define KEY_F12 -37
#define KEY_SHIFT -38
#define KEY_ALT -39

#define SCAN_ALT 56
#define SCAN_F1 59
#define SCAN_F2 60
#define SCAN_F3 61
#define SCAN_F4 62
#define SCAN_F5 63

/* int key_map[] = {KEY_NULL, KEY_ESC, '1', '2', '3', '4', '5', '6',
		'7', '8', '9', '0', '-', '=', KEY_BKSP, KEY_TAB,
		'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
		'[', ']', '\n', KEY_PAUSE, 'a', 's', 'd', 'f',
		'g', 'h', 'j', 'k', 'l', ';', '\'', '`', KEY_LSHIFT,
		'\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.',
		'/', KEY_RSHIFT, '*', KEY_RALT, ' ', KEY_CAPS, KEY_F1,
		KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8,
		KEY_F9, KEY_F10, KEY_PAUSE, KEY_SCROLL, KEY_HOME,
		KEY_UP, KEY_PGUP, KEY_KPSUB, KEY_KP4, KEY_KP5, KEY_KP6,
		KEY_KPADD, KEY_KP1, KEY_KP2, KEY_KP3, KEY_INSERT, KEY_DELETE,
		KEY_F11, KEY_F12};*/

int key_map[] = {0, KEY_ESC, '1', '2', '3', '4', '5', '6',
		'7', '8', '9', '0', '-', '=', KEY_BKSP, 0,
		'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
		'[', ']', '\n', 0, 'a', 's', 'd', 'f',
		'g', 'h', 'j', 'k', 'l', ';', '\'', '`', KEY_SHIFT,
		'\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.',
		'/', KEY_SHIFT, '*'};

int key_maps[] = {0, KEY_ESC, '!', '@', '#', '$', '%', '^',
		'&', '*', '(', ')', '_', '+', KEY_BKSP, 0,
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'{', '}', '\n', 0, 'A', 'S', 'D', 'F',
		'G', 'H', 'J', 'K', 'L', ':', '\"', '~', KEY_SHIFT,
		'|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>',
		'?', KEY_SHIFT, '*'};

#define KEY_BUF_LEN 32
sem_t sem_key;
int key_buf[KEY_BUF_LEN];
int kb_head, kb_tail;

void key_init (void)
{
	char cmd;
	kb_head = kb_tail = 0;
	sem_init(&sem_key);
	outb(0x64, 0x20);
	cmd = inb(0x60);
	cmd |= 1;
	outb(0x64, 0x60);
	outb(0x60, cmd);
}

void do_key (void)
{
	int key;
	static int alt = FALSE;
	key = inb(0x60);
	outb(0x20, 0x20);
	if (key == 0) return;
	if (key & 0x80)
	{
		if (key == (SCAN_ALT | 0x80)) alt = FALSE;
		else
		if (alt)
		{
			if (key == (SCAN_F1 | 0x80)) vt_show(0);
			else if (key == (SCAN_F2 | 0x80)) vt_show(1);
			else if (key == (SCAN_F3 | 0x80)) vt_show(2);
			else if (key == (SCAN_F4 | 0x80)) vt_show(3);
			else if (key == (SCAN_F5 | 0x80)) vt_clear(vt_cur);
		}
	}
	else if (key == SCAN_ALT) alt = TRUE;
	key_buf[kb_tail] = key;
	kb_tail = (kb_tail + 1) % KEY_BUF_LEN;
	if (kb_tail == kb_head)
	{
		kb_head = (kb_head + 1) % KEY_BUF_LEN;
	}
	else
	sem_v(&sem_key);
}

int getvc (void)
{
	char key;
	sem_p(&sem_key);
	key = key_buf[kb_head];
	kb_head = (kb_head + 1) % KEY_BUF_LEN;
	return key;
}

int capslock = FALSE;
int shift = FALSE;

int getc (void)
{
	int k;
	int r;
	for (;;)
	{
		k = 0;
		k = getvc();
		r = k & 0x80;
		k &= 0xFF;
		k &= ~0x80;
		if (k >= sizeof(key_map)/sizeof(int)) continue;
		if (r)
		{	
			if (key_map[k] == KEY_SHIFT)
				shift = FALSE;
		}
		else
		{
			if (key_map[k] == KEY_SHIFT)
			{
				shift = TRUE;
				continue;
			}
			else
			{
				if (shift)
					k = key_maps[k];
				else 
					k = key_map[k];
				if (k) return k;
			}
		}
	}
}

char *__gets(char *buf, int show)
{
	char key;
	char *p = buf;
	for (;;)
	{
		key = getc();
		if (key == KEY_BKSP)
		{
			if (p <= buf) continue;
			if (show) vt_back(0);
			p--;
		}
		else
		if (key == '\n') break;
		else
		{
			if (show) vt_put(0, key);
			*p = key;
			p++;
		}
	}
	*p = 0;
	vt_ln(0);
	return buf;
}

