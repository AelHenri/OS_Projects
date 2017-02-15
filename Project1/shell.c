#include "shell.h"
#define space " \t\r\n\a"
#define BUFFSIZE 64

void type_prompt(){
	printf("> ");
}

void read_command(char *command, char *parameters[]){
	int position = 0;
	char* input;
	char* buffer = malloc(sizeof(char *));
	char** tokens = malloc(BUFFSIZE * sizeof(char *));
	ssize_t bufsize=0;
	getline(&buffer, &bufsize, stdin);
	input = strtok(buffer, space);

	while( input != NULL){
		tokens[position] = input;
		position++;
		
		input = strtok(NULL, space);
	}
	
	strcpy(command, tokens[0]);

	for (int i = 0; i < position; ++i)
	{
		parameters[i] = malloc(sizeof(char *));
		strcpy(parameters[i], tokens[i]);
		free(tokens[i]);
	}
	free(tokens);
	free(buffer);
}

/*
void main_loop() {
	char *command;
	char **parameters;
	int status = 1;

	while(status) {
		type_prompt();
		read_command(command, parameters);
		status = execute_command(command, parameters);

	}
}
*/
int main(int argc, char const *argv[])
{
	char *command = malloc(sizeof(char *));
	char **parameters = malloc(BUFFSIZE * sizeof(char *));
	int status;

	while(TRUE){
		type_prompt();
		read_command(command,parameters);
		if(fork()!=0){
			waitpid(-1,&status,0);
		}	
		else{
			execvp(command, parameters);
		}
	}

	free(command);
	for (int i = 0; i<BUFFSIZE; i++) {
		free(parameters[i]);
	}
	free(parameters);
	return 0;
}