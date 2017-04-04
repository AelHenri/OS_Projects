#include <stdio.h>
#include "sys_topic.h"

#define MAX_NB_PUBLISHER 10
#define MAX_NB_SUBSCRIBER 10 
#define MAX_NB_MESSAGES 5 
#define MAX_CHAR 1024
#define MAX_NB_TOPICS 10

#define SUCCESS 1
#define TOPIC_DUPLICATED 2
#define TOPIC_MAX_REACHED 3
#define TOPIC_NOT_FOUND 4
#define PUPLISHER_DUPLICATED 5
#define SUBSCRIBER_DUPLICATED 6
#define MSG_LEN_OVERFLOW 7
#define NOT_SUBSCRIBER_TOPIC 8

char *result_list[]={
	"ND",
	"SUCCESS",
	"TOPIC IS DUPLICATED",
	"NB MAX TOPIS IS REACHED",
	"TOPIC NOT FOUND",
	"PUPLISHER DUPLICATED",
	"SUBSCRIBER DUPLICATED",
	"OVERFLOW OF THE MESSAGE",
	"NOT A SUBSCRIPER OF THE TOPIC"
};

void test_topic_create(){
    int res;
    sys_tinit();
    
    printf("Topic Create Test\n");
    
    printf("Adding topic with t_id = 1. \n");
    res = sys_tcreate("1");

    if(res == 1){
    	printf("Test passed.\n");
    }else{
    	printf("Test failed.\n");
    }
 }

void test_topic_lookup(){
	int res:
	sys_tinit();
    printf("Topic create test\n");    
    printf("Adding topic with t_id = 1. \n");
    res = sys_tcreate("1");
    printf("Result : %s\n", result_list[status]);
    printf("Adding topic with t_id = 2. \n");
    res = sys_tcreate("2");
    printf("Result : %s\n", result_list[status]);
    printf("Adding topic with t_id = 2. \n");
    res = sys_tcreate("3");
    printf("Look up topics test \n");
    int topics_id[MAX_NB_TOPICS];
    res = sys_tlookup(all_topics);  
    printf("The topics are :\n");
    int len=sizeof(topics_id)/sizeof(int);
    int i;
    for(i=0; i < len; i++){
    	print("%d \n", topics_id[i]);
    }
    if(res == 1){
    	printf("Test passed.\n");
    }else{
    	printf("Test failed.\n");
    }
}

void test_topic_publisher(){
	int res:
	sys_tinit();
    printf("Topic create test\n");
    printf("Adding topic with t_id = 1. \n");
    res = sys_tcreate("1");	
    printf("Result : %s\n", result_list[status]);
    printf("Process %d asking to become a publisher of topic %d\n", 1, 1);
    res = sys_tpublisher(1, 1);
    printf("Result : %s\n", result_list[status]);
    if(res == 1){
    	printf("Test passed.\n");
    }else{
    	printf("Test failed.\n");
    }    
}
void test_topic_subscriber(){
	int res:
	sys_tinit();
    printf("Topic create test\n");
    printf("Adding topic with t_id = 1. \n");
    res = sys_tcreate("1");	
    printf("Result : %s\n", result_list[status]);
    printf("Process %d asking to become a subscriber of topic %d\n", 1, 1);
    res = sys_tsubscriber(1, 1);
    printf("Result : %s\n", result_list[status]);
    if(res == 1){
    	printf("Test passed.\n");
    }else{
    	printf("Test failed.\n");
    }    
}

void test_topic_publish(){
	int res:
	sys_tinit();
    printf("Topic create test\n");
    printf("Adding topic with t_id = 1. \n");
    res = sys_tcreate("1");	
    printf("Result : %s\n", result_list[status]);
    printf("Process %d asking to become a publisher of topic %d\n", 1, 1);
    res = sys_tpublisher(1, 1);
    printf("Result : %s\n", result_list[status]);
    res = add_publisher_to_topic(1, "HELLO WORLD")
    printf("Result : %s\n", result_list[status]);
    if(res == 1){
    	printf("Test passed.\n");
    }else{
    	printf("Test failed.\n");
    }          
}

