#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"

typedef struct autocomplete{
	Element *head;
	Element *current;
	Element *queue;
	int size;
	int isOn;
} Autocomplete;

void init(Autocomplete **a);
void addLine(Autocomplete **a, char *line);
void delLine(Autocomplete **a);
void next(Autocomplete **a, char *firstchars);
void previous(Autocomplete **a, char *firstchars);
void parseHistory(Autocomplete **a, char *path);
void saveHistory(Autocomplete **a, char *path);
void getCurrent(Autocomplete **a, char **line);
void deleteAll(Autocomplete **a);
void printAutocomplete(int printedString, char *autocompleteString);
void goToStart(Autocomplete **a);
void turnOnOff(Autocomplete **a);
int isOn(Autocomplete **a) ;