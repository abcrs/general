CFLAGS = -Wall -g
CC     = gcc $(CFLAGS)

commando : commando.o
	$(CC) -o commando commando.o cmd.o cmdcol.o util.o commando.h
	@echo commando is ready

commando.o : cmdcol.o cmd.o util.o commando.h
	$(CC) -c commando.c commando.h

cmdcol.o : cmdcol.c util.o commando.h
	$(CC) -c cmdcol.c commando.h

cmd.o : cmd.c util.o commando.h
	$(CC) -c cmd.c commando.h

util.o : commando.h
	$(CC) -c util.c commando.h

clean:
	rm -f commando *.o

include test_Makefile
