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

#define TOKSIZE 32
#define MAXTOK 10
#define SEPARATORS " \t\r\n\a"

void type_prompt();
int read_command(char *command, char **parameters);
int execute_command(char *command, char **parameters, int param_size);
void main_loop();

#endif