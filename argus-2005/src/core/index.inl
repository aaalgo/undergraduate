/* dynamic priority calculating function,
   usgin o->priority and o->nice. */

static __inline int index (schedopr_t *o)
{
	int n = o->priority + (buffer_count(o->buffer) >> 5);
	n /= PRIORITY_WEIGHT;
	n = SCHED_BUCKET_NUM - n;
	if (n < 0) n = 0;
	return n;
}

