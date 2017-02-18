#include "built_in_functions.h"

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

int builtin_exit(char *command, char **parameters, int param_size) {
	free(command);
	for (int i=0; i<param_size; i++) {
		free(parameters[i]);
	}
	free(parameters);
	exit(EXIT_SUCCESS);
}

int check_for_builtin(char *command, char **parameters, int param_size) {
	if (strcmp(command, "cd") == 0) {
		return builtin_cd(parameters);
	}
	else if (strcmp(command, "exit") == 0) {
		return builtin_exit(command, parameters, param_size);
	}
	return 0;
}
