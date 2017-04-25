#include "imapwalker.h"

int read_imap(char path[], int_list *imap) {
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

    int dfd = open(path, O_RDWR);
    if(dfd == -1)
        return -1;

    struct super_block sb;
    if(read_superblock(dfd, &sb) == -1)
        return -1;

    unsigned int imap_size = sb.s_ninodes;
    printf("IMAP SIZE: %u\n", imap_size);

    int offset = (START_BLOCK) * sb.s_block_size;
    if(lseek(dfd, offset, SEEK_SET) != offset){
        perror("lseek inode");
        return -1;
    }

    char byte = 0;
    for(int i = 0; i < imap_size; i++) {
        if (i % 8 == 0) {
            if(read(dfd, &byte, 1) != 1) {
                perror("read byte");
                return -1;
            }
            //printf("Byte read: %hhu\n", byte);
        }
        if (byte & ((char)1 << (i % 8))) {
            printf("1");
            if(nb_device == imap->device){
               add_int(&(imap->head), i);
            }
        }
        else {
            printf("0");
        }
    }

    close(dfd);
    return imap_size;
}


