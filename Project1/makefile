CC = clang
CFLAGS  = -Wall -std=c99 -g -O0
#LIBS = -lncurses

PEPPER=../data/pepper.ppm

OBJ= working_shell.o\
	built_in_functions.o\
	read_profile.o\
	userinput.o\

SRC= working_shell.h\
	working_shell.c\
	built_in_functions.h\
	built_in_functions.c\
	read_profile.h\
	read_profile.c\
	userinput.h\
	userinput.c

BIN= wshell

all: $(BIN)

wshell: working_shell.o built_in_functions.o read_profile.o userinput.o
	$(CC) $(CFLAGS) $(OBJ) -o $@ 

working_shell.o: working_shell.c built_in_functions.h built_in_functions.o read_profile.h read_profile.o userinput.h userinput.o
built_in_functions.o: built_in_functions.c
read_profile.o: read_profile.c
userinput.o: userinput.c


clean:
	rm -f $(OBJ) *~ 

cleanall: clean
	rm -rf $(BIN) core.*

.PHONY: all clean cleanall 
