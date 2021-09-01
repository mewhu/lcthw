PREFIX?=/usr/local
CFLAGS=-g -Wall -I${PREFIX}/apr/include/apr-1
LDFLAGS=-L${PREFIX}/apr/lib -lapr-1 -lpthread -laprutil-1

all: devpkg

devpkg: bstrlib.o db.o shell.o commands.o

bstrlib.o: bstrlib.c bstrlib.h
	gcc -c bstrlib.c -o bstrlib.o

db.o: db.c db.h
	gcc -c ${CFLAGS} db.c -o db.o

install: all
	install -d $(DESTDIR)/$(PREFIX)/bin/
	install devpkg $(DESTDIR)/$(PREFIX)/bin/

clean:
	rm -rf *.o
	rm -f devpkg
	rm -rf *.dSYM
