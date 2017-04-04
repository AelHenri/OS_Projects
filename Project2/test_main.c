#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sys_topic.h"

int main(int argc, char const *argv[])
{	
	int res;
	int size = 20;
	int buff_size = 100;
	int topics_id[size];
	sys_tinit();
	sys_tcreate(1);
	sys_tcreate(2);
	sys_tcreate(5);
	sys_tcreate(6);
	int i;
	int nb_topics = sys_tlookup(topics_id, size);
	for (i = 0; i<nb_topics; i++) {
		printf("%d\n", topics_id[i]);
	}
	res = sys_tpublisher(getpid(),5);
	printf(" publisher %d\n", res);
	nb_topics = sys_tlookup(topics_id, size);
	for (i = 0; i<nb_topics; i++) {
		printf("after publisher%d\n", topics_id[i]);
	}
	res = sys_tsubscriber(getpid(),5);
	printf(" publisher %d\n", res);
	nb_topics = sys_tlookup(topics_id, size);
	for (i = 0; i<nb_topics; i++) {
		printf("after subscriber%d\n", topics_id[i]);
	}
	res =sys_tsubscriber(getpid(), 0);
	printf(" subscriber %d\n", res);
	nb_topics = sys_tlookup(topics_id, size);
/*	for (i = 0; i<nb_topics; i++) {
		printf("after add subscriber existing%d\n", topics_id[i]);
	}
*/
	res = sys_tpublish(5, getpid(), "coucou");
	nb_topics = sys_tlookup(topics_id, size);
/*	for (i = 0; i<nb_topics; i++) {
		printf("after publish%d\n", topics_id[i]);
	}
*/
	printf(" publish %d\n", res);
	res = sys_tpublish(5, 6, "coucou");
	printf(" publish %d\n", res);
	char msg[100];
	res = sys_tretrieve(5, getpid(), msg, buff_size);
	printf("retrieve %d\n", res);
	printf("%s\n", msg);
	return 0;
}