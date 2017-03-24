CC = clang
CFLAGS  = -Wall -std=c99 -O0

LIBS = -pthread 

OBJ= working_shell.o\
	built_in_functions.o\
	read_profile.o\
	userinput.o\
	autocomplete.o\
	linkedlist.o\

OBJ2= built_in_functions.o\
	read_profile.o\
	userinput.o\
	autocomplete.o\
	linkedlist.o\
	working_shell_v2.o\
	command_queue.o\
	command_line.o\
	command_utilities.o\
	stack.o\
	queue.o\
	working_shell_utils.o\


SRC= working_shell.h\
	working_shell.c\
	built_in_functions.h\
	built_in_functions.c\
	read_profile.h\
	read_profile.c\
	userinput.h\
	userinput.c\
	autocomplete.h\
	autocomplete.c\
	linkedlist.h\
	linkedlist.c\
	working_shell_v2.h\
	working_shell_v2.c\
	command_queue.h\
	command_queue.c\
	command_line.h\
	command_line.c\
	command_utilities.h\
	command_utilities.c\
	stack.h\
	stack.c\
	queue.h\
	queue.c\
	working_shell_utils.h\
	working_shell_utils.c\

BIN= wshell

all: $(BIN)

wshell: working_shell.o built_in_functions.o read_profile.o userinput.o autocomplete.o
	$(CC) $(CFLAGS) $(OBJ) -o $@ 

wshell2: working_shell_v2.o built_in_functions.o read_profile.o userinput.o autocomplete.o command_queue.o command_line.o command_utilities.o stack.o queue.o working_shell_utils.o
	$(CC) $(CFLAGS) $(LIBS) $(OBJ2) -o $@ 

working_shell.o: working_shell.c built_in_functions.h built_in_functions.o read_profile.h read_profile.o userinput.h userinput.o
built_in_functions.o: built_in_functions.c
read_profile.o: read_profile.c
userinput.o: userinput.c
autocomplete.o: linkedlist.h linkedlist.o autocomplete.c 
linkedlist.o: linkedlist.c

working_shell_v2.o: working_shell_v2.c built_in_functions.h built_in_functions.o read_profile.h read_profile.o userinput.h userinput.o command_queue.o command_line.o command_utilities.o stack.o queue.o working_shell_utils.o
command_queue.o: command_queue.c
command_line.o: command_line.c
command_utilities.o: command_utilities.c
stack.o: stack.c
queue.o: queue.c
working_shell_utils.o: working_shell_utils.c

clean:
	rm -f $(OBJ) $(OBJ2) *~ 

cleanall: clean
	rm -rf $(BIN) core.*

.PHONY: all clean cleanall 
