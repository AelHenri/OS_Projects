#include <lib.h>    // provides _syscall and message
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 128

int main(int argc, char **argv) {
	if (argc < 2)
		exit(1);
    message m;  // Minix uses message to pass parameters to a system call
	m.m1_p1 = malloc(MAX_SIZE*sizeof(char));
	strcpy(m.m1_p1, argv[1]);
 
    _syscall(PM_PROC_NR, PM_COUCOU, &m);
        /* _syscall leads to the system server identified by PM_PRO_NR (the PM
         * server process) invoking the function identified by call number 
         * PRINTMSG with parameters in the message copied to address &m
         */   
    free(m.m1_p1);
    m.m1_p1 = NULL;
}