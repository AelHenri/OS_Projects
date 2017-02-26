#include "linkedlist.h"

#define MAX_SIZE 50


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
}

Element *pop(Element **list) {
	Element *first = (*list);
	(*list) = (*list)->next;
	if (!isEmpty(list)){
		(*list)->previous = NULL;
	}
	return first;
}

int isEmpty(Element **list) {
	return (*list)==NULL;
}

void delete(Element *e) {
	free(e->line);
	e->line = NULL;
	free(e);
	e = NULL;
}

void deleteList(Element **list) {
	while ((*list) != NULL) {
		Element *e = pop(list);
		printf("%s\n", e->line);
		delete(e);
	}
}