void test_duplicate_topic(){
	int res:
	sys_tinit();
    printf("Topic create test\n");    
    printf("Adding topic with t_id = 1. \n");
    res = sys_tcreate("1");
    printf("Result : %s\n", result_list[status]);
    printf("Adding topic with t_id = 1. \n");
    res = sys_tcreate("2");
    printf("Result : %s\n", result_list[status]);
    if(res == 2){
    	printf("Test passed.\n");
    }else{
    	printf("Test failed.\n");
    } 
}


void test_subscriber_topic_not_found(){
	int res:
	sys_tinit();
    printf("Topic create test\n");
    printf("Adding topic with t_id = 1. \n");
    res = sys_tcreate("1");	
    printf("Result : %s\n", result_list[status]);
    printf("Process %d asking to become a subscriber of topic %d\n", 1, 2);
    res = sys_tsubscriber(2, 1);
    printf("Result : %s\n", result_list[status]);
    if(res == 4){
    	printf("Test passed.\n");
    }else{
    	printf("Test failed.\n");
    }    
}

void test_publisher_topic_not_found(){
	int res:
	sys_tinit();
    printf("Topic create test\n");
    printf("Adding topic with t_id = 1. \n");
    res = sys_tcreate("1");	
    printf("Result : %s\n", result_list[status]);
    printf("Process %d asking to become a publisher of topic %d\n", 1, 2);
    res = sys_tpublisher(2, 1);
    printf("Result : %s\n", result_list[status]);
    if(res == 4){
    	printf("Test passed.\n");
    }else{
    	printf("Test failed.\n");
    }    
}

void test_subscriber_topic_not_found(){
	int res:
	sys_tinit();
    printf("Topic create test\n");
    printf("Adding topic with t_id = 1. \n");
    res = sys_tcreate("1");	
    printf("Result : %s\n", result_list[status]);
    printf("Process %d asking to become a subscriber of topic %d\n", 1, 2);
    res = sys_tsubscriber(2, 1);
    printf("Result : %s\n", result_list[status]);
    if(res == 4){
    	printf("Test passed.\n");
    }else{
    	printf("Test failed.\n");
    }    
}

void test_duplicate_publisher(){
	int res:
	sys_tinit();
    printf("Topic create test\n");
    printf("Adding topic with t_id = 1. \n");
    res = sys_tcreate("1");	
    printf("Result : %s\n", result_list[status]);
    printf("Process %d asking to become a publisher of topic %d\n", 1, 2);
    res = sys_tpublisher(1, 1);
    printf("Result : %s\n", result_list[status]);
    printf("Process %d asking to become a publisher of topic %d\n", 1, 2);
    res = sys_tpublisher(1, 1);
    printf("Result : %s\n", result_list[status]);
    if(res == 5){
    	printf("Test passed.\n");
    }else{
    	printf("Test failed.\n");
    }    	
}


void test_duplicate_subscriber(){
	int res:
	sys_tinit();
    printf("Topic create test\n");
    printf("Adding topic with t_id = 1. \n");
    res = sys_tcreate("1");	
    printf("Result : %s\n", result_list[status]);
    printf("Process %d asking to become a subscriber of topic %d\n", 1, 2);
    res = sys_tsubscriber(1, 1);
    printf("Result : %s\n", result_list[status]);
    printf("Process %d asking to become a subscriber of topic %d\n", 1, 2);
    res = sys_tsubscriber(1, 1);
    printf("Result : %s\n", result_list[status]);
    if(res == 6){
    	printf("Test passed.\n");
    }else{
    	printf("Test failed.\n");
    }    	
}


void test_not_subscriber_topic(); 
void test_topic_retrieve();


