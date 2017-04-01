#include <stdio.h>
#include <stdlib.h>
#include "sys_coucou.h"

int main(int argc, char const *argv[])
{
	int topics_id[20];
	sys_tinit();
	sys_tcreate(1);
	sys_tcreate(2);
	sys_tcreate(5);
	sys_tcreate(6);

	sys_tlookup(topics_id);
	return 0;
}