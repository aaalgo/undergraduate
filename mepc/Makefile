CC = /usr/bin/gcc -g
#CC = checkergcc -g
all: opcode_gen build doc

opcode_gen: gen_opcode opcode.def opcode.c
	./gen_opcode
	
build: hash.o info.o mips.o table.o i386 main.o opt.o vm.o lex entry.o help.o vmgen.o opcode.o opcode.h opcode.o
	${CC} hash.o info.o mips.o table.o i386.o main.o opt.o vm.o entry.o help.o vmgen.o opcode.o lex.yy.o pascal.tab.o -o test/mepc

i386: i386.c opcode.i386
	${CC} -c i386.c
	
lex: yacc pascal.lex
	flex -i pascal.lex && ${CC} -c lex.yy.c

yacc: pascal.y
	bison -dv pascal.y && ${CC} -c pascal.tab.c
	
clean:
	rm *.o pas y.* lex.yy.c test/mepc gen_opcode test/hello test/hello.asm
