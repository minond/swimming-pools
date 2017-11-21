CC = cc
CFLAGS = -std=c11 -W -Wall

build:
	$(CC) $(CFLAGS) main.c pools.c -o pools
