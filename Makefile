#To run, put this file together with lexer.h, and lexer.c
#in the same directory. Run "make". Then the executable
#is "scheme," which just takes a line of input and
#breaks it up into tokens.

scheme: parser.o evaltester.o lexer.o evaluator.o
	gcc -o runschemeII evaltester.o lexer.o parser.o evaluator.o

evaluator.o: evaluator.c
	gcc -c evaluator.c

parser.o: parser.c
	gcc -c parser.c

evaltester.o: evaltester.c
	gcc -c evaltester.c

lexer.o: lexer.c
	gcc -c lexer.c

clean:
	rm -f *~ *.o *.a runschemeII

#^^^^^^This space must be a TAB!!.
