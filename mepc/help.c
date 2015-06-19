#include <stdio.h>
/* print the help message */

void help (void)
{
	printf("MEPC - a pascal compiler written by Dong Wei.\n");
	printf("Usage:\n");
	printf("\tmepc -i <input> -o <output> -O <optim> -t <target>\n");
	printf("\t\ttarget = i386 / mips\n\n");
}
