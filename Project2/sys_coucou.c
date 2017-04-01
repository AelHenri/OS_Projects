#include "sys_coucou.h"
#define MAX_SIZE 128

int coucou(char *msg) {
    message m;  // Minix uses message to pass parameters to a system call
 	m.m1_p1 = msg;
    return _syscall(PM_PROC_NR, PM_COUCOU, &m);

}

int sys_tinit(void){  
    message m;
    
    return ( _syscall(PM_PROC_NR, PM_TINIT, &m) );   
}

int sys_tlookup(int topics_id[]){
    message m;
    m.m1_i1 = 1;
    m.m1_p1 = malloc(20*sizeof(char));
    int syscall = _syscall(PM_PROC_NR, PM_TLOOKUP, &m);
    printf("%d\n", m.m1_i1);
    for (int i=0; i<1; i++) {
        topics_id[i] = m.m1_p1[i];
        //printf("%d\n", topics_id[i]);
    }

    return syscall;
}

int sys_tcreate(int topic_id){
    message m;

    m.m1_i1 = topic_id;   

    return ( _syscall(PM_PROC_NR, PM_TCREATE, &m) );
}

int sys_tpublisher(int publisher_id, int topic_id){
    message m;  

    m.m1_i1 = publisher_id;
    m.m1_i2 = topic_id;

    return ( _syscall(PM_PROC_NR, PM_TPUBLISHER, &m) );
}

int sys_tsubscriber(int subscriber_id, int topic_id){
    message m;
    
    m.m1_i1 = subscriber_id;
    m.m1_i2 = topic_id;
    
    return ( _syscall(PM_PROC_NR, PM_TSUBSRIBER, &m) );
}

int sys_tpublish(int publisher_id, int topic_id, char *msg){
    message m;
    
    m.m1_i1 = publisher_id;
    m.m1_i2 = topic_id;
    m.m1_p1 = msg;

    return ( _syscall(PM_PROC_NR, PM_TPUBLISH, &m) );
}
/*
int sys_tretrieve(int topic_id, char *mesg, int subscriber_id){
    message m;
    
    m.m1_i1 = subscriber_id;
    m.m1_p1 = topic_id;
    m.m1_p2 = mesg;
    
    int sta = _syscall(PM_PROC_NR, PM_TRETRIEVE, &m);
    return sta;
}
*/