#include <stdio.h>
#include <stdlib.h>
#include "structs.h"


void test_topic_create(){
    int status;
    sys_tinit();
    
    printf("\nTopic Create Test\n");
    
    printf("Adding a topic : TOPIC_1\n");
    status = sys_tcreate("TOPIC_1");
 }

int main(int argc, char const *argv[])
{
	topic *topic_list = NULL;
	int topic = 1;
	push_topic(&topic_list, topic);
	push_message(&(topic_list->mlist), "Bien le bonjour.");
	push_process(&(topic_list->publishers), getpid());
	push_process(&(topic_list->subscribers), getpid());
	printf("process is for publisher : %d\n", topic_list->publishers->pid);
	printf("%s\n", topic_list->mlist->data);
	delete_topic_list(&topic_list);
	return 0;
}