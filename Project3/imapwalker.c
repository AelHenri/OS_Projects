#include "imapwalker.h"
#include "utilities.h"

int read_imap(char path[], int_list *imap) {
    int dfd = open(path, O_RDWR);
    if(dfd == -1)
        return -1;

    struct super_block sb;
    if(read_superblock(dfd, &sb) == -1)
        return -1;

    unsigned int imap_size = sb.s_ninodes;

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
        }
        if (byte & ((char)1 << (i % 8))) {
            printf("%d\n", i);
            add_int(&(imap->head), i);
        }
    }

    close(dfd);
    return imap_size;
}


