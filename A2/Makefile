CC          =	gcc
# Flags that are sent to the compiler
# Do not change these
CFLAGS      =	-Wall -ansi -pedantic -g

#Directories where the compiler can find things
INCLUDES    = -Iinclude

# add directory names here if you want to separate files by directories
BINDIR = bin/
SRCDIR = src/

#Put the names of your source code file in the lines below.  

SRC_PQ = $(SRCDIR)PQueue.c $(SRCDIR)main.c $(SRCDIR)QStruct.c $(SRCDIR)Queue.c
SRC_Q = $(SRCDIR)QStruct.c $(SRCDIR)main.c $(SRCDIR)Queue.c


#The names of the binary programs that will be produced.  
#
NAME_PQ = $(BINDIR)simcpu
NAME_Q= $(BINDIR)q


all : testing program


simcpu:
	$(CC) $(CFLAGS) $(SRC_PQ) -o $(NAME_PQ) $(INCLUDES)
q:
	$(CC) $(CFLAGS) $(SRC_Q) -o $(NAME_Q) $(INCLUDES)

clean:
	@ rm *.o



