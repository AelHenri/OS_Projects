#include "zmapwalker.h"

int read_zmap(char path[], int_list *zmap) {
    int dfd = open(path, O_RDWR);
    if(dfd == -1)
        return -1;

    struct super_block sb;
    if(read_superblock(dfd, &sb) == -1)
        return -1;

    unsigned int zmap_size = sb.s_zones;

    int offset = (START_BLOCK+sb.s_imap_blocks) * sb.s_block_size;
    if(lseek(dfd, offset, SEEK_SET) != offset){
        perror("lseek inode");
        return -1;
    }

    char byte = 0;
    for(int i = 0; i < zmap_size; i++) {
        if (i % 8 == 0) {
            if(read(dfd, &byte, 1) != 1) {
                perror("read byte");
                return -1;
            }
            //printf("byte:%hhu\n", byte);
        }
        if (byte & ((char)1 << (i % 8))) {
            //printf("%d\n", i);
            add_int(&(zmap->head), 1, i);
        } else {
            add_int(&(zmap->head), 0, i);
        }
    }


    close(dfd);
    return zmap_size;
}
