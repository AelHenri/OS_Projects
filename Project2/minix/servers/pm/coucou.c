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
	int topics[MAX_NB_TOPICS];
	int res = lookup_topics(topics);
	if(res == 1){
		sys_datacopy(m_in.m_source, (vir_bytes) m_in.m1_p1, SELF, (vir_bytes)topics, MAX_SIZE);
	}
	return res;
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
	char msg[MAX_CHAR];
	sys_datacopy(m_in.m_source, (vir_bytes) m_in.m1_p1, SELF, (vir_bytes)msg, MAX_CHAR);
	int res = publish_message(topic_id, msg);
	return res;
}

int do_tretrieve(void){
	return 1;
} 

