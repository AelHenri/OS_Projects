#include "check_imap.h"

void check_imaps(char path[]) {
	int nb_device = -1;
    if(strcmp(path, ROOT) == 0){
        nb_device = ROOT_ID;
    }
    if(strcmp(path, USR) == 0){
        nb_device = USR_ID;
    }
    if(strcmp(path, HOME) == 0){
        nb_device = HOME_ID;
    } 

	int_list *actual_imap = malloc(sizeof(int_list));
	actual_imap->device = nb_device;
	actual_imap->head = NULL;
	int_list *imap = malloc(sizeof(int_list));
	imap->device = nb_device;
	imap->head = NULL;

	printf("Getting imap from the inode bitmap in superblock...\n");
	read_imap(path, actual_imap);
	printf("\n");
	printf("Getting imap from the actual inodes...\n");
	get_imap_from_inodes(path, imap);
	printf("\n");

	int_elmt *it1 = actual_imap->head;
	int_elmt *it2 = imap->head;

	int index = actual_imap->head->data;
	int diffs = 0;
	while(it1 != NULL && it2 != NULL) {
		if (it1->data != it2->data) {
			printf("Inode number %d is different in the bitmaps (%d vs %d).\n", index, it1->data, it2->data);
			diffs = 1;
		}
		index--;
		it1 = it1->next;
		it2 = it2->next;
	}
	if (!diffs) {
		printf("No damage found.\n");
	}
}