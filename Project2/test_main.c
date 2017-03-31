#include <stdio.h>
#include <stdlib.h>
#include "sys_coucou.h"

int main(int argc, char const *argv[])
{
	printf("%d\n",sys_tinit());
	/*
	sys_tcreate(1);
	int topics_id[20];
	sys_tlookup(topics_id);
	printf("%d\n", topics_id[1]);*/
	return 0;
}