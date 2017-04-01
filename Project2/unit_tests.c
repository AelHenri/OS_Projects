#include "unit_tests.h"

void unit_tlookup() {
	printf("UNIT TEST: TOPIC LOOKUP:\n");
	int topics[MAX_SIZE];
	sys_tinit();

	printf("|---EMPTY LOOKUP...");
	int res = sys_tlookup(topics, MAX_SIZE);
	assert(res == 0);
	printf("...OK\n");

	printf("TOPIC LOOKUP OK\n");
	printf("\n");
}

void unit_tcreate() {
	printf("UNIT TEST: TOPIC CREATE:\n");
	int topics[MAX_SIZE];
	int res;
	int size;
	sys_tinit();


	printf("|---FIRST TOPIC CREATED...");
	res = sys_tcreate(0);
	assert(res == SUCCESS);
	printf("...OK\n");

	printf("|---FIRST TOPIC PRESENT...");
	size = sys_tlookup(topics, MAX_SIZE);
	assert(size == 1);
	assert(topics[0] == 0);
	printf("...OK\n");

	printf("|---SAME TOPIC CREATION ATTEMPT...");
	res = sys_tcreate(0);
	assert(res == TOPIC_DUPLICATED);
	size = sys_tlookup(topics, MAX_SIZE);
	assert(size == 1);
	printf("...OK\n");

	printf("|--SECOND TOPIC CREATED...");
	res = sys_tcreate(1);
	assert(res == SUCCESS);
	printf("...OK\n");

	printf("|---BOTH TOPICS PRESENT...");
	size = sys_tlookup(topics, MAX_SIZE);
	assert(size == 2);
	assert(topics[0] == 1);
	assert(topics[1] == 0);
	printf("...OK\n");

	printf("TOPIC CREATE OK\n");
	printf("\n");
}

void unit_tpublisher() {
	printf("UNIT TEST: TOPIC PUBLISHER:\n");
	int res;
	//int size;
	int pid = getpid();
	sys_tinit();
	sys_tcreate(0);
	sys_tcreate(1);
	sys_tcreate(3);

	printf("|--PUBLISHER TO FIRST TOPIC...");
	res = sys_tpublisher(pid, 0);
	assert(res == SUCCESS);
	printf("...OK\n");

	printf("|--PUBLISHER TO SAME TOPIC...");
	res = sys_tpublisher(pid, 0);
	assert(res == PUBLISHER_DUPLICATED);
	printf("...OK\n");

	printf("|--PUBLISHER TO SECOND TOPIC...");
	res = sys_tpublisher(pid, 1);
	assert(res == SUCCESS);
	printf("...OK\n");

	printf("|--PUBLISHER TO INEXISTANT TOPIC...");
	res = sys_tpublisher(pid, 2);
	assert(res == TOPIC_NOT_FOUND);
	printf("...OK\n");

	printf("TOPIC PUBLISHER OK\n");
	printf("\n");
}

void unit_tsubscriber() {
	printf("UNIT TEST: TOPIC SUBSCRIBER:\n");
	int res;
	//int size;
	int pid = getpid();
	sys_tinit();
	sys_tcreate(0);
	sys_tcreate(1);
	sys_tcreate(3);

	printf("|--SUBSCRIBER TO FIRST TOPIC...");
	res = sys_tsubscriber(pid, 0);
	assert(res == SUCCESS);
	printf("...OK\n");

	printf("|--SUBSCRIBER TO SAME TOPIC...");
	res = sys_tsubscriber(pid, 0);
	assert(res == SUBSCRIBER_DUPLICATED);
	printf("...OK\n");

	printf("|--SUBSCRIBER TO SECOND TOPIC...");
	res = sys_tsubscriber(pid, 1);
	assert(res == SUCCESS);
	printf("...OK\n");

	printf("|--SUBSCRIBER TO INEXISTANT TOPIC...");
	res = sys_tsubscriber(pid, 2);
	assert(res == TOPIC_NOT_FOUND);
	printf("...OK\n");

	printf("TOPIC SUBSCRIBER OK\n");
	printf("\n");
}

