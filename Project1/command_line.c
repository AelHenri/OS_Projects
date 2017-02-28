#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>

#include "command_utilities.h"
/*
 * Parse a command line containing commands in sequence and/or parralel
 * Store the commands into the structure cmd_line
 */
void parse_command(char *line, struct cmd_line *cmd)
{

    static char array[MAX_LINE]; 
    char *local_line = array;         
    strcpy(local_line, line);
    //free(line);	
	int k, index_semi, index_and, index_par, index_par_last, index_par_depth, index_and_depth, l = 0, q;

	char *ptr_and_position, *ptr_par_position, *ptr_par_close_position, *ptr_par_position_depth, *ptr_and_position_depth, *ptr_semi_position ;

	char **tokens;

	ptr_and_position = strchr(local_line, '&');
	if(ptr_and_position)
	{
		index_and = ptr_and_position - local_line;
	}
	ptr_par_position = strchr(local_line, '(');
	if(ptr_par_position)
	{
		index_par = ptr_par_position - local_line;
	}

	ptr_semi_position = strchr(local_line, ';');
	if(ptr_semi_position)
	{
		index_semi = ptr_semi_position - local_line;
	}

	ptr_par_close_position = strrchr(local_line, ')');
	if(ptr_par_close_position)
	{
		index_par_last = ptr_par_close_position - local_line;
	}

	ptr_par_position_depth = strrchr(local_line, '(');
	if(ptr_par_position_depth)
	{
		index_par_depth = ptr_par_position_depth - local_line;
	}

	ptr_and_position_depth = strrchr(local_line, '&');
	if(ptr_and_position_depth)
	{
		index_and_depth = ptr_and_position_depth - local_line;
	}
	trim_white_space(local_line);
	englobing_paranthesis(local_line);

	int nb_semi = contains_semicolon(local_line);

	if(nb_semi == 0){
		remove_all_chars(local_line, ')');
		remove_all_chars(local_line, '(');		
	}

	int nb_parallel = is_parallel(local_line);
	int nb_par = nb_parenthesis(local_line);

	if(is_well_parenthisized(local_line))
	{	
		if(nb_parallel == 0)
		{	
			remove_all_chars(local_line, '(');
			remove_all_chars(local_line, ')');
			q = cmd->index_array;
			tokens = str_split(local_line, ';');
			if (tokens)
			{
				k=0;
				for (l = 0; *(tokens + l); l++)
				{
					if(q==0 && cmd->cmd_array[cmd->index_array-1].cmd == NULL){
						change_cmd_data_index_queue(&(cmd->cmd_array[cmd->index_array]), q - 1);
					}

					change_cmd_data_index_queue(&(cmd->cmd_array[cmd->index_array]), q);					
					change_cmd_data_char(&(cmd->cmd_array[cmd->index_array]), *(tokens + l));
					change_cmd_data_index_cmd(&(cmd->cmd_array[cmd->index_array]), k);
					increment_cmd_line_index_array(cmd);
					k++;
					free(*(tokens + l));
					}
        		printf("\n");
        		free(tokens);
        	}
		}
		else if(nb_parallel > 0 && nb_par == 0)
		{	
			q = cmd->cmd_array[cmd->index_array].index_queue;
			tokens = str_split(local_line, '&');
			if (tokens)
			{
				for (l = 0; *(tokens + l); l++){
					if(*(tokens + l) != NULL){
						change_cmd_data_char(&(cmd->cmd_array[cmd->index_array]), *(tokens + l));
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
		{	
			if(index_semi < index_par && index_semi < index_and )
			{	
				q = cmd->cmd_array[cmd->index_array].index_queue;
				tokens = str_split_into_two(local_line, ';');
				if (tokens)
				{	
					change_cmd_data_char(&(cmd->cmd_array[cmd->index_array]), *(tokens));
					if(q == 0 || cmd->cmd_array[cmd->index_array].cmd == NULL){
						change_cmd_data_index_queue(&(cmd->cmd_array[cmd->index_array]), 0);
					}else{
						change_cmd_data_index_queue(&(cmd->cmd_array[cmd->index_array]), q+1);
					}
					change_cmd_data_index_cmd(&(cmd->cmd_array[cmd->index_array]), 0);
					increment_cmd_line_index_array(cmd);
					free(*(tokens));
					parse_command((*(tokens + 1)), cmd);	
				}	
        		free(tokens);
			}
			else if(index_and < index_par && index_par < index_par_last)
			{	

				q = cmd->cmd_array[cmd->index_array].index_queue;
				tokens = str_split_into_two(local_line, '&');
				if(tokens)
				{	
					change_cmd_data_char(&(cmd->cmd_array[cmd->index_array]), *(tokens));
					change_cmd_data_index_queue(&(cmd->cmd_array[cmd->index_array]), q);
					change_cmd_data_index_cmd(&(cmd->cmd_array[cmd->index_array]), 0);
					increment_cmd_line_index_array(cmd);
					free(*(tokens));
					parse_command((*(tokens + 1)), cmd);
					free(tokens);
				}							
			}else if (index_and > index_par_last && index_par_last > index_par)
			{
				
				q = cmd->cmd_array[cmd->index_array].index_queue;
				tokens = str_split_into_two_last(local_line, '&');
				if(tokens)
				{
					topntail(*(tokens+1));
					change_cmd_data_char(&(cmd->cmd_array[cmd->index_array]), *(tokens+1));
					change_cmd_data_index_queue(&(cmd->cmd_array[cmd->index_array]), q);
					change_cmd_data_index_cmd(&(cmd->cmd_array[cmd->index_array]), 0);
					increment_cmd_line_index_array(cmd);	
					free(*(tokens))	;		
					parse_command(*(tokens), cmd);
        			free(tokens);				
				}			
										
			}else if (index_par < index_and && index_and < index_par_last)
			{	
				remove_all_chars(local_line, '(');
				remove_all_chars(local_line, ')');
				q = cmd->cmd_array[cmd->index_array].index_queue;
				tokens = str_split(local_line, '&');
				if(tokens)
				{	
					change_cmd_data_char(&(cmd->cmd_array[cmd->index_array]), *(tokens));
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
			if(index_and_depth > index_par_last){
				q = cmd->cmd_array[cmd->index_array].index_queue;
				tokens = str_split_into_two_last(local_line, '&');
				if(tokens)
				{	
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
				q = cmd->cmd_array[cmd->index_array].index_queue;
				tokens = str_split_into_two(local_line, '&');
				if(tokens)
				{	

					parse_command(*(tokens), cmd);
					free(*(tokens));
					parse_command(*(tokens + 1), cmd);
					free(tokens);
				}
			}else if (index_and > index_par_last && index_par_last > index_par)
			{	

				q = cmd->cmd_array[cmd->index_array].index_queue;
				tokens = str_split_into_two_last(local_line, '&');
				if(tokens)
				{	
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
				q = cmd->cmd_array[cmd->index_array].index_queue;
				tokens = str_split_into_two(local_line, '&');
				if(tokens)
				{
					parse_command(*(tokens), cmd);
					free(*(tokens));	
					parse_command(*(tokens + 1), cmd);
					free(*(tokens + 1));
					free(tokens);				
				}									
			}
		}		
		
	}
	else {
		fprintf(stderr, "Syntax error\n");
	} 
}

/*
int main(){
	char *command = "cmd0 & ( cmd1 &( cmd2 ; cmd3)) & cmd4";
	printf("%s\n", command);

	char **	tokens = str_split_into_two_last(command, '&');
	struct cmd_line *c;
	initialize_cmd_line(c);


	parse_command(command, c);
	display_cmd_data(c);
	free_cmd_line(c);
	return 0;
}
*/

/*
Example of supported commands :
	-	"cmd0 & ( cmd1 &( cmd2 ; cmd3)) & cmd4" 
	-	"cmd1 ; (cmd2 & cmd3)"" 
	-	"((tete & tutu) & tata )"
	-	"((tete & tutu) ; tata )"
	-	"( cmd1; cmd2) & cmd3"
	-	"cmd1 ; (cmd2; cmd3)"
	-	"cmd1 & (cmd2 & cmd3)"
	-	"cmd1 ; cmd2 & cmd3"
	-	"cmd1 & cmd2"
	-	"((tete & tutu) & tata )"
*/
