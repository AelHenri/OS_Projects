#include "working_shell.h"
#include "built_in_functions.h"
#include "read_profile.h"

void type_prompt(){
	printf("> ");
}

// TODO: READ CHAR BY CHAR TO DETECT WHEN TAB OR ARROWS ARE PUSHED, INSTEAD OF USING GETLINE
int parse_line(char** line) {
	size_t bufsize = 0;
	getline(line, &bufsize, stdin);
	return 1;
}

int read_command(char *command, char **parameters) {
	char *line = NULL;
	parse_line(&line);

	if (strcmp(line, "\n") == 0) {
		free(line);
		line = NULL;
		return 0;
	}
	int position = 0;
	int maxtokens = MAXTOK;
	char **tokens = malloc(maxtokens * sizeof(char*));
	char *token;

	if (tokens == NULL) {
		fprintf(stderr, "Malloc failed.\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, SEPARATORS);
	while (token != NULL) {
		tokens[position] = token;
		position++;
		
		if (position >= maxtokens) {
			maxtokens += MAXTOK;
			tokens = realloc(tokens, maxtokens * sizeof(char *));
			if (tokens == NULL) {
				fprintf(stderr, "Realloc failed.\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, SEPARATORS);
	}
	tokens[position] = NULL;
	strcpy(command, tokens[0]);
	for (int i = 0; i < position; i++) {
		parameters[i] = malloc(TOKSIZE * sizeof(char));

		if (parameters[i] == NULL) {
			fprintf(stderr, "Malloc failed.\n");
			exit(EXIT_FAILURE);
		}

		strcpy(parameters[i], tokens[i]);
	}
	free(tokens);
	tokens = NULL;
	free(line);
	line = NULL;

	return position;
}

int execute_command(char *command, char **parameters, int param_size) {
	pid_t pid;
	int status;

	int builtin = check_for_builtin(command, parameters, param_size);
	if (builtin) return builtin;

	pid = fork();
	if (pid == 0) {
		if (execvp(command, parameters) == -1) {
			perror("Execvp");
		}		
		exit(EXIT_FAILURE);
	}
	else if (pid <0) {
		perror("Fork");
	}
	else {

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
		if (command == NULL) {
			fprintf(stderr, "Malloc failed.\n");
			exit(EXIT_FAILURE);
		}
		parameters = malloc(MAXTOK * sizeof(char *));
		if (parameters == NULL) {
			fprintf(stderr, "Malloc failed.\n");
			exit(EXIT_FAILURE);
		}

		type_prompt();
		param_size = read_command(command, parameters);

		if (param_size > 0) {
			status = execute_command(command, parameters, param_size);
		}
		
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
	read_profile();
	main_loop();
	return 0;
}