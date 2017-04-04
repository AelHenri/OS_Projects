#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "sys_topic.h"

void sample_test_1() {
	int pid = getpid();
	char buf1[MAX_MSG_SIZE];
	char buf2[MAX_MSG_SIZE];
	int topic1 = 1;
	int topic2 = 2;
	printf("Hi, I am process number %d.\n", pid);
	sys_tpublisher(pid, topic1);
	sys_tsubscriber(pid, topic2);

	sprintf(buf1, "Hi there! I am %d and I sent this via topic %d.", pid, topic1);
	sys_tpublish(topic1, pid, buf1);

	int ret = sys_tretrieve(topic2, pid, buf2, MAX_MSG_SIZE);
	while(ret == -NO_MESSAGE_FOUND) {
		sleep(1);
		ret = sys_tretrieve(topic2, pid, buf2, MAX_MSG_SIZE);
	}

	if (ret > 0)
		printf("(in process %d) %s\n", pid, buf2);
	else
		printf("Retrieve error %d.\n", ret);
}

void sample_test_2() {
	int pid = getpid();
	char buf1[MAX_MSG_SIZE];
	char buf2[MAX_MSG_SIZE];
	int topic1 = 2;
	int topic2 = 1;
	printf("Hi, I am process number %d.\n", pid);
	sys_tpublisher(pid, topic1);
	sys_tsubscriber(pid, topic2);

	int ret = sys_tretrieve(topic2, pid, buf2, MAX_MSG_SIZE);
	while(ret == -NO_MESSAGE_FOUND) {
		sleep(1);
		ret = sys_tretrieve(topic2, pid, buf2, MAX_MSG_SIZE);
	}

	if (ret > 0) {
		printf("(in process %d) %s\n", pid, buf2);
		sprintf(buf1, "Hi there! I am %d and I sent this via topic %d.", pid, topic1);
		sys_tpublish(topic1, pid, buf1);

	}
	else
		printf("Retrieve error %d.\n", ret);

}

void sample_test() {
	sys_tinit();
	sys_tcreate(1);
	sys_tcreate(2);
	int pid = fork();
	if(pid > 0) {
		sample_test_1();
	}
	else if (pid == 0) {
		sample_test_2();
	}
	else {
		perror("fork");
	}

}

void manual_user() {
	sys_tinit();
	sys_tcreate(1);
	sys_tcreate(2);
	int pid = getpid();
	sys_tpublisher(pid, 1);
	sys_tsubscriber(pid, 2);
	size_t nbytes = MAX_MSG_SIZE;
	char *buf1;
	char buf2[MAX_MSG_SIZE];
	int read, ret, pub;

	while(1) {
		printf(">");
		buf1 = malloc((nbytes+1) * sizeof(char));
		read = getline(&buf1, &nbytes, stdin);

		if (read == -1) {
			printf("Getline error, try again.\n");
			free(buf1);
			continue;
		}
		else {
			pub = sys_tpublish(1, pid, buf1);
			if (pub != SUCCESS) {
				printf("publish error %d\n", pub);
				exit(EXIT_FAILURE);
			}
		}
		
		ret = sys_tretrieve(2, pid, buf2, MAX_MSG_SIZE);
		while(ret == -NO_MESSAGE_FOUND) {
			sleep(1);
			ret = sys_tretrieve(2, pid, buf2, MAX_MSG_SIZE);
		}
		if (ret > 0) {
			printf("%s\n", buf2);	
		}
		else {
			printf("Retrieve error %d.\n", ret);
		}
	}
}

void manual_bot() {
	int pid = getpid();
	sys_tpublisher(pid, 2);
	sys_tsubscriber(pid, 1);
	char buf2[MAX_MSG_SIZE];
	int ret, pub;

	while(1) {
		int ret = sys_tretrieve(1, pid, buf2, MAX_MSG_SIZE);
		while(ret == -NO_MESSAGE_FOUND) {
			sleep(1);
			ret = sys_tretrieve(1, pid, buf2, MAX_MSG_SIZE);
		}

		if (ret > 0) {
			printf("Received: %s\n", buf2);
			pub = sys_tpublish(2, pid, "Message received from bot.");

			if (pub != SUCCESS) {
				printf("publish error %d\n", pub);
				exit(EXIT_FAILURE);
			}
		}
		else {
			printf("Retrieve error %d.\n", ret);
		}
	}
}

int main(int argc, char const *argv[])
{

	if (argc > 1) {
		if (strcmp(argv[1], "sample") == 0) {
			sample_test();
		}
		else if(strcmp(argv[1], "manualu") == 0) {
			manual_user();
		}
		else if(strcmp(argv[1], "manualb") == 0) {
			manual_bot();
		}
		else {
			sample_test();
		}
	}
	else {
		sample_test();
	}
	return 0;
}