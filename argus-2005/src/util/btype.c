#include <stdlib.h>
#include <config.h>
#include <cmnhdr.h>
#include <libtype.h>
typedef int bool;

int bool_from_string (void *buf, char *string, int *readsize)
{
		int i = 0;
		while (string[i] == ' ') i++;
		*(int *)buf = strcmp(string + i, "true") == 0;
		while (string[i] != ' ') i++;
		if (readsize != NULL) *readsize = i;
		return 0;
}

int bool_to_string (void *buf, char *string, int bufsize)
{
		if (*(int *)buf)
		{
				if (bufsize >= 5)
				strcpy(string, "true");
				return 5;
		}
		else
		{
				if (bufsize > 6)
				strcpy(string, "false");
				return 6;
		}
}

int char_from_string (void *buf, char *string, int *readsize)
{
		sscanf(string, "%c", buf);
		if (readsize != NULL) *readsize = 1;
		return 0;
}

int char_to_string (void *buf, char *string, int bufsize)
{
	if (bufsize >= 2)
	sprintf(string, "%c", *(char *)buf);
	return 2;
}

unsigned char_hash (void *buf)
{
	return *(char *)buf;
}

unsigned int_hash (void *buf)
{
	return *(unsigned *)buf;
}

int int_from_string (void *buf, char *string, int *readsize)
{
	int i, r;
	r = sscanf(string, "%d%n", buf, &i);
	if (readsize != NULL) *readsize = i;
	return !(r == 2); /* 0 for success */
}

int int_to_string (void *buf, char *string, int bufsize)
{
	int size;
	char tmp[16];
	size = sprintf(tmp, "%d", *(int *)buf) + 1;
	if (bufsize >= size)
		strcpy(string, tmp);
	return size;
}

int float_from_string (void *buf, char *string, int *readsize)
{
	int i, r;
	r = sscanf(string, "%f%n", buf, &i);
	if (readsize != NULL) *readsize = i;
	return !(r == 2);
}

int float_to_string (void *buf, char *string, int bufsize)
{
	int size;
	char tmp[16];
	size = sprintf(tmp, "%f", *(float *)buf) + 1;
	if (bufsize > size)
		strcpy(string, tmp);
	return size;
}

int string_from_string (void *buf, char *string, int *readsize)
{
	*(char **)buf = strdup(string);
	if (readsize != NULL) *readsize = strlen(string);
	return 0;
}

int string_to_string (void *buf, char *string, int bufsize)
{
	int len;
	char *str = *(char **)buf;
	len = strlen(str) + 1;
	if (len <= bufsize) strcpy(string, str);
	return len;
}

int string_encode (void *buf, void *out, int bufsize)
{
	int len, size;
	char *str = *(char **)buf;
	char *pout = (char *)out;
	len = strlen(str)+1;
	size = len + sizeof(unsigned short);
	if (size <= bufsize)
	{
		*(unsigned short *)out = len;
		pout += sizeof(unsigned short);
		memcpy(pout, str, len);
	}
	return size;
}

int string_decode (void *buf, void *in)
{
	int len;
	char *pin;
	char *str;
	len = *(unsigned short *)in;
	pin = (char *)in + sizeof (unsigned short);
	str = (char *)xmalloc(len);
	memcpy(str, pin, len);
	*(char **)buf = str;
	return len+sizeof(unsigned short);
}

int string_free (void *buf)
{
	free(*(char **)buf);
	return 0;
}

int string_copy (void *to, void *from)
{
	*(char **)to = strdup(*(char **)from);
	return 0;
}

int string_cmp (void *str1, void *str2)
{
	return strcmp(*(char **)str1, *(char **)str2);
}

unsigned string_hash (void *str)
{
	return (**(unsigned **)str);
}

int datetime_from_string (void *buf, char *string)
{
	return 0;		
}

int datetime_to_string (void *buf, char *string, int bufsize)
{
	datetime_t *dt = (datetime_t *)buf;
	if (bufsize < 20) return 20;
	sprintf(string, "%04d-%02d-%02d %02d:%02d:%02d",
		dt->year,
		dt->month,
		dt->day,
		dt->hour,
		dt->minute,
		dt->second);
	return 20;
}

int datetime_cmp (void *d1, void *d2)
{
	unsigned __int64 ret;
	ret = *(unsigned __int64 *)d1 - *(unsigned __int64 *)d2;
	if (ret > 0) return 1;
	if (ret < 0) return -1;
	return 0;
}

