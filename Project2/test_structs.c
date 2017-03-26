#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

int main(int argc, char const *argv[])
{
	topic *topic_list = NULL;
	push_topic(&topic_list);
	push_message(&(topic_list->mlist), "Bien le bonjour.");
	push_process(&(topic_list->publishers), getpid());
	push_process(&(topic_list->subscribers), getpid());

	printf("%s\n", topic_list->mlist->data);

	delete_topic_list(&topic_list);
	return 0;
}