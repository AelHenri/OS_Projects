#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

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



void topic_init(){
	topics_list = malloc(sizeof(topic)*MAX_NB_TOPICS);
	nb_topics = 0;
}


int lookup_topics(int topics_id[]){
	int i =0;
	for(i = 0; i < nb_topics ; i++){
		topics_id = topics_list[i].t_id;
	}
	return SUCCESS;
}

int add_topic(int topic_id){
	int i;
	for(i=0; i < nb_topics; i++){
		if (topics_list[i].t_id == topic_id){
			return TOPIC_DUPLICATED;
		}
	}
	if(nb_topics == MAX_NB_TOPICS){
		return TOPIC_MAX_REACHED;
	}
	push_topic(topics_list, topic_id);
	nb_topics++;
	return SUCCESS;
}

int find_topic_index(int topic_id){
	int i;
	for(i = 0; i < nb_topics; i++){
		if(topics_list[i].t_id == topic_id)
			return i;
	}
	return -1;
}

int get_process_index(t_process *process, int p_id){
	int flag = 0;
	int i = 0;
	while(process->next != NULL){
		if(process->pid == p_id){
			flag = 1;
			break;
		}
		i++;
		process = process->next;
	}
	if(!flag)
		return -1;
	return i;
}

int add_publisher_to_topic(int topic_id, int publisher_id){
	int index = find_topic_index(topic_id);
	if(index == -1){
		return TOPIC_NOT_FOUND;
	}
	//check if publisher is duplicated
	int p_id = get_process_index(topics_list[index].publishers, publisher_id);
	if(p_id != -1)
		return PUPLISHER_DUPLICATED;
	push_process(topics_list[index].subscribers, publisher_id);
	return SUCCESS;
}


int add_subscriber_to_topic(int topic_id, int subscriber_id){
	int index = find_topic_index(topic_id);
	if(index == -1){
		return TOPIC_NOT_FOUND;
	}
	//check if subsriber is duplicated
	int p_id = get_process_index(topics_list[index].subscribers, subscriber_id);
	if(p_id != -1)
		return SUBSCRIBER_DUPLICATED;
	push_process(topics_list[index].subscribers, subscriber_id);
	return SUCCESS;
}

int publish_message(int topic_id, char msg[]){
	int index = find_topic_index(topic_id);
	if(index == -1){
		return TOPIC_NOT_FOUND;
	}

	if(strlen(msg) > MAX_CHAR)
		return MSG_LEN_OVERFLOW;

	if(topics_list[index].nb_msg <= 5){
		pop_message(topics_list[index].mlist);
		push_message(topics_list[index].mlist, msg);
	}
	else{
		push_message(topics_list[index].mlist, msg);
		topics_list[index].nb_msg++;
	}
}

//TODO!!!NOT COMPLETE 
int get_next_message(int topic_id, char *msg[], int subscriber_id){
	int index = find_topic_index(topic_id);
	if(index == -1){
		return TOPIC_NOT_FOUND;
	}
	//subscriber is valid ?	
	int p_id = get_process_index(topics_list[index].subscribers, subscriber_id);
	if(p_id != -1)
		return NOT_SUBSRCRIBER_TOPIC;
}

void print_topic(int topic_index){
	printf("The topic number is %d\n", topic_index);
	printf("Message : \n");
	while(topics_list[topic_index].mlist != NULL){
		printf("%s\n", topics_list[topic_index].mlist->data);
		topics_list[topic_index].mlist = topics_list[topic_index].mlist->next;
	}
	printf("Subscribers : \n" );
	while(topics_list[topic_index].subscribers != NULL){
		printf("%d\n", topics_list[topic_index].subscribers->pid);
		topics_list[topic_index].subscribers = topics_list[topic_index].subscribers->next;
	}
	printf("Publishers : \n" );
	while(topics_list[topic_index].publishers != NULL){
		printf("%d\n", topics_list[topic_index].publishers->pid);
		topics_list[topic_index].publishers = topics_list[topic_index].subscribers->next;
	}
}







