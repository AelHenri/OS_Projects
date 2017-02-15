#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define TOKSIZE 32
#define MAXTOK 10
#define SEPARATORS " \t\r\n\a"

int builtin_cd(char **parameters) {
	if (parameters[1] == NULL) {
		fprintf(stderr, "Expected argument\n");
	}
	else {
		chdir(parameters[1]);
		// error handling
	}
	return 1;
}

int builtin_exit() {
	exit(EXIT_SUCCESS);
}

int check_for_builtin(char *command, char **parameters) {
	if (strcmp(command, "cd") == 0) {
		return builtin_cd(parameters);
	}
	else if (strcmp(command, "exit") == 0) {
		return builtin_exit();
	}
	return 0;
}

/*
//////////////////                //////////////////
////////////////// SEPARATE FILES ////////////////// 
//////////////////                ////////////////// 
*/

void type_prompt(){
	printf("> ");
}

int read_command(char *command, char **parameters) {
	char *line = NULL;
	size_t bufsize = 0;
	getline(&line, &bufsize, stdin);

	int position = 0;
	char **tokens = malloc(MAXTOK * sizeof(char*));
	char *token;

	// malloc error handling

	token = strtok(line, SEPARATORS);
	while (token != NULL) {
		tokens[position] = token;
		position++;
		// realloc ?

		token = strtok(NULL, SEPARATORS);
	}
	tokens[position] = NULL;
	strcpy(command, tokens[0]);
	for (int i = 0; i < position; i++) {
		parameters[i] = malloc(TOKSIZE * sizeof(char));
		strcpy(parameters[i], tokens[i]);
	}
	free(tokens);
	tokens = NULL;

	return position;
}

int execute_command(char *command, char **parameters) {
	pid_t pid;
	int status;

	int builtin = check_for_builtin(command, parameters);
	if (builtin) return builtin;

	pid = fork();
	if (pid == 0) {
		execvp(command, parameters);
		// error handling
		exit(EXIT_FAILURE);
	}
	else if (pid != 0) {
		// More error handling
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}

void main_loop() {
	char *command;
	char **parameters;

	int status = 1;
	int param_size = 0;

	while(status) {
		command = malloc(TOKSIZE * sizeof(char));
		parameters = malloc(MAXTOK * sizeof(char *));

		type_prompt();
		param_size = read_command(command, parameters);
		status = execute_command(command, parameters);
		
		free(command);
		command = NULL;
		for (int i = 0; i < param_size; i++) {
			free(parameters[i]);
			parameters[i] = NULL;
		}
		free(parameters);
		parameters = NULL;
	}
}

int main(int argc, char const *argv[])
{
	main_loop();
	return 0;
}