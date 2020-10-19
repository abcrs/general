CFLAGS	= -Wall -g
CC		= gcc $(CFLAGS)

all : bl_client bl_server

bl_client : bl_client.o
		$(CC) -o bl_client bl_client.o simpio.o blather.h -lpthread

bl_server : bl_server.o
		$(CC) -o bl_server bl_server.o server_funcs.o blather.h

bl_server.o : server_funcs.o
		$(CC) -c bl_server.c blather.h

server_funcs.o : blather.h
		$(CC) -c server_funcs.c blather.h

bl_client.o : simpio.o
		$(CC) -c bl_client.c blather.h

simpio.o : blather.h
		$(CC) -c simpio.c blather.h

util.o : blather.h
		$(CC) -c util.c blather.h

clean :
		rm -f bl_server bl_client *.o

include test_Makefile
