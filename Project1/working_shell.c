#include "working_shell.h"
#include "built_in_functions.h"
#include "read_profile.h"
#include "userinput.h"
#include "autocomplete.h"

#define ALARM_SECS 5

extern int ISCLOCK;
Autocomplete *autocomplete;

void type_prompt(){
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	if (cwd) {	
		printf("%s%s #%s ", GRN, cwd, NRM);
	} 
	else {
		printf("%s#%s ", GRN, NRM);	
	}
}

void runClock(int pid, int seconds) {
	int status;
	int counter = 0;
	int usecs = seconds*1e6;
	while (waitpid(pid, &status, WNOHANG) == 0 && counter < usecs) {
		usleep(1e5);
		counter+=1e5;
	}
	if (counter >= usecs) {
		printf("%sThis process is taking too much time to terminate.%s Would you like to interrupt it ? [y][n]\n", RED, NRM);
		char c = getchar();
		if (c == 'y') {
			kill(pid, SIGKILL);
			printf("Killed child process.\n");
		}
		else {
			printf("Letting the process run.\n");
		}
	}
}

int parse_line(char** line) {
	user_input(line);
	return 1;
}

int read_command(char *command, char **parameters) {
	char *line = NULL;
	parse_line(&line);

	if (line[0] == '\0') {
		free(line);
		line = NULL;
		return 0;
	}
	int position = 0;
	int maxtokens = MAXTOK;
	char **tokens = malloc(maxtokens * sizeof(char*));
	char *token;

	if (tokens == NULL) {
		fprintf(stderr, "%sMalloc failed.%s\n", RED, NRM);
		exit(EXIT_FAILURE);
	}

	token = strtok(line, SEPARATORS);
	while (token != NULL) {
		tokens[position] = token;
		position++;
		token = strtok(NULL, SEPARATORS);
	}
	tokens[position] = NULL;
	strcpy(command, tokens[0]);
	for (int i = 0; i < position; i++) {
		parameters[i] = malloc(TOKSIZE * sizeof(char));

		if (parameters[i] == NULL) {
			fprintf(stderr, "%sMalloc failed.%s\n", RED, NRM);
			exit(EXIT_FAILURE);
		}

		strcpy(parameters[i], tokens[i]);
	}
	free(tokens);
	tokens = NULL;
	free(line);
	line = NULL;
	//printf("\n");

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
		if (ISCLOCK){
			runClock(pid, ALARM_SECS);
		}
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
			fprintf(stderr, "%sMalloc failed.%s\n", RED, NRM);
			exit(EXIT_FAILURE);
		}
		parameters = malloc(MAXTOK * sizeof(char *));
		if (parameters == NULL) {
			fprintf(stderr, "%sMalloc failed.%s\n", RED, NRM);
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
	autocomplete = (Autocomplete*) malloc(sizeof(Autocomplete));
	init(&autocomplete);
	parseHistory(&autocomplete, ".history");
	read_profile();
	main_loop();
	saveHistory(&autocomplete, ".history");
	deleteAll(&autocomplete);
	free(autocomplete);

	return 0;
}