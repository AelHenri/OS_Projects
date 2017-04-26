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

#include "dirwalker.h"
#include "zmapwalker.h"
#include "imapwalker.h"
#include "check_imap.h"

/*
int main(){
	int input=0;

    printf("\nFS TOOLS\n");
	do{
		printf("\nPlease enter \n \
			1 directory walker\n \
			0 exit\n");
		printf(">");
		scanf("%d",&input);
		switch(input){

			case 1:{
			printf("\nPlease enter \n \
			1 recursion\n \
			0 no recursion\n");
			scanf("%d",&input);
			directoryWalker(input);
			}
			break;
			case 0:
			exit(0);
			break;
			default:
			break;
		}
	}while(input !=0);
}
*/
int main(){
	int input=0;
	int dirinput=0;
    char path[] = "/dev/c0d0p0s1";
    int_list *imap = malloc(sizeof(imap));
    imap->device = ROOT_ID;
    imap->head = NULL;
    printf("\nFS TOOLS\n");
	do{
		printf("\nPlease enter \n \
			1 directory walker\n \
			2 inode bitmap walker \n \
			3 zone bitmap walker \n \
			4 check imaps \n \
			0 exit\n");
		printf(">");
		scanf("%d",&input);
		switch(input){

			case 1:
				printf("\nPlease enter \n \
					1 recursion\n \
					0 no recursion\n");
				scanf("%d",&dirinput);
				directoryWalker(dirinput, imap);
				break;
			case 2:
				printf("\ninode bitmap is:");
				read_imap(path, imap);			
				break;
			case 3:
				printf("\nzone bitmap is:");
				read_zmap(path);				
				break;
			case 4:
				printf("Checking imaps...\n");
				check_imaps(path);
			case 0:
				exit(0);
				break;
			default:
				break;
			empty_list(&(imap->head));
		}
	}while(input !=0);
}
