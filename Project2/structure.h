#ifndef STRUCTURE_H
#define STRUCTURE_H

#define MAX_NB_PUBLISHER 10
#define MAX_NB_SUBSCRIBER 10 
#define MAX_NB_MESSAGES 5 
#define MAX_CHAR 1024
#define MAX_NB_TOPICS 10

struct publisher{
	int nb_publisher;
	int publisher_list[MAX_NB_PUBLISHER];
};

struct subscriber{
	int nb_subscribers;
	int subscriber_list[MAX_NB_SUBSCRIBER];
};

//a modifier potentiellement 
struct message{
	char message[MAX_CHAR];
	int subscribers[MAX_NB_SUBSCRIBER];
};

struct message_list{
	int nb_msg;
	struct message msg[MAX_NB_MESSAGES];
};

struct msg_topic{
	char topic[MAX_CHAR];
	struct publisher publishers;
	struct subscriber subscribers;
	struct message_list msg_lst;
};

struct msg_topic msg_topic_array[MAX_NB_TOPICS];
int nb_topics;


int topic_init();
int get_publisher_index(int topic, int publisher);
int get_subscriber_index(int topic, int subscriber);
int next_message(int topic);
int add_topic(char *topic);
int add_publisher_topic(char *topic, int publisher);
int add_subscriber_topic(char *topic, int subscriber);
int publish_msg(char *topic, char *message);
int lookup_topic(char *topic);

#endif