void unit_tpublish() {
	printf("UNIT TEST: TOPIC PUBLISH:\n");
	int res;
	//int size;
	int pid = getpid();
	sys_tinit();
	sys_tcreate(0);
	sys_tcreate(1);
	sys_tcreate(3);
	sys_tpublisher(pid, 0);
	sys_tpublisher(pid, 1);

	printf("|--FIRST MESSAGE PUBLISHED TO FIRST TOPIC...");
	res = sys_tpublish(0, pid, "first");
	assert(res == SUCCESS);
	printf("...OK\n");

	printf("|--FOUR NEXT MESSAGES PUBLISHED...");
	res = sys_tpublish(0, pid, "second");
	assert(res == SUCCESS);
	res = sys_tpublish(0, pid, "third");
	assert(res == SUCCESS);
	res = sys_tpublish(0, pid, "fourth");
	assert(res == SUCCESS);
	res = sys_tpublish(0, pid, "fifth");
	assert(res == SUCCESS);
	printf("...OK\n");

	printf("|--ATTEMPT TO PUBLISH SIXTH MESSAGE...");
	res = sys_tpublish(0, pid, "sixth");
	assert(res == MESSAGE_BUF_FULL);
	printf("...OK\n");

	printf("|--FIRST MESSAGE PUBLISHED TO SECOND TOPIC...");
	res = sys_tpublish(1, pid, "first");
	assert(res == SUCCESS);
	printf("...OK\n");

	printf("|--ATTEMPT TO PUBLISH TO UNAUTHORIZED TOPIC...");
	res = sys_tpublish(3, pid, "first");
	assert(res == NOT_PUBLISHER_TOPIC);
	printf("...OK\n");

	printf("|--ATTEMPT TO INEXISTANT TOPIC...");
	res = sys_tpublish(2, pid, "first");
	assert(res == TOPIC_NOT_FOUND);
	printf("...OK\n");
	printf("TOPIC PUBLISH OK\n");
	printf("\n");
}

void unit_tretrieve(){
	printf("UNIT TEST: TOPIC RETRIEVE:\n");
	int res;
	char buff[100];
	int pid = getpid();
	int pid2 = pid + 1;
	sys_tinit();
	sys_tcreate(0);
	sys_tcreate(1);
	sys_tcreate(3);
	sys_tpublisher(pid, 0);
	sys_tpublisher(pid, 1);
	sys_tsubscriber(pid, 0);
	sys_tsubscriber(pid, 1);
	sys_tsubscriber(pid2, 0);
	sys_tpublish(0, pid, "first");
	
	printf("|--ATTEMPT TO RETRIEVE MESSAGE ");
	res = sys_tretrieve(0, pid, buff, 100);
	assert(res == 5); //size of the msg 
	printf("...OK\n");

	buff[0] = '\0';
	printf("|--ATTEMPT TO RETRIEVE MESSAGE AFTER RETRIEVING ALL EXISTING MESSAGES" );
	res = sys_tretrieve(0, pid2, buff, 100);
	assert(res == ALREADY_RETRIEVED);
	printf("...OK\n");	

	buff[0] = '\0';
	printf("|--ATTEMPT TO RETRIEVE MESSAGE FROM UNAUTHORIZED SUBSCRIBER");
	res = sys_tretrieve(3, pid, buff, 100);
	assert(res == NOT_SUBSCRIBER_TOPIC);
	printf("...OK\n");	

	buff[0] = '\0';
	printf("|--ATTEMPT TO RETRIEVE UNEXISTING MESSAGE " );
	res = sys_tretrieve(1, pid, buff, 100);
	assert(res == NO_MESSAGE_FOUND);
	printf("...OK\n");	

}

void unit_all(){

	unit_tlookup();
	unit_tcreate();
	unit_tpublisher();
	unit_tsubscriber();
	unit_tpublish();	
	unit_tretrieve();
}

int main(int argc, char const *argv[])
{
	unit_all();
	return 0;
}