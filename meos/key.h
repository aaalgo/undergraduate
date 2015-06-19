#ifndef __MEOS_KEY__
#define __MEOS_KEY__

#define KEY_ALTF1 -1
#define KEY_ALTF2 -2
#define KEY_ALTF3 -3
#define KEY_ALTF4 -4
#define KEY_ESC -5

extern void key_init (void);

extern int getvc (void);
extern int getc (void);
extern char *__gets (char *, int);

#define gets(a) __gets(a, 1)
#define hgets(a) __gets(a, 0)

#endif
