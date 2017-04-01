#include <lib.h>    // provides _syscall and message
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int coucou(char * msg);
int sys_tinit(void);
int sys_tlookup(int topics_id[], int size);
int sys_tcreate(int topic_id);
int sys_tpublisher(int publisher_id, int topic_id);
int sys_tsubscriber(int subscriber_id, int topic_id);
int sys_tpublish(int topic_id, int publisher_id, char *msg);
int sys_tretrieve(int topic_id, int subscriber_id, char msg[], int size);