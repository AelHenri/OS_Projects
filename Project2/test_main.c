#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sys_coucou.h"

int main(int argc, char const *argv[])
{
	int size = 20;
	int topics_id[size];
	sys_tinit();
	sys_tcreate(1);
	sys_tcreate(2);
	sys_tcreate(5);
	sys_tcreate(6);

	int nb_topics = sys_tlookup(topics_id, size);
	for (int i = 0; i<nb_topics; i++) {
		printf("%d\n", topics_id[i]);
	}
	sys_tpublisher(getpid(),5);
	//sys_tsubscriber(getpid(), 5);
	//sys_tpublish(getpid(), 5, "coucou");
	//char msg[10];
	//sys_tretrieve(5, msg, getpid());
	return 0;
}