#include "shell.h"
#define space" \t\r\n\a"

void type_prompt(){
	printf("> ");
}

void read_command(char **command, char **parameters){
	char* input
	ssize_t bufsize=0;
	getline(command, &bufsize, stdin);
	input = strtok(command, space);
	
	while( input != NULL){
		printf(" %s\n", input);
		
		input = strtok(NULL, space);
	}
		
	
	//command = cmd;
}

int main(int argc, char const *argv[])
{
	char **command = malloc(sizeof(command));
	char **parameters;

	int status;
	while(TRUE){
		type_prompt();
		read_command(command,parameters);
		printf("%s\n", *command);
		/*if(fork()!=0){
			waitpid(-1,&status,0);
		}	
		else{
			execve(*command, parameters, 0);
		}*/
	}

	free(command);
	return 0;
}