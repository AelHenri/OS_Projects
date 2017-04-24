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

typedef struct Int_elmt{
	int data;
	struct Int_elmt *next;
}int_elmt;

typedef struct Int_list{
	int device;
	int_elmt *head;
}int_list;

void add_int(int_elmt **list, int data);
int pop_int(int_elmt **list);
void empty_list(int_elmt **list);

int read_superblock(int dfd, struct super_block *sb);