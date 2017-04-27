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
#include "mfs/const.h"
#include "mfs/inode.h"
#include "mfs/type.h"
#include "mfs/mfsdir.h"
#include "mfs/super.h"
#include "utilities.h"


int get_blocks(int tab[V2_NR_TZONES], dev_t dev_id, ino_t inode_id);
int view_directory(const char *path, int recursive);
int directoryWalker(int r);
