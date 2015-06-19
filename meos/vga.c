/* filename: clib.c
   by Dong Wei */
#include <io.h>
#include <vga.h>
#include <clib.h>

void vt_adjust (int i)
{
	if (vt[i].current % (2 * SRC_WIDTH) == 0)	/* new line */
	{
		if (vt[i].current >= SRC_SIZE * 2) /* we have to scroll the screen */
		{
			if (vt[i].start >=  SRC_SIZE) /* flip up */
			{
				memcpy(vt[i].orig,
					vt[i].orig + (SRC_SIZE + SRC_WIDTH) * 2,
					(SRC_SIZE - SRC_WIDTH) * 2);
				memsetw(vt[i].orig + (SRC_SIZE - SRC_WIDTH) * 2, ' '| 0x0700, SRC_SIZE + SRC_WIDTH);
				vt[i].start = 0;
				vt[i].current = (SRC_SIZE - SRC_WIDTH) * 2;
			}
			else
			{
				vt[i].start += SRC_WIDTH;
			}
			vt[i].cursor = vt[i].start + (SRC_HEIGHT - 1) * SRC_WIDTH;
			if (i == vt_cur) vt_scroll(i);
		}
	}
}

void vtprintf (int vt, const char *format, ...)
{
	char **arg = (char **) &format;
	int c;
	arg++;
  
	while ((c = *format++) != 0)
	{
		if (c == '\n')
			vt_ln(vt);
		else
		if (c != '%')
			vt_put(vt, c);
		else
        	{
			char *p;
			c = *format++;
			switch (c)
			{
			case 'c': vt_put(vt, *(int*)arg++);
				  break;
			case 'd':
			case 'u': p = itoa(*(int *)arg++);
				goto string;
				break;
			case 'x': p = ltox(*((int *) arg++));
				goto string;
				break;
			case 's':
				p = *arg++;
				if (! p)
				p = "(null)";
string:				while (*p)
					vt_put(vt, *p++);
				break;
			default:
				vt_put(vt, *((int *) arg++));
				break;
			}
		}
	}
}

