#include <lib.h>    // provides _syscall and message
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_MSG_SIZE 512

#define SUCCESS 1
#define TOPIC_DUPLICATED 2
#define TOPIC_MAX_REACHED 3
#define TOPIC_NOT_FOUND 4
#define PUBLISHER_DUPLICATED 5
#define SUBSCRIBER_DUPLICATED 6
#define MSG_LEN_OVERFLOW 7
#define NOT_SUBSCRIBER_TOPIC 8
#define MESSAGE_BUF_FULL 9
#define NO_MESSAGE_FOUND 10
#define ALREADY_RETRIEVED 11
#define NOT_PUBLISHER_TOPIC 12

int sys_tinit(void);
int sys_tlookup(int topics_id[], int size);
int sys_tcreate(int topic_id);
int sys_tpublisher(int publisher_id, int topic_id);
int sys_tsubscriber(int subscriber_id, int topic_id);
int sys_tpublish(int topic_id, int publisher_id, char *msg);
int sys_tretrieve(int topic_id, int subscriber_id, char msg[], int size);