#include "shell.h"


void type_prompt(){

}

void read_command(char *command, char **parameters){

}

int main(int argc, char const *argv[])
{
	char *command;
	char **parameters;

	int status;
	while(TRUE){
		type_prompt();
		read_command(command,parameters);
		
		if(fork()!=0){
			waitpid(-1,&status,0);
		}	
		else{
			execve(command, parameters, 0);
		}
	}
	return 0;
}