bc.o: bc.c bc.h
	cc -c bc.c -Wall
main.o: main.c
	cc -c main.c -Wall
project: main.o bc.o
	cc main.o bc.o -o project
