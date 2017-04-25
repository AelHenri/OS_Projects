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

	read_imap(path, actual_imap);
	get_imap_from_inodes(imap, nb_device);

	int_elmt *it1 = actual_imap->head;
	int_elmt *it2 = imap->head;

	int index = actual_imap->head->data;
	while(it1 != NULL && it2 != NULL) {
		if (it1->data != it2->data) {
			printf("Inode number %d is different in the bitmaps (%d vs %d).\n", index, it1->data, it2->data);
		}
		index--;
		it1 = it1->next;
		it2 = it2->next;
	}
}