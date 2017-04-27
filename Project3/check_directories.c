#include "check_directories.h"


ino_t check_special_directories(char path[]) {
    printf("INSIDE CHECK SPECIAL DIRECTORIES(%s)\n", path);
    struct stat fstat;
    int p_flag = -1;
    ino_t pp_flag = -1;
    struct dirent *dp;
    size_t path_len;
    if(stat(path, &fstat) < 0){
        return -1;
    }
    ino_t current_inode = fstat.st_ino;
    DIR *dirp = opendir(path);
    while ((dp = readdir(dirp)) != NULL) {

        if(strcmp(dp-> d_name, ".") == 0 && (ino_t)dp-> d_ino == current_inode){
            printf("courant %s %llu\n", dp-> d_name, (ino_t)dp-> d_ino );
            p_flag = 1;
        } 
        else if(strcmp(dp-> d_name, "..") == 0){
            printf("pere %s %llu\n", dp-> d_name, (ino_t)dp-> d_ino );
            pp_flag = (ino_t)dp-> d_ino ;
        }
    }
    if(pp_flag != -1 && p_flag == 1){
        return pp_flag;
    }
    closedir(dirp);
    return 0;
}


int view_directory_special_files(char path[], int_list *imap)
{   
    ino_t current_inode = -1;
    ino_t s_inode = -1;
    struct dirent *direntp = NULL;
    DIR *dirp = NULL;
    size_t path_len;
    int tab[V2_NR_TZONES];
    struct stat fstat;

    if (!path){
        printf("!path\n");
        return -1;
    }
    path_len = strlen(path);    

    if (!path || !path_len || (path_len > _POSIX_PATH_MAX)){
        printf("length\n");
        return -1;
    }

    if(stat(path, &fstat) < 0){
        return -1;
    }
    //ino_t current_inode = fstat.st_ino;
    current_inode = check_special_directories(path);
    printf("the path is %s and  inode %llu \n", path, current_inode );
    dirp = opendir(path);
    if (dirp == NULL){
        return -1;
    }

    while ((direntp = readdir(dirp)) != NULL)
    {
        /* For every directory entry... */
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
        //printf("Full name is :  %s\n", full_name);
        if (S_ISDIR(m)){
            s_inode = check_special_directories(full_name);
            printf("Full name is :  %s, inode %llu \n", full_name, s_inode);
            //s_inode = check_special_directories(full_name);
            if (s_inode == current_inode ){
                printf("addin directory, full_name: %s\n", full_name);
                add_int(&(imap->head), fstat.st_ino, 0);
            }
        }/*
        else if (S_ISREG(m)) {
            printf("%s  -- file -- ", full_name);           
        }
        else if (S_ISCHR(m)) {
            printf("%s -- char -- ", full_name);
        }
        else if (S_ISBLK(m)) {
            printf("%s -- block -- ", full_name);
        }
        else if (S_ISFIFO(m)) {
            printf("%s  -- pipe -- ", full_name);
        }
        else if (S_ISLNK(m)) {
            printf("%s -- link -- ", full_name);
        }
        else if (S_ISSOCK(m)) {
            printf("%s -- socket -- ", full_name);
        }*/
        if(get_blocks(tab, fstat.st_dev, fstat.st_ino) == -1){
            printf("get block not working\n");
            continue;
        }
        printf("\n");
/*        if (S_ISDIR(m) && recursive)
            view_directory(full_name, 1, imap);*/
    }

    /* Finalize resources. */
    closedir(dirp);
    return 0;
}
