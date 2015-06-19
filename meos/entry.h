typedef struct
{
	char *base;
	size_t size;
} mmap_t;

void * stacktop;
size_t memlower;
size_t memupper;
int bootdev;
char * cmdline;
int nmmap;
mmap_t *mmap;

