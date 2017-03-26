#include "linkedlist.h"

#define MAX_SIZE 128


void push(Element **list, char *line) {
	Element *new = (Element*) malloc(sizeof(Element));
	char *s = malloc(MAX_SIZE * sizeof(char));
	strcpy(s, line);
	new->line = s;
	new->next = *list;
	new->previous = NULL;
	if (!isEmpty(list)) {
		(*list)->previous = new;
	}
	*list = new;
	s = NULL;
}

Element *pop(Element **list) {
	Element *first = (*list);
	(*list) = (*list)->next;
	if (!isEmpty(list)){
		(*list)->previous = NULL;
	}
	return first;
}

void removeElement(Element *e) {
	Element *prev = NULL;
	Element *nex = NULL;
	if (!isEmpty(&(e->previous))) {
		prev = e->previous;
	}
	if (!isEmpty(&(e->previous))) {
		nex = e->next;
	}
	prev->next = nex;
	nex->previous = prev;
	e->next = NULL;
	e->previous = NULL;
}

int isEmpty(Element **list) {
	return (*list)==NULL;
}

void deleteElement(Element *e) {
	free(e->line);
	e->line = NULL;
	free(e);
	e = NULL;
}

void deleteList(Element **list) {
	while ((*list) != NULL) {
		Element *e = pop(list);
		deleteElement(e);
	}
}