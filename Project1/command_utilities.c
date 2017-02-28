#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>

#include "stack.h"
#include "command_utilities.h"

/*
 * Initialize the structure cmd_line containing an array 
 * of the structure cmd_data that containes the command 
 * string and the order of execution
 */
void initialize_cmd_line(struct cmd_line *c){
	int i;
	c->index_array = 0;
	for(i=0; i < MAX_NB_CMD; i++){
		//c->cmd_array[i].cmd[0] = '\0';
		c->cmd_array[i].index_queue = 0;		
		c->cmd_array[i].index_cmd = 0;
	}
}

/*
 * Free the strings containted in the structure cmd_line
 */
void free_cmd_line(struct cmd_line *c){
	int index = c->index_array;
	int i = 0;
	for(i = 0;i < index; i++){
		free(c->cmd_array[i].cmd);
	}
} 

void change_cmd_data_char(struct cmd_data *c, char *new_cmd){
	c->cmd = strdup(new_cmd);
}

void change_cmd_data_index_queue(struct cmd_data *c, int i){
	c->index_queue = i;
}

void change_cmd_data_index_cmd(struct cmd_data *c, int i){
	c->index_cmd = i;
}

void display_cmd_data(struct cmd_line *c){
	int i;
	int nb = c->index_array;
	for(i=0; i < nb; i++){
		if(c->cmd_array[i].cmd != NULL){
			printf("command char %s\n", c->cmd_array[i].cmd);
			printf("index queue %d\n", c->cmd_array[i].index_queue);
			printf("index cmd %d\n", c->cmd_array[i].index_cmd);
		}
	}
}

void increment_cmd_line_index_array(struct cmd_line *c){
	c->index_array++;
}

int is_well_parenthisized(char exp[]){
   int i = 0;
   struct sNode *stack = NULL;
   while (exp[i]){
      if (exp[i] == '(')
        push_stack(&stack, exp[i]);
      if (exp[i] == ')' ){
         if (stack == NULL)
           return 0; 
         else if (!(pop_stack(&stack) == '(' && exp[i] == ')'))
           return 0;
      }
      i++;
   }
   if (stack == NULL)
     return 1; 
   else
     return 0;  
} 

int is_parallel(char exp[]){
  int i = 0; 
  int j = 0;
  while(exp[i] != '\0'){
    if(exp[i] == '&'){
      j++;
    }
    i++;
  }
  return j;
}

int nb_parenthesis(char *exp){
  int i = 0; 
  int j = 0;
  while(exp[i] != '\0'){
    if(exp[i] == '('){
      j++;
    }
    i++;
  }
  return j;	
}


void topntail(char *str) {
    size_t len = strlen(str);
    assert(len >= 2); 
   	memmove(str, str+1, len-2);
   	str[len-2] = 0;
}

char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }
    count += last_comma < (a_str + strlen(a_str) - 1);
    count++;
    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);
        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }
    //free(tmp);
    return result;
}

void remove_all_chars(char* str, char c) {
    char *pr = str, *pw = str;
    while (*pr) {
        *pw = *pr++;
        pw += (*pw != c);
    }
    *pw = '\0';
}
void double_remove_all_chars(char *str, char c, char cc){
	remove_all_chars(str, c);
	remove_all_chars(str, cc);
}

char *concatenate(size_t size, char *array[size], const char *joint){
    size_t jlen, lens[size];
    size_t i, total_size = (size-1) * (jlen=strlen(joint)) + 1;
    char *result, *p;


    for(i=0;i<size;++i){
        total_size += (lens[i]=strlen(array[i]));
    }
    p = result = malloc(total_size);
    for(i=0;i<size;++i){
        memcpy(p, array[i], lens[i]);
        p += lens[i];
        if(i<size-1){
            memcpy(p, joint, jlen);
            p += jlen;
        }
    }
    *p = '\0';
    return result;
}

char **str_split_into_two(char *a_str, const char a_delim){
	char **result = NULL;
	int index;
	result = malloc(sizeof(char *)*2);
	char *local_str = strdup(a_str);
	int len = strlen(local_str);
	char *ptr_position = strchr(local_str, a_delim);
	if(ptr_position)
	{
		index = ptr_position - local_str;
		*(result) = malloc(sizeof(char)*1024);
		*(result + 1) = malloc(sizeof(char)*1024);
		strncpy(*(result), local_str, index);
		strncpy(*(result + 1), local_str + index + 1, len - index +1);
	}
	free(local_str);
	return result;
}

char **str_split_into_two_last(char *a_str, const char a_delim){
	char **result = NULL;
	int index;
	result = malloc(sizeof(char *)*2);
	char *local_str = strdup(a_str);
	int len = strlen(local_str);
	char *ptr_position = strrchr(local_str, a_delim);
	if(ptr_position)
	{
		index = ptr_position - local_str;
		*(result) = malloc(sizeof(char)*1024);
		*(result + 1) = malloc(sizeof(char)*1024);
		strncpy(*(result), local_str, index);
		strncpy(*(result + 1), local_str + index + 1, len - index+1);
	}
	free(local_str);
	return result;
}

void trim_white_space(char * s) {
    char * p = s;
    int l = strlen(p);

    while(isspace(p[l - 1])) p[--l] = 0;
    while(* p && isspace(* p)) ++p, --l;

    memmove(s, p, l + 1);
}   

int contains_semicolon(char *str){
	char c = str[0];
	int i = 0;
	int nb = 0;
	while(c != '\0'){
		if(c == ';')
			nb++;
		i++;
		c = str[i];
	}
	return nb;
}
int last_element_is_paren(char *str){
	int len = strlen(str);
	if(str[len-1]==')'){
		return 1;
	}
	return 0;
}

int first_element_is_paren(char *str){
	if(str[1]==')'){
		return 1;
	}
	return 0;
}
void englobing_paranthesis(char *str){
	char *l_str = strdup(str);
	trim_white_space(l_str);
	int elem = last_element_is_paren(l_str);
	int elem2 = first_element_is_paren(l_str);	
	topntail(l_str);
	if(is_well_parenthisized(l_str)){

		if (elem == 1 && elem2 == 2)
		{	
			topntail(str);			
		}
	}
	free(l_str);
}