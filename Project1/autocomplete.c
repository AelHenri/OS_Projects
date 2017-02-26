#include "autocomplete.h"

#define MAX_SIZE 50
#define MAX_HISTORY_SIZE 200

void init(Autocomplete **a) {
	(*a)->head = NULL;
	(*a)->current = NULL;
	(*a)->queue = NULL;
	(*a)->size = 0;
	(*a)->isOn = 0;
}

void parseHistory(Autocomplete **a, char *path) {
	FILE *file = fopen(path, "r");
	if (!file) file = fopen(path, "wr");
	if (!file) {
		printf("Cannot open or create .history file.\n");
		exit(EXIT_FAILURE);
	}
	char *line = NULL;
	size_t size = 0;
	fseek(file, 0, SEEK_END); // goto end of file
	if (ftell(file) == 0){
	      return;
	}
	fseek(file, 0, SEEK_SET); // goto begin of file
	// etc;

	while(getline(&line, &size, file) != -1) {
		int len = strlen(line);
		if (line[len-1] == '\n')
			line[len-1] = '\0';
		addLine(a, line);
	}
	//printf("hello\n");

	fclose(file);
	free(line);
}

void saveHistory(Autocomplete **a, char *path) {
	FILE *file = fopen(path, "w");

	(*a)->current = (*a)->head;

	while (!isEmpty(&((*a)->current->next))) {
		(*a)->current = (*a)->current->next;
	}
	while ((*a)->current != (*a)->head) {
		fprintf(file, "%s\n", (*a)->current->line);
		(*a)->current = (*a)->current->previous;
	}
	fprintf(file, "%s", (*a)->current->line);
	fclose(file);
}

void addLine(Autocomplete **a, char* line) {
	push(&((*a)->head), line);
	(*a)->current = (*a)->head;
	if (isEmpty(&(*a)->head->next)) (*a)->queue = (*a)->head;
	if ((*a)->size >= MAX_HISTORY_SIZE) {
		Element *last = (*a)->queue;
		(*a)->queue = last->previous;
		removeElement(last);
		deleteElement(last);
	}
	else {
		(*a)->size++;
	}
}

void next(Autocomplete **a, char *firstchars) {
	int len = strlen(firstchars);
	Element *rightAuto = (*a)->current;
	if (isOn(a) && !isEmpty(&(rightAuto)->next) && strcmp(rightAuto->next->line, firstchars)){
		rightAuto = (rightAuto)->next;
		if (strncmp((rightAuto)->line, firstchars, len) == 0){
			(*a)->current = rightAuto;
		}
	}

	while(strncmp((rightAuto)->line, firstchars, len) != 0 && !isEmpty(&(rightAuto->next))){
		rightAuto = rightAuto->next;
		if (strncmp((rightAuto)->line, firstchars, len) == 0){
			(*a)->current = rightAuto;
		}
	}
	rightAuto = NULL;
}

void previous(Autocomplete **a, char *firstchars) {
	int len = strlen(firstchars);
	Element *rightAuto = (*a)->current;
	if (!isEmpty(&(rightAuto)->previous) && strcmp(rightAuto->previous->line, firstchars) != 0){
		rightAuto = (rightAuto)->previous;
		if (strncmp((rightAuto)->line, firstchars, len) == 0) (*a)->current = rightAuto;
	}

	while(strncmp((rightAuto)->line, firstchars, len) != 0 && !isEmpty(&(rightAuto->previous))){
		rightAuto = rightAuto->previous;
		if (strncmp((rightAuto)->line, firstchars, len) == 0) (*a)->current = rightAuto;
	}
	rightAuto = NULL;
}

void getCurrent(Autocomplete **a, char **line) {
	strcpy(*line, ((*a)->current)->line);
}

void deleteAll(Autocomplete **a) {
	deleteList(&(*a)->head);
	(*a)->head = NULL;
	(*a)->current = NULL;
}

void printAutocomplete(int printed, char *autocompleteString) {
	for (int i=0; i<printed; i++) {
		printf("\b \b");
	}
	printf("%s", autocompleteString);
}

void goToStart(Autocomplete **a) {
	(*a)->current = (*a)->head;
}

void turnOnOff(Autocomplete **a) {
	(*a)->isOn = 1-(*a)->isOn;
}

int isOn(Autocomplete **a) {
	return (*a)->isOn;
}

/*
int main(int argc, char const *argv[])
{
	Autocomplete *a = (Autocomplete*) malloc(sizeof(Autocomplete));
	init(&a);
	parseHistory(&a, ".history");
	addLine(&a, "lolololo");
	next(&a, "");
	//printf("hello\n");
	next(&a, "");
//	previous(&a, "");
//	previous(&a, "");
//	previous(&a, "");
	previous(&a, "hh");

	char *line = malloc(MAX_SIZE * sizeof(char));
	getCurrent(&a, &line);
	printf("%s\n", line);
	saveHistory(&a, ".history");
	deleteAll(&a);
	free(line);
	free(a);
	return 0;
}
*/