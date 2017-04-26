#include "check_imap.h"

int repair_bit(char path[], int inode_id, int bit) {
	int dfd = open(path, O_RDWR);
    if(dfd == -1)
        return -1;

    struct super_block sb;
    if(read_superblock(dfd, &sb) == -1)
        return -1;

    unsigned int imap_size = sb.s_ninodes;
    //printf("IMAP SIZE: %u\n", imap_size);

    int offset = (START_BLOCK) * sb.s_block_size;
    if(lseek(dfd, offset, SEEK_SET) != offset){
        perror("lseek inode");
        return -1;
    }

    int i = 0;
    char readByte = 0;
    char writeByte = 0;
    while (i != inode_id) {
    	if (i % 8 == 0) {
            if(read(dfd, &readByte, 1) != 1) {
                perror("read byte");
                return -1;
            }
        }
        i++;
    }
    if (i % 8 == 0) {
        if(read(dfd, &readByte, 1) != 1) {
            perror("read byte");
            return -1;
        }
    }

    if (bit) {
    	writeByte = readByte | ((char)1 << (i % 8));
    } else {
    	writeByte = readByte & ~((char)1 << (i % 8));
    }
    //printf("%hu\n", writeByte);
    lseek(dfd, -1, SEEK_CUR);
    if(write(dfd, &writeByte, 1) != 1) {
    	perror("write byte");
    	return -1;
    }
    return 0;
}

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

	//repair_bit(path, 8, 0);
	printf("Getting imap from the inode bitmap in superblock...\n");
	read_imap(path, actual_imap);
	printf("\n");
	printf("Getting imap from the actual inodes...\n");
	get_imap_from_inodes(path, imap);
	printf("\n");

	int_elmt *it1 = actual_imap->head;
	int_elmt *it2 = imap->head;
	printf("coucou\n");
	int index = actual_imap->head->index;
	int diffs = 0;
	while(it1 != NULL && it2 != NULL) {
		if (it1->data != it2->data) {
			printf("Inode number %d is different in the bitmaps (%d vs %d). Attempting to repair.\n", index, it1->data, it2->data);
			repair_bit(path, index, it2->data);
			diffs = 1;
		}
		index--;
		it1 = it1->next;
		it2 = it2->next;
	}
	if (!diffs) {
		printf("No damage found.\n");
	}

	print_list(&(actual_imap->head));
	printf("\n");
	print_list(&(imap->head));
	printf("\n");
}