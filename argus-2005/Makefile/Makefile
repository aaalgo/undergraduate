CFLAGS =  -I"..\include" -DWIN32 /MT
CC = cl
OBJS = libtype.obj core.obj btype.obj stream.obj udp.obj sql_help.obj test.obj opt.obj osdept.obj sql.tab.obj lex.sql.obj count_window.obj timeSlide_window.obj timeTumble_window.obj
 
all:	$(OBJS)
	cl /MT /Fetest.exe $(OBJS) ws2_32.lib
	
	
yacc:	sql.y
	bison -d -p sql sql.y -o sql.tab.c

lex:	sql.lex
	flex -olex.sql.c -Psql sql.lex

clean:
	del *.obj  *.tds test.exe

