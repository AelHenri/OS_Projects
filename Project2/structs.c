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

void remove_process(t_process **list, t_process *proc) {
	t_process *it = *list;
	while ((it->next)->pid != proc->pid && it != NULL) {
		it = it->next;
	}
	if (it!=NULL) {
		it->next = proc->next;
	}
}

t_process *find_process(t_process **list, int pid) {
	t_process* it = *list;
	while (it != NULL) {
		if (it->pid == pid)
			return it;
		it = it->next;
	}
	return it;
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

topic* find_topic(topic **list, int topic_id) {
	topic* it = *list;
	while (it != NULL) {
		if (it->t_id == topic_id)
			return it;
		it = it->next;
	}
	return it;
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

/*
		UTILITY FUNCTIONS
*/

void topic_init(){
	topics_list = NULL;
	nb_topics = 0;
}


int lookup_topics(char *topics_id){
	topic *it = topics_list;
	int i = 0;
	while(it != NULL){
		topics_id[i] = it->t_id;
		it = it->next;
		i++;
	}
	return SUCCESS;
}

int add_topic(int topic_id){
	int i;
	topic *it = topics_list;
	while(it != NULL){
		if (it->t_id == topic_id){
			return TOPIC_DUPLICATED;
		}
		it = it->next;
	}
	if(nb_topics == MAX_NB_TOPICS){
		return TOPIC_MAX_REACHED;
	}
	push_topic(&(topics_list), topic_id);
	nb_topics++;
	return SUCCESS;
}

int is_process_in_list(t_process *process, int p_id){
	int flag = 0;
	t_process *it = process;
	while(it != NULL){
		if(it->pid == p_id){
			return 1;
		}
		it = it->next;
	}
	return 0;
}

int add_publisher_to_topic(int topic_id, int publisher_id){
	topic *top = find_topic(&(topics_list), topic_id);
	if(top == NULL){
		return TOPIC_NOT_FOUND;
	}
	//check if publisher is duplicated
	if(is_process_in_list(top->publishers, publisher_id) == 1)
		return PUPLISHER_DUPLICATED;
	push_process(&(top->publishers), publisher_id);
	return SUCCESS;
}

int add_subscriber_to_topic(int topic_id, int subscriber_id){
	topic *top = find_topic(&(topics_list), topic_id);
	if(top == NULL){
		return TOPIC_NOT_FOUND;
	}
	//check if subscriber is duplicated
	if(is_process_in_list(top->subscribers, subscriber_id) == 1)
		return SUBSCRIBER_DUPLICATED;
	push_process(&(top->subscribers), subscriber_id);
	return SUCCESS;
}

int publish_message(int topic_id, int publisher_id, char msg[]){
	topic *top = find_topic(&(topics_list), topic_id);
	if(top == NULL){
		return TOPIC_NOT_FOUND;
	}
	if(!is_process_in_list(top->publishers, publisher_id)){
		return NOT_PUBLISHER_TOPIC;
	}
	if(strlen(msg) > MAX_CHAR)
		return MSG_LEN_OVERFLOW;

	if(top->nb_msg >= 5){
		return MESSAGE_BUF_FULL;
	}
	else{
		push_message(&(top->mlist), msg);
		top->mlist->subscribers = top->subscribers;
		top->nb_msg++;
	}
	return SUCCESS;
}

//TODO!!!NOT COMPLETE 

int retrieve_message(int topic_id, int subscriber_id, char buffer[]){
	topic *top = find_topic(&(topics_list), topic_id);
	if(top == NULL){
		return TOPIC_NOT_FOUND;
	}
	//subscriber is valid ?	
	if(!is_process_in_list(top->subscribers, subscriber_id))
		return NOT_SUBSCRIBER_TOPIC;

	t_message *msg = top->mlist;
	if (is_messages_empty(&msg))
		return NO_MESSAGE_FOUND;
	if(!is_process_in_list(msg->subscribers, subscriber_id))
		return ALREADY_RETRIEVED;
	if (strlen(buffer) < strlen(msg->data))
		return MSG_LEN_OVERFLOW;
	strcpy(buffer, msg->data);

	remove_process(&(msg->subscribers), find_process(&(msg->subscribers), subscriber_id));

	if (is_processes_empty(&(msg->subscribers))) {
		delete_message(pop_message(&(top->mlist)));
	}

	return 1;
}

void print_topic(topic *t){
	printf("------------------------------------\n");
	printf("The topic number is %d\n", t->t_id);
	printf("Messages : \n");
	while(t->mlist != NULL){
		printf("%s\n", t->mlist->data);
		t->mlist = t->mlist->next;
	}
	printf("Subscribers : \n" );
	while(t->subscribers != NULL){
		printf("%d\n", t->subscribers->pid);
		t->subscribers = t->subscribers->next;
	}
	printf("Publishers : \n" );
	while(t->publishers != NULL){
		printf("%d\n", t->publishers->pid);
		t->publishers = t->publishers->next;
	}
	printf("------------------------------------\n");
}
