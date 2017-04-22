#include <sys/cdefs.h>
#include <lib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <strings.h>





void view_directory(const char *path){
	DIR *directory_name;
	struct dirent *start;

	if (!(directory_name = opendir(path)))
		return;
	while ((start = readdir(directory_name))) {
		if(strcmp(start->d_name,".")== 0 || strcmp(start->d_name,"..") == 0)
			continue;
		printf("%s ----Inode number %llu \n",start->d_name,start->d_ino);
	}
	closedir(directory_name);
}

int directoryWalker(){
	char path[50];
	bzero(path,50);
	printf("Enter the path you want to open: \n");
	scanf(" %[^\n]%*c", path);
	view_directory(path);
	return 0;
}

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

			case 1:
			directoryWalker();
			break;
			case 0:
			exit(0);
			break;
			default:
			break;
		}
	}while(input !=0);
}
