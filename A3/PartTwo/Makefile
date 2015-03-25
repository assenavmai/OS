CC          =	gcc
# Flags that are sent to the compiler
# Do not change these
CFLAGS      =	-Wall -ansi -pedantic -g -pthread

#Directories where the compiler can find things
INCLUDES    = -Iinclude

# add directory names here if you want to separate files by directories
BINDIR = bin/
SRCDIR = src/

#Put the names of your source code file in the lines below.  

SRC_PHIL = $(SRCDIR)Queue.c $(SRCDIR)holes.c

#The names of the binary programs that will be produced.  
#
NAME_PHIL = $(BINDIR)holes


all : testing program


holes:
	$(CC) $(CFLAGS) $(SRC_PHIL) -o $(NAME_PHIL) $(INCLUDES)


clean:
	@ rm *.o



