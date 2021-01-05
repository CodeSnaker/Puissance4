CC=gcc

CCWIN=x86_64-w64-mingw32-gcc

IFLAGS=-Iinclude

WFLAGS=-Wall

GFLAG=-g

<<<<<<< HEAD
OBJS = src/*.c
=======
OBJS = src/partie.c src/main.c src/safeinput.c src/SaveAndSettings.c
>>>>>>> e7bd97aa29a20478d1d7e37c848f7cd8a004752d

EXEC_NAME = Exec

finalmake : $(OBJS)
		$(CC) $(GFLAG) $(WFLAGS) $(IFLAGS) $(OBJS) -o $(EXEC_NAME) 
