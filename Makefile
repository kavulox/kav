FILE := src/kav.c

CFLAGS := -march=native -O3 
CC = gcc

default:
	$(CC) $(FILE) $(CFLAGS) -o kav 

test:
	$(CC) $(FILE) $(CFLAGS) -o test
	./test term-info
	./test monitor-count
	./test resolution
	./test ip
	
