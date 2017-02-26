#include "autocomplete.h"

#define MAX_SIZE 50

void init(Autocomplete **a) {
	(*a)->head = NULL;
	(*a)->current = NULL;
}

void parseHistory(Autocomplete **a, char *path) {
	FILE *file = fopen(path, "r");
	char *line = NULL;
	size_t size = 0;

	while(getline(&line, &size, file) != -1) {
		int len = strlen(line);
		if (line[len-1] == '\n')
			line[len-1] = '\0';
		addLine(a, line);
	}

	fclose(file);
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
	fprintf(file, "%s\n", (*a)->current->line);
	fclose(file);
}

void addLine(Autocomplete **a, char* line) {
	push(&((*a)->head), line);
	(*a)->current = (*a)->head;
}

void next(Autocomplete **a, char *firstchars) {
	if (firstchars[0] == '\0' && !isEmpty(&((*a)->current)) && !isEmpty(&((*a)->current)->next)) {
		(*a)->current = ((*a)->current)->next;
	}
	else {
		int len = strlen(firstchars);
		do {
			if (!isEmpty(&((*a)->current)->next)){
				(*a)->current = ((*a)->current)->next;
			}
		}
		while(strncmp(((*a)->current)->line, firstchars, len) != 0);
	}
}

void previous(Autocomplete **a, char *firstchars) {
	if (!isEmpty(&((*a)->current)) && !isEmpty(&((*a)->current)->previous)) {
		(*a)->current = ((*a)->current)->previous;
	}
	else {
		int len = strlen(firstchars);
		do {
			if (!isEmpty(&((*a)->current)->previous)){
				(*a)->current = ((*a)->current)->previous;
			}
		}
		while(strncmp(((*a)->current)->line, firstchars, len) != 0);
	}
}

void getCurrent(Autocomplete **a, char **line) {
	strcpy(*line, ((*a)->current)->line);
}

int main(int argc, char const *argv[])
{
	Autocomplete *a = (Autocomplete*) malloc(sizeof(Autocomplete));
	init(&a);
	//parseHistory(&a, ".history");
	addLine(&a, "hello");
	addLine(&a, "there");
	addLine(&a, "my");
	addLine(&a, "name is");
	addLine(&a, "henri");
	saveHistory(&a, ".history");
	//char *line = malloc(MAX_SIZE * sizeof(char));
	//getCurrent(&a, &line);
	//printf("%s\n", line);
	return 0;
}

