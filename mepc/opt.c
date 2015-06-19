/* filename: opt.c
   by Dong Wei */

#include "pascal.h"

#define MAX_LABEL 4096
static char label_v[MAX_LABEL];

void optimize (void)
{
		int n_label;
		int n_code, r_code;
		int i;
		n_label = next_label();
		n_code = text->last;
		memset(label_v, 0, sizeof(label_v));
		for (i = 0; i < n_code; i++)
				if ((text->data[i].op != OP_LABEL)
						&& (text->data[i].arg[0].flag == ARG_LABEL))
						{
								label_v[text->data[i].arg[0].offset] = 1;
						}
		r_code = 0;
		for (i = 0; i < n_code; i++)
				if ((text->data[i].op != OP_NOP)
					&& ((text->data[i].op != OP_LABEL) ||
							(label_v[text->data[i].arg[0].offset % n_label] != 0)))
		{
				text->data[r_code] = text->data[i];
				r_code++;
		}
		text->last = r_code;
}

