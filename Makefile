edit:Simple.tab.o lex.yy.o
	gcc -o Simple Simple.tab.o lex.yy.o -lm

Simple.tab.o:Simple.tab.c SM.h ST.h CG.h
	gcc -c Simple.tab.c

lex.yy.o:lex.yy.c Simple.tab.h
	gcc -c lex.yy.c

Simple.tab.c Simple.tab.h:Simple.y
	bison -d Simple.y

lex.yy.c:Simple.lex
	flex Simple.lex

clean:
	rm -rf *.o Simple.tab.c lex.yy.c Simple.tab.h Simple
