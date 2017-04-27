#include "check_zmap.h"

int repair_bit_zmap(char path[], int zone_id, int bit) {
	printf("Setting bit bit number %d to %d...\n", zone_id, bit);
	int dfd = open(path, O_RDWR);
    if(dfd == -1) {
    	perror("open");
        return -1;
    }

    struct super_block sb;
    if(read_superblock(dfd, &sb) == -1) {
    	perror("read sb");
        return -1;
    }

    unsigned int zmap_size = sb.s_zones;
    //printf("IMAP SIZE: %u\n", imap_size);

    int offset = (START_BLOCK+sb.s_imap_blocks) * sb.s_block_size;
    if(lseek(dfd, offset, SEEK_SET) != offset){
        perror("lseek zmap");
        return -1;
    }

    int i = 0;
    char readByte = 0;
    char writeByte = 0;
    while (i != zone_id) {
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
    //printf("zone %hu\n", writeByte);
    lseek(dfd, -1, SEEK_CUR);
    if(write(dfd, &writeByte, 1) != 1) {
    	perror("write byte");
    	return -1;
    }
    return 0;
}

void check_zmaps(char path[]) {
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

	int_list *actual_zmap = malloc(sizeof(int_list));
	actual_zmap->device = nb_device;
	actual_zmap->head = NULL;
	int_list *zmap = malloc(sizeof(int_list));
	zmap->device = nb_device;
	zmap->head = NULL;

	//repair_bit_zmap(path, 6, 1);
	printf("Getting zmap from the inode bitmap in superblock...\n");
	read_zmap(path, actual_zmap);
	reverse_list(&(actual_zmap->head));
	printf("\n");
	printf("Getting zmap from the actual inodes...\n");
	get_zmap_from_inodes(path, zmap);
	reverse_list(&(zmap->head));
	printf("\n");

	int_elmt *it1 = actual_zmap->head;
	int_elmt *it2 = zmap->head;
	int index = 0;
	int diffs = 0;
	while(it1 != NULL && it2 != NULL) {
		if (it1->data != it2->data) {
			printf("Zone number %d is different in the bitmaps (%d vs %d). Attempting to repair.\n", index, it1->data, it2->data);
			repair_bit_zmap(path, index, it2->data);
			diffs = 1;
		}
		index++;
		it1 = it1->next;
		it2 = it2->next;
	}
	if (!diffs) {
		printf("No damage found.\n");
	}

	//print_list(&(actual_zmap->head));
	//printf("\n");
	//print_list(&(zmap->head));
	//printf("\n");
}