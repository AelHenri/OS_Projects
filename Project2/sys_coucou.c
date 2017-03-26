#include "sys_coucou.h"
#define MAX_SIZE 128

int coucou(char *msg) {
    message m;  // Minix uses message to pass parameters to a system call
 	m.m1_p1 = msg;
    return _syscall(PM_PROC_NR, PM_COUCOU, &m);

}