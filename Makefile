CFLAGS=-Wall -g

all: ex1 ex3 ex4 ex6 ex7

test: test.c
	gcc -o test ${CFLAGS} test.c

clean:
	rm -rf ex1 ex3 ex4 ex6 ex7

cleantest:
	rm -rf test
