#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"

typedef struct autocomplete{
	Element *head;
	Element *current;
} Autocomplete;

void init(Autocomplete **a);
void addLine(Autocomplete **a, char *line);
void delLine(Autocomplete **a);
void next(Autocomplete **a, char *firstchars);
void previous(Autocomplete **a, char *firstchars);