CFLAGS=-Wall -g -D NDEBUG

all: ex1 ex3 ex4 ex6 ex7 ex9 ex10 ex14 ex15 ex16 ex17 ex18 ex19 ex20 ex22_main ex23

ex17: ex17.c ex17.h
	gcc -o $@ ${CFLAGS} $@.c

ex19: object.o

ex20: dbg.h

ex22_main: ex22.o
	gcc -o ex22_main ex22.o ex22_main.c

test: test.c
	gcc -o test ${CFLAGS} test.c

clean: cleanobject
	rm -rf ex1 ex3 ex4 ex6 ex7 ex9 ex10 ex14 ex15 ex16 ex17 ex18 ex19 ex20 ex22_main
	rm -rf ex23

cleansym:
	rm -rf ex*dSYM

cleantest:
	rm -rf test

cleanobject:
ifneq (,$(wildcard *.o))
	rm *.o
endif
