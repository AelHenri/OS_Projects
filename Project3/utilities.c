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

void print_list(int_elmt **list) {
	int_elmt *it = *list;
	while (it != NULL) {
		printf("%d\n", it->data);
		it = it->next;
	}
	it = NULL;
}

int get_imap_from_inodes(int_list *imap, dev_t dev_id) {
	int dfd = get_device_file(dev_id);
	if(dfd == -1)
		return -1;
	struct super_block sb;
	if(read_superblock(dfd, &sb) == -1)
		return -1;
	int offset = (START_BLOCK + sb.s_imap_blocks + sb.s_zmap_blocks) * sb.s_block_size;
	if(lseek(dfd, offset, SEEK_SET) != offset){
		perror("lseek inode");
		return -1;
	}

	struct inode i;
	for (int k = 0; k < sb.s_ninodes; k++){
		if(read(dfd, &i, sizeof(i)) != sizeof(i)){
			perror("error read inode");
			return -1;
		}
		if (i.i_nlinks > 0) {
			add_int(&(imap->head), k);
			printf("adding inode number %d whith %hu links\n", k, i.i_nlinks);
		}
		//printf("getting imap %hu\n", i.i_nlinks);
	}
	close(dfd);
	return 0;	
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

int get_device_file(dev_t dev_id){

	char path[] = "/dev/";
    struct dirent *direntp = NULL;
    DIR *dirp = NULL;
    size_t path_len;

    path_len = strlen(path);    

    dirp = opendir(path);
    if (dirp == NULL){
    	perror("opendir /dev");
        return -1;
    }

    while ((direntp = readdir(dirp)) != NULL)
    {
        /* For every directory entry... */
        struct stat fstat;
        char full_name[_POSIX_PATH_MAX + 1];

        /* Ignore special directories. */
        if ((strcmp(direntp->d_name, ".") == 0) ||
            (strcmp(direntp->d_name, "..") == 0))
            continue;

        /* Calculate full name, check we are in file length limts */
        if ((path_len + strlen(direntp->d_name) + 1) > _POSIX_PATH_MAX)
            continue;

        strcpy(full_name, path);
        strcat(full_name, direntp->d_name);

        /* print */
        if (stat(full_name, &fstat) < 0)
            continue;

		if (S_ISBLK(fstat.st_mode) && fstat.st_rdev == dev_id){
			closedir(dirp);
			return open(full_name, O_RDWR);
        }

    }

    /* Finalize resources. */
    closedir(dirp);
    fprintf(stderr, "Couldnt find device\n");
    return -1;
}