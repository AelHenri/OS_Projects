#ifndef LINKED_LIST
#define LINKED_LIST

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct element {
	char *line;
	struct element *next;
	struct element *previous;
} Element;

void push(Element **list, char *line);
Element *pop(Element **list);
int isEmpty(Element **list);
void delete(Element *e);
void deleteList(Element **list);

#endif