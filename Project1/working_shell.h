#ifndef WORKING_SHELL
#define WORKING_SHELL

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <signal.h>
//#include <ncurses.h>


#define TOKSIZE 128
#define MAXTOK 10
#define SEPARATORS " \t\r\n\a"

#define NRM  "\x1B[0m"
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"
#define MAG  "\x1B[35m"
#define CYN  "\x1B[36m"
#define WHT  "\x1B[37m"

void type_prompt();
int read_command(char *command, char **parameters);
int execute_command(char *command, char **parameters, int param_size);
void main_loop();

#endif