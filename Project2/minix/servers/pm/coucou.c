#include <stdio.h>
#include "pm.h"
#include "structs.h"

#define MAX_SIZE 128

int do_coucou(void){
	char toto[MAX_SIZE];
    sys_datacopy(m_in.m_source, (vir_bytes) m_in.m1_p1, SELF, (vir_bytes)toto, MAX_SIZE);
	printf("MESSAGE : %s\n", toto);

	return 0;
}
int do_tinit(void){
	topic_init();
	return 1;
}
int do_tcreate(void){
	int topic_id = m_in.m1_i1;
	int res = add_topic(topic_id);
	return res;
}

int do_tlookup(void){
	char *topics = malloc(nb_topics*sizeof(char));
	int res;
	res = lookup_topics(topics);
	sys_datacopy(PM_PROC_NR, (vir_bytes) topics, who_e, (vir_bytes)m_in.m1_p1, MAX_SIZE);
	return nb_topics;
}  

int do_tsubscriber(void){
	int subscriber_id = m_in.m1_i1;
	int topic_id = m_in.m1_i2;
	int res = add_subscriber_to_topic(topic_id, subscriber_id);
	return res;
} 

int do_tpublisher(void){
	int publisher_id = m_in.m1_i1;
	int topic_id = m_in.m1_i2;
	int res = add_publisher_to_topic(topic_id, publisher_id);
	return res;
} 

int do_tpublish(void){
	int topic_id = m_in.m1_i1;
	int publisher_id = m_in.m1_i2;
	char msg[MAX_CHAR];
	sys_datacopy(m_in.m_source, (vir_bytes) m_in.m1_p1, SELF, (vir_bytes)msg, MAX_CHAR);
	int res = publish_message(topic_id, publisher_id, msg);
	return res;
}

int do_tretrieve(void){
	int topic_id = m_in.m1_i1;
	int subscriber_id = m_in.m1_i2;
	char msg[MAX_CHAR];
	sys_datacopy(m_in.m_source, (vir_bytes) m_in.m1_p1, SELF, (vir_bytes)msg, MAX_CHAR);
	int res = retrieve_message(topic_id, subscriber_id, msg) ;
	return res;
} 

