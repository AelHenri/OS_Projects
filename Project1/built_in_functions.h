#ifndef BUILTIN
#define BUILTIN

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int builtin_cd(char **parameters);
int builtin_exit(char *command, char **parameters, int param_size);
int check_for_builtin(char *command, char **parameters, int param_size);

#endif