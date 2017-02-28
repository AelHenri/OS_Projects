#include "command_queue.h"

#define MAX_NB_THREADS 10
#define MAX_SIZE_QUEUE 10

//pthread_t tid[MAX_NB_THREADS];

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
	pthread_t tid[MAX_NB_THREADS];
	int i = 0;
	while (queue->size > 0 && i<MAX_NB_THREADS) {
		int *commandPointer = (int *)queue->popQueue(queue);
		pthread_create(&tid[i], NULL, (void *) execute_sequence_command, (void *)commandPointer);
		i++;
	}
	if (i==MAX_NB_THREADS) {
		fprintf(stderr, "Max thread number reached.\n");
	}
	for (int j = 0; j<i; j++) {
		pthread_join(tid[j], NULL);
	}
}

void execute_sequence_command(void *cmd_seq){
	char *seqString = (char *) cmd_seq;
	char **tokens = str_split(seqString, ';');
	char *command = NULL;
	char **parameters = NULL;
	int param_size = 0;

	if(tokens){
		for(int i = 0; *(tokens + i); i++){
			printf("token[%d] : %s\n", i, *(tokens + i) );
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

			param_size = parse_command_line(tokens[i], command, parameters);
			if (param_size > 0) {
				execute_command(command, parameters, param_size);
			}

			free(*(tokens+i));
			free(command);
			command = NULL;
			for (int i = 0; i < param_size; i++) {
				free(parameters[i]);
				parameters[i] = NULL;
			}
			free(parameters);
			parameters = NULL;
		}
		free(tokens);
	}

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
				if (j <= nb_queue)
					strcat(commands[j], ";");
				printf("command %s\n", commands[j]);
			}
		}
	}

	for(i = 0; i <= nb_queue; i++){
		trim_white_space(commands[i]);
		int len = strlen(commands[i]);
		commands[i][len-1] = '\0';
		printf("command %s\n", commands[i]);
		queues[i].pushQueue(&queues[i], commands[i]);
	}
    execute_all(queues);
}

void main_execute(char *line) {
	struct cmd_line *c = (struct cmd_line*) malloc(sizeof(struct cmd_line));	
	initialize_cmd_line(c);
	parse_command(line, c);	
	display_cmd_data(c);
    struct Queue queues[MAX_SIZE_QUEUE]; 
    int nb = c->index_array;
    int j;
    for(j=0; j<10; j++)
    {
   	    Queue queue = createQueue();
        queues[j] = queue;
    }
    fill_queue(c, queues);

	free_cmd_line(c);
}

/*
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


*/