unsigned datetime_hash (void *d)
{
	unsigned *t = (unsigned *)d; 
	unsigned ret = *t;
	t++;
	ret += *t;
	return ret;
}

/*
int double_from_string (void *buf, char *string)
{
		int i;
		sscanf(string, "%lf%n", buf, &i);
		return i;
}

int double_to_string (void *buf, char *string)
{
		return sprintf(string, "%lf", *(double *)buf) + 1;
}
*/

/*
int string_to_string (void *buf, char *string)
{
		strcpy(string, buf);
		return strlen(buf) + 1;
}

int pchar_to_string (void *buf, char *string)
{
		strcpy(string, *(char **)buf);
		return strlen(string) + 1;
}
*/

int ipaddr_to_string (void *buf, char *string, int bufsize)
{
		char tmp[32];
		int len;
		unsigned char *ip = (unsigned char *)buf;
		unsigned int a = ip[0];
		unsigned int b = ip[1];
		unsigned int c = ip[2];
		unsigned int d = ip[3];
		len = sprintf(tmp, "%u.%u.%u.%u",
					a,b,c,d);
		if (len + 1 <= bufsize)
			strcpy(string, tmp);
		return len + 1;
}

/*
int type_to_string (void *buf, char *string)
{
		int p = *(int *)buf;
		type_t *t = type_from_id(p);
		if (t == NULL)
		{
			return sprintf(string, "") + 1;
		}
		else
		{
			return sprintf(string, "%s", t->name) + 1;
		}
		info("Type to string\n");
}
*/
int char_cmp (int *a, int *b)
{
	return *a - *b;
}

int int_cmp (int *a, int *b)
{
		return *a - *b;
}

int float_cmp (float *a, float *b)
{
	if (*a > *b) return 1;
	if (*a < *b) return -1;
	return 0;
}


