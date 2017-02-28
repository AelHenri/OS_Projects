#include "built_in_functions.h"
#include "autocomplete.h"

int ISCLOCK=1;
extern Autocomplete *autocomplete;
extern char *HOME;

int builtin_cd(char **parameters) {
	if (parameters[1] == NULL) {
		if (HOME) chdir(HOME);
		else fprintf(stderr, "No HOME folder set; Argument expexted.\n");
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
	saveHistory(&autocomplete, ".history");
	deleteAll(&autocomplete);
	free(autocomplete);
	autocomplete = NULL;
	free(parameters);
	parameters = NULL;
	exit(EXIT_SUCCESS);
}

int builtin_clock() {
	ISCLOCK = 1-ISCLOCK;
	return 1;
}

int check_for_builtin(char *command, char **parameters, int param_size) {
	if (strcmp(command, "cd") == 0) {
		return builtin_cd(parameters);
	}
	else if (strcmp(command, "exit") == 0) {
		return builtin_exit(command, parameters, param_size);
	}
	else if (strcmp(command, "clock") == 0) {
		return builtin_clock();
	}
	return 0;
}


