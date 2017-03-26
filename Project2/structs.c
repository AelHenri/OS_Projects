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

void push_topic(topic **list) {
	topic *new = (topic*) malloc(sizeof(topic));
	if (is_topics_empty(list))
		new->t_id = 0;
	else
		new->t_id = (*list)->t_id + 1;
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