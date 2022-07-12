FILE := src/kav.c

CFLAGS := -march=native -O3 
TFILES := tests/test.c
CC = gcc

run:
	$(CC) $(FILE) $(CFLAGS) -o kav 
	./kav

testrun:
	$(CC) $(TFILES) $(CFLAGS) -o test
	./test
