CC=gcc

CCWIN=x86_64-w64-mingw32-gcc

IFLAGS=-Iinclude

WFLAGS=-Wall

GFLAG=-g

OBJS = src/*.c

EXEC_NAME = Exec

finalmake : $(OBJS)
		$(CC) $(GFLAG) $(WFLAGS) $(IFLAGS) $(OBJS) -o $(EXEC_NAME) 
