#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <pthread.h>

#include "command_utilities.h"
#include "command_line.h"
#include "queue.h"

#define MAX_NB_THREADS 10;

pthread_t tid[MAX_NB_THREADS];

int get_max_queue(struct cmd_line *cmd){
	int nb_array = cmd->index_array;
	int i, max = 0;
	for(i = 0; i < nb_array; i++){
		if(cmd->cmd_array[i].index_queue > max){
			max = cmd->cmd_array[i].index_queue;
		}
	}
	return max;
}

void execute_all(struct Queue *queue){
	pthread_t tid;
	pthread_create(&tid, NULL, execute_queue, NULL);
}

void execute_queue(){

}

void execute_sequence_command(struct Queue *queue){

}

void execute_and_command(struct Queue *queue){

}

void fill_queue(struct cmd_line *cmd_d, Queue *queues){
	int nb_array = cmd_d->index_array;
	int nb_queue = get_max_queue(cmd_d);
	char commands[nb_queue+1][100];
	int i, j;
	char *tmp;
	for(i = 0; i <= nb_queue; i++){
		memset(commands[i], 0, sizeof(char)*100);
	}

	for(i = 0; i < nb_array; i++)
	{
		for(j = 0; j<= nb_queue; j++)
		{
			if(cmd_d->cmd_array[i].index_queue == j)
			{	
				printf("int i %d int j %d \n", i, j);
				tmp = cmd_d->cmd_array[i].cmd;
				strcat(commands[j], tmp);
				printf("command %s\n", commands[j]);
			}
		}
	}

	for(i = 0; i <= nb_queue; i++){
		printf("Inserting '%s' \n", commands[i]);
		queues[i].push(&queues[i], commands[i]);
		printf("Pushed a new item %s \n",commands[i]);
       	printf("Printing level %d \n", i);
        queues[i].display(&queues[i]);
	}
}



int main(){
	char *command = "cmd0 & (cmd1; cmd2)";
	printf("%s\n", command);

	char **	tokens = str_split_into_two_last(command, '&');
	struct cmd_line *c;
	initialize_cmd_line(c);
	parse_command(command, c);
	display_cmd_data(c);
    struct Queue queues[10]; 
    int nb = c->index_array;
    int j;
    for(j=0; j<10; j++)
    {
   	    Queue queue = createQueue();
        queues[j] = queue;
    }
    fill_queue(c, queues);
	free_cmd_line(c);
	return 0;
}


