#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>

#include "command_utilities.h"

void parse_command(char *line, struct cmd_line *cmd)
{

    static char array[MAX_LINE]; 
    char *local_line = array;         
    strcpy(local_line, line);	
	int index_semi, index_and, index_par, index_par_last, index_par_depth, index_and_depth, index_sem, i = 0, l = 0, k, q;

	char c = local_line[i];
	char *ptr_and_position, *ptr_par_position, *ptr_par_close_position, *ptr_par_position_depth, *ptr_semicolon_position, *ptr_and_position_depth, *ptr_semi_position ;
	char *cmd_data = NULL;

	char **tokens;

	ptr_and_position = strchr(local_line, '&');
	if(ptr_and_position)
	{
		index_and = ptr_and_position - local_line;
		printf("index_and %d\n", index_and);
	}
	ptr_par_position = strchr(local_line, '(');
	if(ptr_par_position)
	{
		index_par = ptr_par_position - local_line;
		printf("index_par %d\n", index_par);
	}

	ptr_semi_position = strchr(local_line, ';');
	if(ptr_semi_position)
	{
		index_semi = ptr_semi_position - local_line;
		printf("index_semi %d\n", index_semi);
	}

	ptr_par_close_position = strrchr(local_line, ')');
	if(ptr_par_close_position)
	{
		index_par_last = ptr_par_close_position - local_line;
		printf("index_par_last %d\n", index_par_last);
	}

	ptr_par_position_depth = strrchr(local_line, '(');
	if(ptr_par_position_depth)
	{
		index_par_depth = ptr_par_position_depth - local_line;
		printf("index_par_depth %d\n", index_par_depth);
	}

	ptr_and_position_depth = strrchr(local_line, '&');
	if(ptr_and_position_depth)
	{
		index_and_depth = ptr_and_position_depth - local_line;
		printf("index_and_depth %d\n", index_and_depth);
	}
	trim_white_space(local_line);
	printf("local line before englobing_paranthesis %s\n", local_line);
	englobing_paranthesis(local_line);
	printf("local line after englobing_paranthesis %s\n", local_line);
	int nb_semi = contains_semicolon(local_line);
	printf("im here nb nb_semi %d\n", nb_semi);
	printf("local_line %s\n", local_line);
	if(nb_semi == 0){
		printf("im here\n");
		printf("%d\n", nb_semi);
		remove_all_chars(local_line, ')');
		remove_all_chars(local_line, '(');		
	}

	int nb_parallel = is_parallel(local_line);
	int nb_par = nb_parenthesis(local_line);

	printf("nb_parallel %d\n", nb_parallel);
	printf("nb_parenthesis %d\n", nb_par);
	printf("%s\n", local_line);
	printf("LOCAL LINE %s\n\n", local_line);
	printf("LINE %s\n\n", line );
	if(is_well_parenthisized(local_line))
	{	printf("is_well_parenthisized\n");
		if(nb_parallel == 0)
		{	printf("nb_parallel\n");
			remove_all_chars(local_line, '(');
			remove_all_chars(local_line, ')');
			q = cmd->index_array;
			printf("nb_parallel queue %d\n", q);
			tokens = str_split(local_line, ';');
			if (tokens)
			{
				k=0;
				for (l = 0; *(tokens + l); l++)
				{
					if(q==0 && cmd->cmd_array[cmd->index_array-1].cmd == NULL){
						printf("je suis la\n");
						change_cmd_data_index_queue(&(cmd->cmd_array[cmd->index_array]), q - 1);
					}

					printf("je suis lala\n");
					change_cmd_data_index_queue(&(cmd->cmd_array[cmd->index_array]), q);					
					change_cmd_data_char(&(cmd->cmd_array[cmd->index_array]), *(tokens + l));
					change_cmd_data_index_cmd(&(cmd->cmd_array[cmd->index_array]), k);
					increment_cmd_line_index_array(cmd);
					k++;
					printf("1-token=[%s]\n", *(tokens + l));
					free(*(tokens + l));
					}
        		printf("\n");
        		free(tokens);
        	}
		}
		else if(nb_parallel > 0 && nb_par == 0)
		{	printf("(nb_parallel > 0 && nb_par == 0)\n");
			q = cmd->cmd_array[cmd->index_array].index_queue;
			tokens = str_split(local_line, '&');
			if (tokens)
			{
				for (l = 0; *(tokens + l); l++){
					if(*(tokens + l) != NULL){
						change_cmd_data_char(&(cmd->cmd_array[cmd->index_array]), *(tokens + l));
						printf("2-token=[%s]\n", *(tokens + l));
						if(contains_semicolon(*tokens + l) != 0){
							parse_command(*(tokens +l), cmd);
						}
						if(q == 0 || cmd->cmd_array[cmd->index_array].cmd == NULL){
	
							change_cmd_data_index_queue(&(cmd->cmd_array[cmd->index_array]), q);
							q++;
						}
						else{
							//q++;
							change_cmd_data_index_queue(&(cmd->cmd_array[cmd->index_array]), q);
							q++;							
						}
						change_cmd_data_index_cmd(&(cmd->cmd_array[cmd->index_array]), 0);
						increment_cmd_line_index_array(cmd);
						free(*(tokens + l));
					}
				}
        		printf("\n");
        		free(tokens);
			}			
		}
		else if (nb_parallel == 1 && nb_par == 1)
		{	printf("(nb_parallel == 1 && nb_par == 1)\n");
			if(index_semi < index_par && index_semi < index_and )
			{	printf("index_semi < index_par && index_semi < index_and\n");
				q = cmd->index_array;
				printf("THE QUEUE%d\n", q);
				tokens = str_split_into_two(local_line, ';');
				if (tokens)
				{	printf("token 2 =[%s]\n", *(tokens));
					printf("token 1 = [%s]\n", *(tokens + 1));
					change_cmd_data_char(&(cmd->cmd_array[cmd->index_array]), *(tokens));
					if(q == 0 || cmd->cmd_array[cmd->index_array].cmd == NULL){
						printf("la\n");
						change_cmd_data_index_queue(&(cmd->cmd_array[cmd->index_array]), 0);
					}else{
						change_cmd_data_index_queue(&(cmd->cmd_array[cmd->index_array]), q+1);
					}
					change_cmd_data_index_cmd(&(cmd->cmd_array[cmd->index_array]), 0);
					increment_cmd_line_index_array(cmd);
					free(*(tokens));
					//topntail(*(tokens+1));
					parse_command((*(tokens + 1)), cmd);	
				}	
        		free(tokens);
			}
			else if(index_and < index_par && index_par < index_par_last)
			{	
				printf("index_and < index_par && index_par < index_par_last\n");
				q = cmd->cmd_array[cmd->index_array].index_queue;
				tokens = str_split_into_two(local_line, '&');
				if(tokens)
				{	
					change_cmd_data_char(&(cmd->cmd_array[cmd->index_array]), *(tokens));
					printf("--token=[%s]\n", *(tokens));
					printf("*-token=[%s]\n", *(tokens + 1));
					change_cmd_data_index_queue(&(cmd->cmd_array[cmd->index_array]), q);
					change_cmd_data_index_cmd(&(cmd->cmd_array[cmd->index_array]), 0);
					increment_cmd_line_index_array(cmd);
					free(*(tokens));
					//topntail(*(tokens+1));
					parse_command((*(tokens + 1)), cmd);
					free(tokens);
				}							
			}else if (index_and > index_par_last && index_par_last > index_par)
			{
				printf("index_and > index_par_last && index_par_last > index_par)\n");
				q = cmd->cmd_array[cmd->index_array].index_queue;
				tokens = str_split_into_two_last(local_line, '&');
				if(tokens)
				{
					topntail(*(tokens+1));
					printf("-2-token=[%s]\n", *(tokens));
					printf("*2-token=[%s]\n", *(tokens + 1));					
					change_cmd_data_char(&(cmd->cmd_array[cmd->index_array]), *(tokens+1));
					change_cmd_data_index_queue(&(cmd->cmd_array[cmd->index_array]), q);
					change_cmd_data_index_cmd(&(cmd->cmd_array[cmd->index_array]), 0);
					increment_cmd_line_index_array(cmd);	
					free(*(tokens))	;
					//topntail(*(tokens));			
					parse_command(*(tokens), cmd);
        			free(tokens);				
				}			
										
			}else if (index_par < index_and && index_and < index_par_last)
			{	
				printf("(index_par < index_and && index_and < index_par_last)\n");
				remove_all_chars(local_line, '(');
				remove_all_chars(local_line, ')');
				///topntail(local_line);
				printf("topntail %s\n", local_line);
				q = cmd->cmd_array[cmd->index_array].index_queue;
				tokens = str_split(local_line, '&');
				if(tokens)
				{	
					change_cmd_data_char(&(cmd->cmd_array[cmd->index_array]), *(tokens));
					printf("3-token %d =[%s]\n", l, *(tokens));
					change_cmd_data_index_queue(&(cmd->cmd_array[cmd->index_array]), q);
					change_cmd_data_index_cmd(&(cmd->cmd_array[cmd->index_array]), 0);
					increment_cmd_line_index_array(cmd);
					q++;
					free(*(tokens + l));	
					for (l = 1; *(tokens + l); l++){
						parse_command(*(tokens+l), cmd);
					}
        		printf("\n");
        		free(tokens);				
				}	
			}		

		}
		else if(nb_parallel > 0 && nb_par > 1){
			printf("(nb_parallel > 0 && nb_par > 1)\n");
			if(index_and_depth > index_par_last){
				printf("(index_and > index_par_last && index_par_last > index_par)\n");
				q = cmd->cmd_array[cmd->index_array].index_queue;
				tokens = str_split_into_two_last(local_line, '&');
				if(tokens)
				{	
					printf("= *-2-token=[%s]\n", *(tokens));
					printf("= **2-token=[%s]\n", *(tokens + 1));						
					parse_command(*(tokens), cmd);
					change_cmd_data_char(&(cmd->cmd_array[cmd->index_array]), *(tokens + 1));
					change_cmd_data_index_queue(&(cmd->cmd_array[cmd->index_array]), q);
					change_cmd_data_index_cmd(&(cmd->cmd_array[cmd->index_array]), 0);
					increment_cmd_line_index_array(cmd);
					free(*(tokens + 1));
					free(tokens);
				}
			}
			else if(index_and < index_par && index_par < index_par_last)
			{
				printf("(index_and < index_par && index_par < index_par_last)\n");
				q = cmd->cmd_array[cmd->index_array].index_queue;
				tokens = str_split_into_two(local_line, '&');
				if(tokens)
				{	
					printf("*-2-token=[%s]\n", *(tokens));
					printf("**2-token=[%s]\n", *(tokens + 1));					
					/*change_cmd_data_char(&(cmd->cmd_array[cmd->index_array]), *(tokens));
					change_cmd_data_index_queue(&(cmd->cmd_array[cmd->index_array]), q);
					change_cmd_data_index_cmd(&(cmd->cmd_array[cmd->index_array]), 0);
					increment_cmd_line_index_array(cmd);*/
					parse_command(*(tokens), cmd);
					free(*(tokens));
					parse_command(*(tokens + 1), cmd);
					free(tokens);
				}
			}else if (index_and > index_par_last && index_par_last > index_par)
			{	
				printf("(index_and > index_par_last && index_par_last > index_par)\n");
				q = cmd->cmd_array[cmd->index_array].index_queue;
				tokens = str_split_into_two_last(local_line, '&');
				if(tokens)
				{	
					printf("= *-2-token=[%s]\n", *(tokens));
					printf("= **2-token=[%s]\n", *(tokens + 1));						
					parse_command(*(tokens), cmd);
					change_cmd_data_char(&(cmd->cmd_array[cmd->index_array]), *(tokens + 1));
					change_cmd_data_index_queue(&(cmd->cmd_array[cmd->index_array]), q);
					change_cmd_data_index_cmd(&(cmd->cmd_array[cmd->index_array]), 0);
					increment_cmd_line_index_array(cmd);
					free(*(tokens + 1));
					free(tokens);
				}
			}
			else if (index_par < index_and && index_and < index_par_last)
			{	
				trim_white_space(local_line);
				topntail(local_line);
				//printf("topntail %s\n", local_line);
				printf("index_par < index_and && index_and < index_par_last\n");
				q = cmd->cmd_array[cmd->index_array].index_queue;
				tokens = str_split_into_two(local_line, '&');
				if(tokens)
				{
					printf("token & =[%s]\n", *(tokens));
					printf("token & 2=[%s]\n", *(tokens + 1));
					parse_command(*(tokens), cmd);
					free(*(tokens));	
					parse_command(*(tokens + 1), cmd);
					free(*(tokens + 1));
					free(tokens);				
				}									
			}
		}		
		
	} 
}


