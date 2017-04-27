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
#include "check_zmap.h"
#include "check_directories.h"

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
			5 check zmaps \n \
			6 check directory \n \
			7 damage bitmaps (1) \n \
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
				print_list(&(imap->head));		
				break;
			case 3:
				printf("\nzone bitmap is:");
				read_zmap(path, imap);
				print_list(&(imap->head));				
				break;
			case 4:
				printf("Checking imaps...\n");
				check_imaps(path);
				break;
			case 5:
				printf("Checking zmaps...\n");
				check_zmaps(path);
				break;
			case 6:
				printf("Check directory...\n");
				char path[50];
				bzero(path,50);
				printf("Enter the directory you want to check: \n");
				scanf(" %[^\n]%*c", path);
				view_directory_special_files(path, imap);
				break;
			case 7:
				printf("Damaging maps, choose 5 bits to change to 1:\n");
				int bit1, bit2, bit3, bit4, bit5;
				scanf("%d", &bit1);
				scanf("%d", &bit2);
				scanf("%d", &bit3);
				scanf("%d", &bit4);
				scanf("%d", &bit5);
				repair_bit_imap(path, bit1, 1); 
				repair_bit_zmap(path, bit1, 1);
				repair_bit_imap(path, bit2, 1); 
				repair_bit_zmap(path, bit2, 1);
				repair_bit_imap(path, bit3, 1); 
				repair_bit_zmap(path, bit3, 1);
				repair_bit_imap(path, bit4, 1); 
				repair_bit_zmap(path, bit4, 1);
				repair_bit_imap(path, bit5, 1); 
				repair_bit_zmap(path, bit5, 1); 
				break;
			case 0:
				exit(0);
				break;
			default:
				exit(0);
				break;
			empty_list(&(imap->head));
		}
		input = -1;
	}while(input !=0);
}
