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

int read_superblock(int dfd, struct super_block *sb);