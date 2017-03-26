#ifndef LINKED_LIST
#define LINKED_LIST

#include <stdio.h>
#include <stdlib.h>

typedef struct element {
	void *data;
	struct element *next;
	struct element *previous;
} Element;

void push(Element **list, void *data);
Element *pop(Element **list);
int isEmpty(Element **list);
void deleteElement(Element *e);
void deleteList(Element **list);
void removeElement(Element *e);

#endif