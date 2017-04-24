#include "utilities.h"

void add_int(int_elmt **list, int data) {
	int_elmt *elmt = malloc(sizeof(int_elmt));
	elmt->data = data;
	elmt->next = *list;
	(*list) = elmt;
}

int pop_int(int_elmt **list) {
	int rep = -1;
	int_elmt *tmp1 = (*list);
	if (tmp1 != NULL) {
		rep = tmp1->data;
		(*list) = tmp1->next;
		free(tmp1);
		tmp1 = NULL;
	}
	return rep;
}

void empty_list(int_elmt **list) {
	while(*list != NULL) {
		pop_int(list);
	}
}

int read_superblock(int dfd, struct super_block *sb){
	if(lseek(dfd, SUPER_BLOCK_BYTES, SEEK_SET) != SUPER_BLOCK_BYTES){
		perror("lseek super block");
		return -1;
	}
	if(read(dfd, sb, sizeof(*sb)) != sizeof(*sb)){
		perror("error read superblock");
		return -1;
	}
	if(sb->s_magic != SUPER_V3){
		perror("bad magic superblock");
		return -1;
	} 
	return 0;
}