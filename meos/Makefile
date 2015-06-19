all: install

kernel: kernel.o entry.o clib.o page.o gdt.o vga.o process.o key.o dma.o floppy.o ext2.o
	ld -o kernel -Ttext 0x100000 -N -e start entry.o kernel.o clib.o page.o gdt.o key.o ext2.o vga.o process.o dma.o floppy.o && objcopy -R .note -R .comment -S -O binary kernel meos

process.o: process.c process.h
	gcc -O2 -c -I. process.c
	
kernel.o: kernel.c vga.h key.h string.h clib.h page.h
	gcc -O2 -c -I. kernel.c clib.c

clib.o:	clib.c clib.h
	gcc -O2 -c -I. clib.c
	
entry.o: entry.S
	gcc -c entry.S

page.o: page.c page.h
	gcc -O2 -c -I. page.c

vga.o: vga.c vga.h clib.h
	gcc -O2 -c -I. vga.c
	
install: kernel
	cp kernel /mnt/boot/boot/meos && sync

gdt.o: gdt.h gdt.c
	gcc -O2 -c -I. gdt.c

key.o: key.h key.c
	gcc -O2 -c -I. key.c

dma.o: dma.c dma.h
	gcc -O2 -c -I. dma.c
	
floppy.o: floppy.c floppy.h
	gcc -O2 -c -I. floppy.c

ext2.o: ext2.c ext2.h
	gcc -O2 -c -I. ext2.c
	
clean:
	rm *.o kernel meos

