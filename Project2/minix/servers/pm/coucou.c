#include <stdio.h>
#include "pm.h"
#define MAX_SIZE 128

int do_coucou(void){
	char toto[MAX_SIZE];
    sys_datacopy(m_in.m_source, (vir_bytes) m_in.m1_p1, SELF, (vir_bytes)toto, MAX_SIZE);
	printf("MESSAGE : %s\n", toto);

	return 0;
}
