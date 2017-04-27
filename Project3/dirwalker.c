
#include "dirwalker.h"

//static struct super_block sb;

int get_blocks(int tab[V2_NR_TZONES], dev_t dev_id, ino_t inode_id){
	int dfd = get_device_file(dev_id);
	if(dfd == -1)
		return -1;
	struct super_block sb;
	if(read_superblock(dfd, &sb) == -1)
		return -1;
	int offset = (START_BLOCK + sb.s_imap_blocks + sb.s_zmap_blocks) * sb.s_block_size + (inode_id-1)*V2_INODE_SIZE;
	if(lseek(dfd, offset, SEEK_SET) != offset){
		perror("lseek inode");
		return -1;
	}
	struct inode i;
	if(read(dfd, &i, V2_INODE_SIZE) != V2_INODE_SIZE){
		perror("error read inode");
		return -1;
	}
	for(int d = 0; d < V2_NR_TZONES; d++){
		tab[d] = i.i_zone[d];
	}
	close(dfd);
	return 0;	
}


int view_directory(const char *path, int recursive)
{
    struct dirent *direntp = NULL;
    DIR *dirp = NULL;
    size_t path_len;
    int tab[V2_NR_TZONES];

    if (!path)
        return -1;
    path_len = strlen(path);    

    if (!path || !path_len || (path_len > _POSIX_PATH_MAX))
        return -1;

    dirp = opendir(path);
    if (dirp == NULL)
        return -1;

    while ((direntp = readdir(dirp)) != NULL)
    {
        /* For every directory entry... */
        struct stat fstat;
        char full_name[_POSIX_PATH_MAX + 1];

        /* Calculate full name, check we are in file length limts */
        if ((path_len + strlen(direntp->d_name) + 1) > _POSIX_PATH_MAX)
            continue;

        strcpy(full_name, path);
        if (full_name[path_len - 1] != '/')
            strcat(full_name, "/");
        strcat(full_name, direntp->d_name);

        /* Ignore special directories. */
        if ((strcmp(direntp->d_name, ".") == 0) ||
            (strcmp(direntp->d_name, "..") == 0))
            continue;

        /* print */
        if (stat(full_name, &fstat) < 0)
            continue;

        mode_t m = fstat.st_mode;
        /*if (fstat.st_dev == imap->device){
            add_int(&(imap->head), fstat.st_ino);
        }*/

        if (S_ISDIR(m)){
            printf("%s -- (%llu:%llu) -- dir -- ", full_name, fstat.st_dev, fstat.st_ino);
        }
        else if (S_ISREG(m)) {
            printf("%s -- (%llu:%llu) -- file -- ", full_name, fstat.st_dev, fstat.st_ino);           
        }
        else if (S_ISCHR(m)) {
            printf("%s -- (%llu:%llu) -- char -- ", full_name, fstat.st_dev, fstat.st_ino);
        }
        else if (S_ISBLK(m)) {
            printf("%s -- (%llu:%llu) -- block -- ", full_name, fstat.st_dev, fstat.st_ino);
        }
        else if (S_ISFIFO(m)) {
            printf("%s -- (%llu:%llu) -- pipe -- ", full_name, fstat.st_dev, fstat.st_ino);
        }
        else if (S_ISLNK(m)) {
            printf("%s -- (%llu:%llu) -- link -- ", full_name, fstat.st_dev, fstat.st_ino);
        }
        else if (S_ISSOCK(m)) {
            printf("%s -- (%llu:%llu) -- socket -- ", full_name, fstat.st_dev, fstat.st_ino);
        }

        if(get_blocks(tab, fstat.st_dev, fstat.st_ino) == -1){
        	printf("get block not working\n");
        	continue;
        }
        for(int d = 0; d < V2_NR_TZONES; d++){
        	printf("%d ", tab[d]);
        }
        printf("\n");
        if (S_ISDIR(m) && recursive)
            view_directory(full_name, 1);
    }

    /* Finalize resources. */
    closedir(dirp);
    return 0;
}

int directoryWalker(int r){
	char path[50];
	bzero(path,50);
	printf("Enter the path you want to open: \n");
	scanf(" %[^\n]%*c", path);
	view_directory(path, r);
	return 0;
}
