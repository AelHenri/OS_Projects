#include "structs.h"

/*
		MESSAGE FUNCTIONS
*/

void push_message(t_message **list, char *data) {
	t_message *new = (t_message*) malloc(sizeof(t_message));
	char *s = malloc(strlen(data)+1 * sizeof(char));
	strcpy(s, data);
	new->data = s;
	new->subscribers = NULL;
	new->next = *list;
	*list = new;
	s = NULL;
}

t_message *pop_message(t_message **list) {
	if (is_messages_empty(list))
		return NULL;
	t_message *first = (*list);
	(*list) = (*list)->next;
	return first;
}

int is_messages_empty(t_message **list) {
	return (*list)==NULL;
}

void delete_message(t_message *m) {
	delete_process_list(&(m->subscribers));
	m->subscribers = NULL;
	free(m->data);
	m->data = NULL;
	free(m);
	m = NULL;
}

void delete_message_list(t_message **list) {
	while ((*list) != NULL) {
		t_message *e = pop_message(list);
		delete_message(e);
	}
}

/*
		PROCESS FUNCTIONS
*/

void push_process(t_process **list, int pid) {
	t_process *new = (t_process*) malloc(sizeof(t_process));
	new->pid = pid;
	new->next = *list;
	*list = new;
}

t_process *pop_process(t_process **list) {
	if (is_processes_empty(list))
		return NULL;
	t_process *first = (*list);
	(*list) = (*list)->next;
	return first;
}

int is_processes_empty(t_process **list) {
	return (*list)==NULL;
}

void delete_process(t_process *p) {
	free(p);
	p = NULL;
}

void delete_process_list(t_process **list) {
	while ((*list) != NULL) {
		t_process *p = pop_process(list);
		delete_process(p);
	}
}

/*
		TOPIC FUNCTIONS
*/

void push_topic(topic **list, int nb) {
	topic *new = (topic*) malloc(sizeof(topic));
	/*if (is_topics_empty(list))
		new->t_id = 0;
	else
		new->t_id = (*list)->t_id + 1;*/
	new->t_id = nb;
	new->nb_msg = 0;
	new->mlist = NULL;
	new->subscribers = NULL;
	new->publishers = NULL;
	new->next = *list;
	*list = new;
}

topic *pop_topic(topic **list) {
	if (is_topics_empty(list))
		return NULL;
	topic *first = (*list);
	(*list) = (*list)->next;
	return first;
}

int is_topics_empty(topic **list) {
	return (*list)==NULL;
}

void delete_topic(topic *t) {
	if (!is_processes_empty(&(t->subscribers)))
		delete_process_list(&(t->subscribers));
	if (!is_processes_empty(&(t->publishers)))
		delete_process_list(&(t->publishers));
	if (!is_messages_empty(&(t->mlist)))
		delete_message_list(&(t->mlist));
	t->subscribers = NULL;
	t->publishers = NULL;
	t->mlist = NULL;
	free(t);
	t = NULL;
}

void delete_topic_list(topic **list) {
	while ((*list) != NULL) {
		topic *e = pop_topic(list);
		delete_topic(e);
	}
}	


void topic_init(){
	topics_list = malloc(sizeof(topic)*MAX_NB_TOPICS);
	nb_topics = 0;
}


int lookup_topics(int topics_id[]){
	int i =0;
	for(i = 0; i < nb_topics ; i++){
		topics_id[i] = topics_list[i].t_id;
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
	push_topic(&(topics_list), topic_id);
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
	push_process(&(topics_list[index].publishers), publisher_id);
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
	push_process(&(topics_list[index].subscribers), subscriber_id);
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
		pop_message(&(topics_list[index].mlist));
		push_message(&(topics_list[index].mlist), msg);
	}
	else{
		push_message(&(topics_list[index].mlist), msg);
		topics_list[index].nb_msg++;
	}
	return SUCCESS;
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
	return 1;
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
	