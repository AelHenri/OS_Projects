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

void push_topic(topic **list, int nb);
topic *pop_topic(topic **list);
int is_topics_empty(topic **list);
void delete_topic(topic *m);
void delete_topic_list(topic **list);



#define MAX_NB_PUBLISHER 10
#define MAX_NB_SUBSCRIBER 10 
#define MAX_NB_MESSAGES 5 
#define MAX_CHAR 1024
#define MAX_NB_TOPICS 10

#define SUCCESS 1
#define TOPIC_DUPLICATED 2
#define TOPIC_MAX_REACHED 3
#define TOPIC_NOT_FOUND 4
#define PUPLISHER_DUPLICATED 5
#define SUBSCRIBER_DUPLICATED 6
#define MSG_LEN_OVERFLOW 7
#define NOT_SUBSRCRIBER_TOPIC 8


topic  *topics_list; //max size is MAX_NB_TOPICS
int nb_topics;

int find_topic_index(int topic_id);
int get_process_index(t_process *process, int p_id);;;
void print_topic(int topic_index);

void topic_init();
int lookup_topics(int topics_id[]);
int add_topic(int topic_id);
int add_publisher_to_topic(int topic_id, int publisher_id);
int add_subscriber_to_topic(int topic_id, int subscriber_id);
int publish_message(int topic_id, char msg[]);
int get_next_message(int topic_id, char *msg[], int subscriber_id);


