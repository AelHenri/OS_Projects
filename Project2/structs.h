#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

/*
		STRUCTURES
*/


typedef struct t_message t_message;
typedef struct t_process t_process;
typedef struct topic topic;

struct t_message {
	char *data;
	t_process *subscribers;
	t_message *next;
};

struct t_process {
	int pid;
	t_process *next;
};

struct topic {
	int t_id;
	int nb_msg;
	t_message *mlist;
	t_process *subscribers;
	t_process *publishers;
	topic *next;
};

void push_message(t_message **list, char *data);
t_message *pop_message(t_message **list);
int is_messages_empty(t_message **list);
void delete_message(t_message *m);
void delete_message_list(t_message **list);

void push_process(t_process **list, int pid);
t_process *pop_process(t_process **list);
int is_processes_empty(t_process **list);
void delete_process_list(t_process **list);

void push_topic(topic **list);
topic *pop_topic(topic **list);
int is_topics_empty(topic **list);
void delete_topic(topic *m);
void delete_topic_list(topic **list);