#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

/*
void topic_init();
int lookup_topics(char *topics_id);
int add_topic(int topic_id);
int add_publisher_to_topic(int topic_id, int publisher_id);
int add_subscriber_to_topic(int topic_id, int subscriber_id);
int publish_message(int topic_id, char msg[]);
*/
/*
void test_topic_create(){
    int status;
    sys_tinit();
    
    printf("\nTopic Create Test\n");
    
    printf("Adding a topic : \n");
    status = sys_tcreate("1");
    printf("print status  %d:\n", status);
 }
*/
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
	//test_topic_create();
	
	topic_init();
	add_topic(1);
	add_topic(3);
	int res = add_publisher_to_topic(1, 3);
	printf("add pub %d\n", res); 
	res = add_subscriber_to_topic(1, 3);
	printf("add sub %d\n", res); 
	res = add_subscriber_to_topic(1, 3);
	printf("add sub already existing %d\n", res); 
	char *msg1 = "COUCOUU";
	res = publish_message(1, msg1);
	printf("publish msg 1 %d\n", res); 
	char *msg2 = "COUCOUU2!!!";
	res = publish_message(1, msg2);
	printf("publish msg 2 %d\n", res); 
	//topic *top = ;
	print_topic(find_topic(&(topics_list), 1));


	return 0;
}


