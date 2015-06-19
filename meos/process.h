/* filename: process.h
   by Dong Wei */
#ifndef __MEOS_PROCESS_
#define __MEOS_PROCESS_

typedef struct __pcb pcb_t;
struct __pcb
{
	tss_t tss;
	sel_t sel;
	pcb_t *prev;
	pcb_t *next;
	pcb_t *lprev;
	pcb_t *lnext;
	u32 sleep;
	int pid;
	int state;
	char cmdline[128];
};

extern volatile pcb_t *current;
extern volatile int critical;
extern int schedule (void);
extern int process_init (void);
pcb_t *create_process (void *start, void *param, char *cmdline);
extern void exit (int f);
static inline void begin_critical_section (void)
{
	critical = TRUE;
}

static inline void end_critical_section (void)
{
	critical = FALSE;
}

typedef struct
{
	pcb_t *wait;
	int n;
} sem_t;

#define SEM_INIT {NULL, 0}

static inline int sem_init (sem_t *sem)
{
	sem->wait = NULL;
	sem->n = 0;
}

static inline int sem_init_set (sem_t *sem, int n)
{
	sem->wait = NULL;
	sem->n = n;
}

extern int sem_p (sem_t *sem);
extern int sem_v (sem_t *sem);

extern int sem_destroy (sem_t *sem);

extern void dump_ps (void);

#define STATE_RUNNING 0
#define STATE_ACTIVE 1
#define STATE_SLEEP 2
#define STATE_BLOCK 3

#endif
