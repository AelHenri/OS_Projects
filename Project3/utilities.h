#ifndef UTILITIES_H
#define UTILITIES_H

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
#include <minix/const.h>

#define ROOT "/dev/c0d0p0s0"
#define USR "/dev/c0d0p0s2"
#define HOME "/dev/c0d0p0s1"

#define ROOT_ID 896
#define HOME_ID 897
#define USR_ID 898

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
void print_list(int_elmt **list);

int get_imap_from_inodes(char path[], int_list *imap);
int read_superblock(int dfd, struct super_block *sb);
int get_device_file(dev_t dev_id);

#endif