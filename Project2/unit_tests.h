#include <stdio.h>
#include <stdlib.h>
#include "sys_coucou.h"

#define MAX_SIZE 64

#define SUCCESS 1
#define TOPIC_DUPLICATED 2
#define TOPIC_MAX_REACHED 3
#define TOPIC_NOT_FOUND 4
#define PUPLISHER_DUPLICATED 5
#define SUBSCRIBER_DUPLICATED 6
#define MSG_LEN_OVERFLOW 7
#define NOT_SUBSCRIBER_TOPIC 8
#define MESSAGE_BUF_FULL 9
#define NO_MESSAGE_FOUND 10
#define ALREADY_RETRIEVED 11

void unit_tinit();
void unit_tlookup();
void unit_tcreate();
void unit_tpublisher();
void unit_tsubscriber();
void unit_tpublish();
void unit_tretrieve();
void unit_all();