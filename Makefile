CC = gcc
CCFLAGS = -Wall
SRC = problema1.c
PROGRAM = problema1


all:
	$(CC) -o $(PROGRAM) $(SRC) $(CCFLAGS)


.PHONY : clean
clean :
	rm -f $(PROGRAM) core *~


