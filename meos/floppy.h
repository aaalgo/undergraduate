/* filename: floppy.h
   by Dong Wei */
#ifndef __MEOS_FLOPPY_
#define __MEOS_FLOPPY_
int floppy_reset (void);
int floppy_read (int sector, void *buf);
int floppy_write (int sector, void *buf);
#endif
