#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#define TRUE 1

void type_prompt();
void read_command(char *command, char *parameters);