int main(){
	char *command = "cmd0 & ( cmd1 &( cmd2 ; cmd3)) & cmd4";
	printf("%s\n", command);

	char **	tokens = str_split_into_two_last(command, '&');
/*
	if(tokens)
	{
		printf("token=[%s]\n", *(tokens));
		printf("token=[%s]\n", *(tokens + 1));
	}
	free(*(tokens));
	free(*(tokens + 1));
	free(tokens);
*/	
	struct cmd_line *c;
	initialize_cmd_line(c);


	parse_command(command, c);
	display_cmd_data(c);
	free_cmd_line(c);
	return 0;
}



/*
" 
cmd0 & ( cmd1 &( cmd2 ; cmd3)) & cmd4" 
cmd1 ; (cmd2 & cmd3) // a revoir 
"((tete & tutu) & tata )"
"((tete & tutu) ; tata )"
"( cmd1; cmd2) & cmd3"
"cmd1 ; (cmd2; cmd3)"
"cmd1 & (cmd2 & cmd3)"
"cmd1 ; cmd2 & cmd3"
"cmd1 & cmd2"
"((tete & tutu) & tata )"

void parse_command(char *line, struct cmd_line *cmd)
{

    static char array[MAX_LINE]; 
    char *local_line = array;         
    strcpy(local_line, line);	
	int index_and, index_par, i = 0, l = 0, k, q;

	char c = local_line[i];
	char *ptr_and_position, *ptr_par_position;
	char *cmd_data = NULL;
	int nb_parallel = is_parallel(line);
	char **tokens;

	if(is_well_parenthisized(line))
	{
		printf("is is_well_parenthisized\n");
		// parallel commands
		if(nb_parallel != 0)
		{
			printf("number of & %d\n", nb_parallel);
			//parallel & sequence
			if(strchr(local_line, '('))
			{
				printf("local line %s\n", local_line);
				while(c != '\0')
				{
					ptr_and_position = strchr(local_line, '&');
					if(ptr_and_position)
					{
						index_and = ptr_and_position - local_line;
						printf("index and %d\n", index_and);
					}
					ptr_par_position = strchr(local_line, '(');
					if(ptr_par_position)
					{
						index_par = ptr_par_position - local_line;
						printf("index par %d\n", index_par);
					}
					// cmd & ( )
					if(index_par > index_and)
					{
						tokens = str_split(local_line, '&');
						if(tokens)
						{
							for (l = 0; *(tokens + l); l++){
								printf("token=[%s]\n", *(tokens + l));
								parse_command(*(tokens + l), cmd);
								free(*(tokens + l));
							}	
						}
						printf("\n");
						free(tokens);
					}
								
					i++;
					c = local_line[i];
				}

			}
			//parrallel only 
			else
			{
				q = cmd->cmd_array[cmd->index_array].index_queue;
				tokens = str_split(local_line, '&');
				if (tokens)
				{

					for (l = 0; *(tokens + l); l++){
						change_cmd_data_char(&(cmd->cmd_array[cmd->index_array]), *(tokens + l));
						printf("token=[%s]\n", *(tokens + l));
						change_cmd_data_index_queue(&(cmd->cmd_array[cmd->index_array]), q);
						change_cmd_data_index_cmd(&(cmd->cmd_array[cmd->index_array]), 0);
						increment_cmd_line_index_array(cmd);
						q++;
						free(*(tokens + l));
					}
        		printf("\n");
        		free(tokens);
				}
    		}
		// sequence only 
		}else
		{	q = cmd->cmd_array[cmd->index_array].index_queue;
			printf("%d\n", q);
			remove_all_chars(local_line, '(');
			remove_all_chars(local_line, ')');	
			tokens = str_split(local_line, ';');
			if (tokens)
			{
				k=0;
				for (l = 0; *(tokens + l); l++){
					change_cmd_data_char(&(cmd->cmd_array[cmd->index_array]), *(tokens + l));
					if(q==0)
						change_cmd_data_index_queue(&(cmd->cmd_array[cmd->index_array]), q);
					else
						change_cmd_data_index_queue(&(cmd->cmd_array[cmd->index_array]), q+1);
					change_cmd_data_index_cmd(&(cmd->cmd_array[cmd->index_array]), k);
					increment_cmd_line_index_array(cmd);
					k++;

					printf("token=[%s]\n", *(tokens + l));
					free(*(tokens + l));

					}
        		printf("\n");
        		free(tokens);
				}
		
		}
	} 
}

{

    static char array[MAX_LINE]; 
    char *local_line = array;         
    strcpy(local_line, line);	
	int index_and, index_par, i = 0, l = 0, k, q;

	char c = local_line[i];
	char *ptr_and_position, *ptr_par_position;
	char *cmd_data = NULL;
	int nb_parallel = is_parallel(line);
	char **tokens;

	if(is_well_parenthisized(line))
	{
		printf("is is_well_parenthisized\n");
		// parallel commands
		if(nb_parallel != 0)
		{
			printf("number of & %d\n", nb_parallel);
			//parallel & sequence
			if(strchr(local_line, '('))
			{
				printf("local line %s\n", local_line);

				ptr_and_position = strchr(local_line, '&');
				if(ptr_and_position)
				{
					index_and = ptr_and_position - local_line;
					printf("index and %d\n", index_and);
				}
				ptr_par_position = strchr(local_line, '(');
				if(ptr_par_position)
				{
					index_par = ptr_par_position - local_line;
					printf("index par %d\n", index_par);
				}
				tokens = str_split(local_line, '&');
				if(tokens)
				{
					for (l = 0; *(tokens + l); l++){
						printf("token=[%s]\n", *(tokens + l));
						parse_command(*(tokens + l), cmd);
						free(*(tokens + l));
					}	
				}
				printf("\n");
				free(tokens);

			}
			//parrallel only 
			else
			{
				remove_all_chars(local_line, ')');	
				remove_all_chars(local_line, ')');
				q = cmd->cmd_array[cmd->index_array].index_queue;
				tokens = str_split(local_line, '&');
				if (tokens)
				{

					for (l = 0; *(tokens + l); l++){
						change_cmd_data_char(&(cmd->cmd_array[cmd->index_array]), *(tokens + l));
						printf("token=[%s]\n", *(tokens + l));
						if(q == 0){
							printf("queue est nuuulle %d\n", q);
							change_cmd_data_index_queue(&(cmd->cmd_array[cmd->index_array]), q);
							q++;
						}
						else{
							q++;
							change_cmd_data_index_queue(&(cmd->cmd_array[cmd->index_array]), q);							
						}
						change_cmd_data_index_cmd(&(cmd->cmd_array[cmd->index_array]), 0);
						increment_cmd_line_index_array(cmd);
						free(*(tokens + l));
					}
        		printf("\n");
        		free(tokens);
				}
    		}
		// sequence only 
		}else
		{	q = cmd->cmd_array[cmd->index_array].index_queue;
			printf("queue seq est %d\n", q);
			remove_all_chars(local_line, '(');
			remove_all_chars(local_line, ')');	
			tokens = str_split(local_line, ';');
			if (tokens){
				k=0;
				for (l = 0; *(tokens + l); l++){
					change_cmd_data_char(&(cmd->cmd_array[cmd->index_array]), *(tokens + l));
					if(q==0 && cmd->cmd_array[cmd->index_array].cmd == NULL)
						change_cmd_data_index_queue(&(cmd->cmd_array[cmd->index_array]), q);
					else
						change_cmd_data_index_queue(&(cmd->cmd_array[cmd->index_array]), q+1);
					change_cmd_data_index_cmd(&(cmd->cmd_array[cmd->index_array]), k);
					increment_cmd_line_index_array(cmd);
					k++;

					printf("token=[%s]\n", *(tokens + l));
					free(*(tokens + l));

					}
        		printf("\n");
        		free(tokens);
				}
		
		}
	} 
}
*/