type_t type_void = {0, "void", 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

type_t type_bool = {1, "bool", sizeof(bool),
				bool_from_string, bool_to_string, NULL, NULL, NULL, int_cmp, NULL, int_hash};
type_t type_char = {2, "char", sizeof(char),
				char_from_string, char_to_string, NULL, NULL, NULL, char_cmp, NULL, char_hash};
type_t type_int = {3, "int", sizeof(int),
				int_from_string, int_to_string, NULL, NULL, NULL, int_cmp, NULL, int_hash};
type_t type_float = {4, "float", sizeof(float),
				float_from_string, float_to_string, NULL, NULL, NULL, float_cmp, NULL, int_hash};

type_t type_string = {5, "string", sizeof(char *), 
				string_from_string, string_to_string, string_encode, string_decode, string_copy, string_cmp, string_free, string_hash};

type_t type_ip = {6, "ip", 4,
				NULL, ipaddr_to_string, NULL, NULL, NULL, int_cmp, NULL, int_hash};

type_t type_datetime = {7, "datetime", 8,
				NULL, datetime_to_string, NULL, NULL, NULL, datetime_cmp, NULL, datetime_hash};
#define DECLARE_UNI_FUNC(id, name, op, t)	\
	void t##_##name (t *r, t *p1)		\
	{											\
			*r = op *p1;						\
	}											\
func_t func_##t##_##name = {id, #name, 			\
	/*	NULL, NULL, NULL,*/ (func_f)t##_##name, &type_##t, &type_##t, &type_void}

#define DECLARE_BIN_FUNC(id, name, op, t)	\
	void t##_##name (t *r, t *p1, t *p2)		\
	{											\
			*r = *p1 op *p2;					\
	}											\
func_t func_##t##_##name = {id, #name, 			\
/*	NULL, NULL, NULL, */(func_f)t##_##name, &type_##t, &type_##t, &type_##t}

#define DECLARE_COMP_FUNC(id, name, op, t)	\
	void t##_##name (int *r, t *p1, t *p2)		\
	{											\
			*r = *p1 op *p2;					\
	}											\
func_t func_##t##_##name = {id, #name, 			\
/*	NULL, NULL, NULL, */(func_f)t##_##name, &type_bool, &type_##t, &type_##t}


DECLARE_UNI_FUNC(1, not, !, bool);
DECLARE_BIN_FUNC(2, and, &&, bool);
DECLARE_BIN_FUNC(3, or, ||, bool);
DECLARE_BIN_FUNC(4, add, +, int);
DECLARE_BIN_FUNC(5, sub, -, int);
DECLARE_BIN_FUNC(6, mul, *, int);
DECLARE_BIN_FUNC(7, div, /, int);
DECLARE_BIN_FUNC(8, add, +, float);
DECLARE_BIN_FUNC(9, sub, -, float);
DECLARE_BIN_FUNC(10, mul, *, float);
DECLARE_BIN_FUNC(11, div, /, float);

DECLARE_COMP_FUNC(12, equ, ==, int);
DECLARE_COMP_FUNC(13, gt, > , int);
DECLARE_COMP_FUNC(14, lt, < , int);
DECLARE_COMP_FUNC(15, ge, >=, int);
DECLARE_COMP_FUNC(16, le, <=, int);
DECLARE_COMP_FUNC(17, ne, !=, int);
DECLARE_COMP_FUNC(18, equ, ==, float);
DECLARE_COMP_FUNC(19, gt, > , float);
DECLARE_COMP_FUNC(20, lt, < , float);
DECLARE_COMP_FUNC(21, ge, >=, float);
DECLARE_COMP_FUNC(22, le, <=, float);
DECLARE_COMP_FUNC(23, ne, !=, float);

void string_equ (int *r, char **s1, char **s2)
{
	*r = strcmp(*s1, *s2) == 0;
}

void string_gt (int *r, char **s1, char **s2)
{
	*r = strcmp(*s1, *s2) > 0;
}

void string_lt (int *r, char **s1, char **s2)
{
	*r = strcmp(*s1, *s2) < 0;
}

void string_ge (int *r, char **s1, char **s2)
{
	*r = strcmp(*s1, *s2) >= 0;
}

void string_le (int *r, char **s1, char **s2)
{
	*r = strcmp(*s1, *s2) <= 0;
}

void string_ne (int *r, char **s1, char **s2)
{
	*r = strcmp(*s1, *s2) != 0;
}

void string_length (int *r, char **s1)
{
	*r = strlen(*s1);
}

func_t func_string_equ = {24, "equ", (func_f)string_equ,
							TYPE_INT, TYPE_STRING, TYPE_STRING};
func_t func_string_gt = {25, "gt", (func_f)string_gt,
							TYPE_INT, TYPE_STRING, TYPE_STRING};
func_t func_string_lt = {26, "lt", (func_f)string_lt,
							TYPE_INT, TYPE_STRING, TYPE_STRING};
func_t func_string_ge = {27, "ge", (func_f)string_ge,
							TYPE_INT, TYPE_STRING, TYPE_STRING};
func_t func_string_le = {28, "le", (func_f)string_le,
							TYPE_INT, TYPE_STRING, TYPE_STRING};
func_t func_string_ne = {29, "ne", (func_f)string_ne,
							TYPE_INT, TYPE_STRING, TYPE_STRING};
func_t func_string_length = {30, "length", (func_f)string_length,
							TYPE_INT, TYPE_STRING, TYPE_VOID};
DECLARE_COMP_FUNC(31, equ, ==, bool);


/*DECLARE_BIN_FUNC(12, add, +, double);
DECLARE_BIN_FUNC(13, sub, -, double);
DECLARE_BIN_FUNC(14, mul, *, double);
DECLARE_BIN_FUNC(15, div, /, double);*/

int register_internal_types ()
{
		/* register types */
		type_register(&type_void);
		type_register(&type_bool);
		type_register(&type_char);
		type_register(&type_int);
		type_register(&type_float);
		type_register(&type_string);
		type_register(&type_ip);
		type_register(&type_datetime);
		/* register functions */
		func_register(&func_bool_not);
		func_register(&func_bool_and);
		func_register(&func_bool_or);
		func_register(&func_int_add);
		func_register(&func_int_sub);
		func_register(&func_int_mul);
		func_register(&func_int_div);
		func_register(&func_float_add);
		func_register(&func_float_sub);
		func_register(&func_float_mul);
		func_register(&func_float_div);
		func_register(&func_int_equ);
		func_register(&func_int_gt);
		func_register(&func_int_lt);
		func_register(&func_int_ge);
		func_register(&func_int_le);
		func_register(&func_int_ne);
		func_register(&func_float_equ);
		func_register(&func_float_gt);
		func_register(&func_float_lt);
		func_register(&func_float_ge);
		func_register(&func_float_le);
		func_register(&func_float_ne);
		func_register(&func_string_equ);
		func_register(&func_string_gt);
		func_register(&func_string_lt);
		func_register(&func_string_ge);
		func_register(&func_string_le);
		func_register(&func_string_ne);
		func_register(&func_string_length);
		func_register(&func_bool_equ);

/*		func_register(&func_double_add);
		func_register(&func_double_sub);
		func_register(&func_double_mul);
		func_register(&func_double_div);*/
		return 0;
}

