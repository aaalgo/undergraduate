/* filename: entry.S
   by Dong Wei */

#define MB_MAGIC	0x1badb002
#define MB_LOAD_MAGIC	0x2badb002
#define MB_FLAG		0x00010002
#define MB_CHECKSUM	-(MB_MAGIC + MB_FLAG)
#define LOAD_ADDR	0x100000
#define TEXT_SIZE	0x200000
#define BSS_SIZE	0x100000
#define LOAD_END	(LOAD_ADDR + TEXT_SIZE)
#define BSS_END		(LOAD_END + BSS_SIZE)
#define STACKTOP	BSS_END
#define CODESEL		(code_gdt - gdt)
#define DATASEL		(data_gdt - gdt)
#define INT_VECTOR_LOW	0x00
#define INT_VECTOR_HIGH	0x06
	
#define BI_FLAGS	0
#define BI_MEMLOWER	4
#define BI_MEMUPPER	8
#define BI_DEVICE	12
#define BI_CMDLINE	16
#define BI_MMAP_LEN	44
#define BI_MMAP_ADDR	48
#define BI_MMAP_SIZE	0
#define BI_MMAP_BASE	4
#define BI_MMAP_LENGTH	12
#define BI_MMAP_TYPE	20
#define BI_MMAP_AVAIL	1
#define MMAP_SIZE	8

.data
.global	memlower, memupper, bootdev, nmmap, mmap, cmdline
.global stacktop, gdt, gdtend, gdtr, gdtr_lim, gdtr_gdt
.align 4, 0
	.word 0
gdtr:
gdtr_lim:
	.word gdtend - gdt - 1
gdtr_gdt:
	.long gdt
gdt:	.long 0x0
	.long 0x0	/* the null descriptor */
code_gdt:
	.word 0xffff
	.word 0x0000
	.byte 0x00
	.byte 0x9a
	.byte 0xcf
	.byte 0x00
data_gdt:
	.word 0xffff
	.word 0x0000
	.byte 0x00
	.byte 0x92
	.byte 0xcf
	.byte 0x00
gdtend:

.align 4, 0
	.word 0
idtr:	.word idtend - idt - 1
	.long idt
idt:
/* div0 */
	.long 0x0
	.long 0x0
/* step */
	.long 0x0
	.long 0x0
/* NMI */
	.long 0x0
	.long 0x0
/* break */
	.long 0x0
	.long 0x0
/* overflow */
	.long 0x0
	.long 0x0
/* bind */
	.long 0x0
	.long 0x0
/* opcode */
	.long 0x0
	.long 0x0
/* coproc */
	.long 0x0
	.long 0x0
/* IRQ0, timer */
	.word 0x0
	.word CODESEL
	.byte 0x0
	.byte 0x8E
	.word 0x0
/* IRQ1, keyboard */	
   	.word 0x0
	.word CODESEL
	.byte 0x0
	.byte 0x8E
	.word 0x0
/* IRQ2 */
	.word 0x0
	.word CODESEL
	.byte 0x0
	.byte 0x8E
	.word 0x0
/* com2 */
	.word 0x0
	.word CODESEL
	.byte 0x0
	.byte 0x8E
	.word 0x0
/* com1 */
	.word 0x0
	.word CODESEL
	.byte 0x0
	.byte 0x8E
	.word 0x0
/* IRQ5 */
	.word 0x0
	.word CODESEL
	.byte 0x0
	.byte 0x8E
	.word 0x0
/* floppy */
	.word 0x0
	.word CODESEL
	.byte 0x0
	.byte 0x8E
	.word 0x0
idtend:

int_vector:
	.long int_div0
	.long int_step
	.long int_NMI
	.long int_break
	.long int_overflow
	.long int_bind
	.long int_opcode
	.long int_coproc
	.long int_timer
	.long int_key
	.long int_IRQ2
	.long int_com2
	.long int_com1
	.long int_IRQ5
	.long int_floppy
	.long 0x0
int_vector_end:
stacktop:	.long STACKTOP
memlower:	.long 0x0	/* size of lower memory */
memupper:	.long 0x0	/* size of upper memory */
bootdev:	.long 0x0	/* boot device */
cmdline:	.long 0x0	/* pointer to cmdline */
nmmap:		.long 0x0	/* # of items in mmap */
mmap:		.long 0x0	/* pointer to mmap */

.text
.globl	start
start:	jmp entry
.align 4, 0
multiboot:		/* used by grub to load the kernel image */
	.long MB_MAGIC	/* magic */
	.long MB_FLAG	/* flags, require information on available memory */
	.long MB_CHECKSUM	/* checksum */
	.long multiboot	/*header_addr */
	.long LOAD_ADDR	/* load_addr */
	.long LOAD_END	/* load_end_addr */
	.long BSS_END	/* bss_end_addr */
	.long entry	/* entry_addr */
	.long 1		/* mode_type, EGA-standard text mode */
	.long 80	/* width */
	.long 25	/* height */
	.long 0		/* depth */

