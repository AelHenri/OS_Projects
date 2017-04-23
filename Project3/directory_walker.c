#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>

/* Print all the dirs starting from <path> [maybe recursive]. */
int print_dirs(const char *path, int recursive)
{
    struct dirent *direntp = NULL;
    DIR *dirp = NULL;
    size_t path_len;

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
        if (S_ISDIR(m)){
            printf("%s -- (%llu:%llu) -- dir\n", full_name, fstat.st_dev, fstat.st_ino);
            if (recursive)
                print_dirs(full_name, 1);
        }
        else if (S_ISREG(m)) {
            printf("%s -- (%llu:%llu) -- file\n", full_name, fstat.st_dev, fstat.st_ino);           
        }
        else if (S_ISCHR(m)) {
            printf("%s -- (%llu:%llu) -- char\n", full_name, fstat.st_dev, fstat.st_ino);
        }
        else if (S_ISBLK(m)) {
            printf("%s -- (%llu:%llu) -- block\n", full_name, fstat.st_dev, fstat.st_ino);
        }
        else if (S_ISFIFO(m)) {
            printf("%s -- (%llu:%llu) -- pipe\n", full_name, fstat.st_dev, fstat.st_ino);
        }
        else if (S_ISLNK(m)) {
            printf("%s -- (%llu:%llu) -- link\n", full_name, fstat.st_dev, fstat.st_ino);
        }
        else if (S_ISSOCK(m)) {
            printf("%s -- (%llu:%llu) -- socket\n", full_name, fstat.st_dev, fstat.st_ino);
        }
    }

    /* Finalize resources. */
    (void)closedir(dirp);
    return 0;
}

/* We are taking first argument as initial path name. */
int main(int argc, const char* argv[])
{
    if (argc < 2)
        return -1;

    print_dirs(argv[1], 1);
    return 0;
}