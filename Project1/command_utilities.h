#ifndef COMMAND_UTILITIES
#define COMMAND_UTILITIES

#include "stack.h"

//max max size command in a command line
#define MAX_NB_CMD 10
#define MAX_LINE 1024

struct cmd_data
{
    char *cmd;
    int index_queue;
    int index_cmd;
};

struct cmd_line{
    struct cmd_data cmd_array[MAX_NB_CMD];
    int index_array;
};

void initialize_cmd_line(struct cmd_line *c);

void free_cmd_line(struct cmd_line *c);

void change_cmd_data_char(struct cmd_data *c, char *new_cmd);

void change_cmd_data_index_queue(struct cmd_data *c, int i);

void change_cmd_data_index_cmd(struct cmd_data *c, int i);

void display_cmd_data(struct cmd_line *c);

void increment_cmd_line_index_array(struct cmd_line *c);

int is_well_parenthisized(char exp[]);

int is_parallel(char exp[]);

int nb_parenthesis(char *exp);

void trim_white_space(char * s) ;

int contains_semicolon(char *str);

void topntail(char *str);

char** str_split(char* a_str, const char a_delim);

void remove_all_chars(char* str, char c);

void double_remove_all_chars(char *str, char c, char cc);

char *concatenate(size_t size, char *array[size], const char *joint);

char **str_split_into_two(char *a_str, const char a_delim);

char **str_split_into_two_last(char *a_str, const char a_delim);

int last_element_is_paren(char *str);

int first_element_is_paren(char *str);

void englobing_paranthesis(char *str);

#endif
