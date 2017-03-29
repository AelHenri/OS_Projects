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

    m.m1_p1 = topics_id;   

    return ( _syscall(PM_PROC_NR, PM_TLOOKUP, &m) );
}

int sys_tcreate(int topic_id){
    message m;

    m.m1_p1 = topic_id;   

    return ( _syscall(PM_PROC_NR, PM_TCREATE, &m) );
}

int sys_tpublisher(int publisher_id, int topic_id){
    message m;  

    m.m1_i1 = publisher_id;
    m.m1_p1 = topic_id;

    return ( _syscall(PM_PROC_NR, PM_TPUBLISHER, &m) );
}

int sys_tsubscriber(int subscriber_id, int topic_id){
    message m;
    
    m.m1_i1 = subscriber_id;
    m.m1_p1 = topic_id;
    
    return ( _syscall(PM_PROC_NR, PM_TSUBSRIBER, &m) );
}

int sys_tpublish(int publisher_id, int topic_id, char *msg){
    message m;
    
    m.m1_i1 = publisher_id;
    m.m1_p1 = topic_id;
    m.m1_p2 = msg;

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