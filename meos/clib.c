/* filename: clib.c
   by Dong Wei */

#include <clib.h>

char *ltox (long n)
{
	static char buf[16];
	int i;
	for (i = 0; i < 8; i++)
	{
		asm("roll $4, %0":"=g"(n):"0"(n));
		buf[i] = n & 0xf;
		if (buf[i] < 10) buf[i] += '0';
		else buf[i] += 'A'-10;
	}
	buf[i] = 0;
	return buf;
}

int atoi (const char *nptr)
{
	int ret = 0;
	int minus = 0;
	if (*nptr == '-')
	{
		minus = 1;
		nptr++;
	}
	while (isdigit(*nptr))
	{
		ret *= 10;
		ret += *nptr - '0';
		nptr++;
	}
	return minus ? -ret : ret;
}

char *itoa (int i)
{
	static char buf[16];
	if (i == 0)
	{
		buf[0] = '0';
		buf[1] = 0;
		return buf;
	}
	else
	{
		char *p;
		int minus = 0;
		if (i < 0)
		{
			minus = 1;
			i = -i;
		}
		buf[15] = 0;
		p = &buf[14];
		while (i != 0)
		{
			*p = i % 10 + '0';
			i /= 10;
			p--;
		}
		if (minus)
		{
			*p = '-';
		}
		else
		{
			p++;
		}
		return p;
	}
}


