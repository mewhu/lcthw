CFLAGS=-Wall -g

all: ex1 ex3 ex4 ex6 ex7 ex9 ex10 ex14 ex15 ex16 ex17 ex18

ex17: ex17.c ex17.h
	gcc -o $@ ${CFLAGS} $@.c

test: test.c
	gcc -o test ${CFLAGS} test.c

clean:
	rm -rf ex1 ex3 ex4 ex6 ex7 ex9 ex10 ex14 ex15 ex16 ex17 ex18

cleansym:
	rm -rf ex*dSYM

cleantest:
	rm -rf test
