#include "utilities.h"

void add_int(int_elmt **list, int data, int index) {
	int_elmt *elmt = malloc(sizeof(int_elmt));
	elmt->data = data;
	elmt->index = index;
	elmt->next = *list;
	(*list) = elmt;
}

void add_int_at(int_elmt **list, int data, int index) {
	int_elmt *elmt = malloc(sizeof(int_elmt));
	elmt->data = data;
	elmt->index = index;

	int_elmt *it = *list;
	int_elmt *it_prev = *list;
	printf("In add_int_at\n");
	while(it != NULL && it->index < index) {
	//	printf("In add_int_at loop\n");
		it_prev = it;
		it = it->next;
	}
	if ((*list) != NULL){
		elmt->next = it;
		it_prev->next = elmt;
	} else {
		(*list) = elmt;
	}
}

void replace(int_elmt **list, int data, int index) {
	int_elmt *it = *list;
	while(it != NULL && it->index != index) {
		it = it->next;
	}
	if (*list != NULL) {
		it->data = data;
	} else {
		add_int(list, data, index);
	}
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

void reverse_list(int_elmt ** list) {
	int_elmt *it = *list;
	int_elmt *tmp_prev = NULL;
	int_elmt *tmp_next = NULL;
	while (it != NULL) {
		tmp_next = it->next;
		it->next = tmp_prev;
		tmp_prev = it;
		it = tmp_next;
	}
	*list = tmp_prev;
}

void print_list(int_elmt **list) {
	int_elmt *it = *list;
	while (it != NULL) {
		printf("%d", it->data);
		it = it->next;
	}
	it = NULL;
}

void print_indexes(int_elmt **list) {
	int_elmt *it = *list;
	reverse_list(&it);
	while (it != NULL) {
		printf("%d", it->index);
		it = it->next;
	}
	it = NULL;
}

void print_indexes_n(int_elmt **list, int n) {
	int_elmt *it = *list;
	//reverse_list(&it);
	int i = 0;
	while (it != NULL && i < n) {
		printf("%d\n", it->index);
		it = it->next;
		i++;
	}
	it = NULL;
}

//TODO
int get_indirect_zone(int tab[]) {
	return 0;
}

int get_zmap_from_inodes(char path[], int_list *zmap) {
	int dfd = open(path, O_RDWR);
    if(dfd == -1)
        return -1;
    
	struct super_block sb;
	if(read_superblock(dfd, &sb) == -1)
		return -1;

	int scale = (1 << sb.s_log_zone_size);
	int n_ilist = ((sb.s_ninodes+V2_INODES_PER_BLOCK(sb.s_block_size)-1) / V2_INODES_PER_BLOCK(sb.s_block_size));
	int blk_ilist = START_BLOCK + sb.s_imap_blocks + sb.s_zmap_blocks;
	sb.s_firstdatazone = (blk_ilist + n_ilist + scale - 1) >> sb.s_log_zone_size;

	int offset = (START_BLOCK + sb.s_imap_blocks + sb.s_zmap_blocks) * sb.s_block_size;
	if(lseek(dfd, offset, SEEK_SET) != offset){
		perror("lseek inode");
		return -1;
	}

	struct inode i;

	for (int j = 0; j<sb.s_zones; j++) {
		add_int(&(zmap->head), 0, j);
	}
	replace(&(zmap->head), 1, 0);

	for (int k = 0; k < sb.s_ninodes-1; k++){
		if(read(dfd, &i, V2_INODE_SIZE) != V2_INODE_SIZE){
			perror("error read inode");
			return -1;
		}
		//printf("In first for\n");

		if (i.i_mode != I_NOT_ALLOC) {
			for(int d = 0; d < V2_NR_TZONES; d++){
				if (d < V2_NR_DZONES){	
					if (i.i_zone[d] != 0){
						//printf("In inode %d, zone %d\n", k, (i.i_zone[d] << sb.s_log_zone_size)-sb.s_firstdatazone+1);
						replace(&(zmap->head), 1, (i.i_zone[d] << sb.s_log_zone_size)-sb.s_firstdatazone+1);
					} else {
						//add_int_at(&(zmap->head), 0, k*V2_INODE_SIZE+d);
					}
				}
				else if (d-V2_NR_DZONES == 1) {
					int tab[10];
					get_indirect_zone(tab);
				}
			}
		}
		//printf("getting imap %hu\n", i.i_nlinks);
	}
	close(dfd);
	return 0;
}

int get_imap_from_inodes(char path[], int_list *imap) {
	int dfd = open(path, O_RDWR);
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
	//printf("1");
	add_int(&(imap->head), 1, 0);
	for (int k = 0; k < sb.s_ninodes-1; k++){
		if(read(dfd, &i, V2_INODE_SIZE) != V2_INODE_SIZE){
			perror("error read inode");
			return -1;
		}
		if (i.i_mode != I_NOT_ALLOC) {
			add_int(&(imap->head), 1, k+1);
			//printf("1");
			//printf("adding inode number %d with mode %hu\n", k, i.i_mode);
		}
		else {
			add_int(&(imap->head), 0, k+1);
			//printf("0");
			//printf("skipping inode number %d with mode %hu\n", k, i.i_mode );
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

