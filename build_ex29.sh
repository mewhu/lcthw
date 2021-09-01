#!/bin/sh
gcc -c -fPIC libex29.c -o libex29.o
gcc -shared -o libex29.so libex29.o

gcc -Wall -g -DNDEBUG ex29.c -ldl -o ex29
