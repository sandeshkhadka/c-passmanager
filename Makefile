CC = gcc
CFLAGS = -Wall -Werror -g
LIBS = -lsqlite3

SRCS = main.c library/library.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: cpassmanager

cpassmanager: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o cpassmanager 

main.o: main.c library/library.h
	$(CC) $(CFLAGS) -c main.c

library/library.o: library/library.c library/library.h
	$(CC) $(CFLAGS) -c -o library/library.o library/library.c

clean:
	rm -f $(OBJS) cpassmanager

