all:	cpu_tab.c lex.yy.c
	cl lex.yy.c cpu_tab.c /Fenail.exe

lex.yy.c:	cpu.lex
	flex cpu.lex

cpu_tab.c:	cpu.y
	bison -d cpu.y
		
