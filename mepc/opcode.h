/* filename: opcode.h
   Definition of opcode of the virtual machine.
   Generated by gen_opcode, DO NOT touch it. */
#ifndef __PASCAL_OPCODE__
#define __PASCAL_OPCODE__

#define OP_NOP	0
#define OP_ADD	1
#define OP_ANS	2
#define OP_SUB	3
#define OP_MUL	4
#define OP_DIV	5
#define OP_MOD	6
#define OP_NEG	7
#define OP_FADD	8
#define OP_FSUB	9
#define OP_FMUL	10
#define OP_FDIV	11
#define OP_GLOBAL	12
#define OP_CIF	13
#define OP_CFI	14
#define OP_NOT	15
#define OP_AND	16
#define OP_OR	17
#define OP_CTEMP	18
#define OP_SHL	19
#define OP_SHR	20
#define OP_JMP	21
#define OP_JGT	22
#define OP_JLT	23
#define OP_JEQ	24
#define OP_JNE	25
#define OP_JGE	26
#define OP_JLE	27
#define OP_PARAM	28
#define OP_ALLOC	29
#define OP_CALL	30
#define OP_CCALL	31
#define OP_RET	32
#define OP_MRET	33
#define OP_ADDR	34
#define OP_PEEK	35
#define OP_POKE	36
#define OP_TEMP	37
#define OP_LABEL	38
#define OP_MOVE	39
#define OP_TITLE	40
#define OP_END	41
#define OP_PROC	42
#define OP_ENDP	43
extern char *opcode_symbol[];
extern int op_max;
#endif
