#include <stdlib.h>
#include <cmnhdr.h>
#include <config.h>
#include <libtype.h>
#include <schema.h>


int schema_encode (void *sch, void *out, int bufsize)
{
	int i, size;
	schema_t *sin;
	schema_t *sout;
	sin = *(schema_t **)sch;
	size = schema_size(sin);
	if (bufsize < size) return size;
	sout = (schema_t *)out;
	memcpy(sout, sin, size);
	for (i = 0; i < sout->nof; i++)
	{
		sout->field[i].type = (type_t *)sout->field[i].type->id;
	}
	return size;
}

int schema_decode (void *sch, void *in)
{
	int i, size;
	schema_t *sin = (schema_t *)in;
	schema_t *sout = schema_alloc(sin->nof);
	size = schema_size(sin);
	memcpy(sout, sin, size);
	for (i = 0; i < sout->nof; i++)
	{
		sout->field[i].type = type_from_id((int)sout->field[i].type);
	}
	*(schema_t **)sch = sout;
	return size;
}

int tuple_encode (schema_t *schema, void *tuple, void *buffer, int buf_size)
{
	int i, ret;
	char *t, *b;
	t = tuple;
	b = buffer;
	for (i = 0; i < schema->nof; i++)
	{
		if (schema->field[i].type->encode != NULL)
		{
			ret = schema->field[i].type->encode(t, b, buf_size);
		}
		else
		{
			ret = schema->field[i].type->size;
			if (ret <= buf_size)
				memcpy(b, t, ret);
		}
		buf_size -= ret;
		if (buf_size < 0) break;
		b += ret;
		t += schema->field[i].type->size;
	}
	if (buf_size < 0) return -1;
	return b - (char *)buffer;
}

int tuple_decode (schema_t *schema, void *tuple, void *buffer)
{
	int i, ret;
	char *t, *b;
	t = tuple;
	b = buffer;
	for (i = 0; i < schema->nof; i++)
	{
		if (schema->field[i].type->decode != NULL)
		{
			ret = schema->field[i].type->decode(t, b);
		}
		else
		{
			ret = schema->field[i].type->size;
			memcpy(t, b, ret);
		}
		b += ret;
		t += schema->field[i].type->size;
	}
	return 0;
}
