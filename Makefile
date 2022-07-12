FILES := src/kav.c

CFLAGS := -march=native -O3 
CC = gcc

default:
	$(CC) $(FILES) $(CFLAGS) -o kav 

test:
	$(CC) $(FILES) $(CFLAGS) -o test
	./test term-info
	./test monitor-count
	./test resolution
	./test ip
	
