CC = gcc
CFLAGS = -Wall -Werror -g 
LIBS = -lsqlite3 -lsodium

SRCS = main.c library/library.c library/base64.c library/encrypt_decrypt.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: cpassmanager

cpassmanager: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o cpassmanager 

main.o: main.c library/library.h
	$(CC) $(CFLAGS) -c main.c

library/library.o: library/library.c library/library.h
	$(CC) $(CFLAGS) -c -o library/library.o library/library.c

library/base64.o: library/base64.c library/base64.h
	$(CC) $(CFLAGS) -c -o library/base64.o library/base64.c

library/encrypt_decrypt.o: library/encrypt_decrypt.c library/encrypt_decrypt.h
	$(CC) $(CFLAGS) -c -o library/encrypt_decrypt.o library/encrypt_decrypt.c
clean:
	rm -f $(OBJS) cpassmanager

