#include <sys/cdefs.h>
#include <fcntl.h>
#include <lib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <strings.h>
#include <sys/types.h>
#include "mfs/const.h"
#include "mfs/inode.h"
#include "mfs/type.h"
#include "mfs/mfsdir.h"
#include "mfs/super.h"

//static struct super_block sb;


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

int read_imap(char path[]) {
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
        }
    }

    close(dfd);
    return imap_size;
}

int main(){
    char path[] = "/dev/c0d0p0s0";
    int ret = read_imap(path);
    return 0;
}