/* machine state when entry is invoked:
   CS:	r/w code, 0-0xFFFFFFFF
   DS, ES, FS, GS, SS: r/w data, 0-0xFFFFFFFF
   address 20 line enabled
   paging turned off
   IF = 0
   EAX = MB_MAGIC
   EBX = pointer to multiboot information structure
 */
entry:	cmpl $MB_LOAD_MAGIC, %eax
	jnz entry	/* check for the magic number */
	/* load gdtr */
	lgdt gdtr
	ljmp $CODESEL, $1f
1:	movw $DATASEL, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %ss
	movw %ax, %fs
	movw %ax, %gs
/* process multiboot information */
	movl BI_FLAGS(%ebx), %eax
	testl $(1<<0), %eax
	jz spin
	testl $(1<<1), %eax
	jz spin
	testl $(1<<6), %eax
	jz spin
	movl $(STACKTOP + BSS_SIZE), %esp
	movl BI_MEMLOWER(%ebx), %eax
	movl %eax, memlower
	movl BI_MEMUPPER(%ebx), %eax
	movl %eax, memupper
	movl BI_DEVICE(%ebx), %eax
	movl %eax, bootdev
	movl $STACKTOP, stacktop
	/* count strlen(cmdline) */
	xorb %al, %al
	movl BI_CMDLINE(%ebx), %edi
	cld
	xorl %ecx, %ecx
	notl %ecx
repnz	cmpsb
	incl %edi
	subl BI_CMDLINE(%ebx), %edi
	/* copy cmdline to proper address */
	subl %edi, stacktop
	movl %edi, %ecx
	movl BI_CMDLINE(%ebx), %esi
	movl stacktop, %edi
	movl %edi, cmdline
	addl %ecx, %ecx
	addl %ecx, %ecx
rep	movsb	
	/* count mmap item number */
	movl BI_MMAP_ADDR(%ebx), %esi
	movl %esi, %edx
	xorl %ecx, %ecx
	addl BI_MMAP_LEN(%ebx), %edx
2:	cmpl $BI_MMAP_AVAIL, BI_MMAP_TYPE(%esi)
	jnz 1f
	incl %ecx
	subl $MMAP_SIZE, stacktop
1:	addl BI_MMAP_SIZE(%esi), %esi
	addl $4, %esi
	cmpl %esi, %edx
	ja 2b
	movl stacktop, %edi
	movl %edi, mmap
	movl %ecx, nmmap
	movl BI_MMAP_ADDR(%ebx), %esi
2:	cmpl $BI_MMAP_AVAIL, BI_MMAP_TYPE(%esi)
	jnz 1f
	movl BI_MMAP_BASE(%esi), %eax
	xor %ecx, %ecx
	cmpl $LOAD_ADDR, %eax
	js  4f
	cmpl $BSS_END, %eax
	jae 4f
	movl $BSS_END, %ecx
	subl %eax, %ecx
	movl $BSS_END, %eax
4:	pushl %ecx
	stosl
	mov BI_MMAP_LENGTH(%esi), %eax
	popl %ecx
	sub %ecx, %eax
	stosl
1:	addl BI_MMAP_SIZE(%esi), %esi
	addl $4, %esi
	cmpl %esi, %edx
	ja 2b
	/* process int table */
	movl $idt, %edi
	movl $int_vector, %esi
	cld
2:	lodsl
	orl %eax, %eax
	jz 3f
	movw %ax, INT_VECTOR_LOW(%edi)
	shrl $16, %eax
	movw %ax, INT_VECTOR_HIGH(%edi)
	addl $8, %edi
	jmp 2b
3:	call init
	lidt idtr
	mov stacktop, %esp
	sti
	call main
	cli
	call cleanup
spin:	jmp spin

/* interrupt handlers */
int_div0:
	jmp int_end
int_step:
	jmp int_end
int_NMI:
	jmp int_end
int_break:
	jmp int_end
int_overflow:
	jmp int_end
int_bind:
	jmp int_end
int_opcode:
	jmp int_end
int_coproc:
	jmp int_end
int_timer:		/* IRQ0 */
	call do_timer
	jmp int_end
int_key:		/* IRQ1 */
	call do_key
	jmp int_end
int_IRQ2:
	jmp int_end
int_com2:
	jmp int_end
int_com1:
	jmp int_end
int_IRQ5:
	jmp int_end
int_floppy:
	call do_floppy
	jmp int_end
int_end:
	iret
