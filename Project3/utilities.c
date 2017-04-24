#include "utilities.h"

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