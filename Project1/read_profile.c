#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>
#include <unistd.h>

#include "read_profile.h"

void change_home_directory(){
	int ret;
	if (HOME != NULL){
		ret = chdir (HOME);
		if(ret == 0){
			printf("HOME directory changed to %s \n", HOME);
		}else{
			printf("Error while setting HOME directory to %s \n", HOME);
		}
	}else{
		printf("NULL HOME directory\n");
	}
}

int start_with(const char* line, char *name, int *position){
	const char *temp_line = line;
	int i=0;
	while((*temp_line != '\n') && *temp_line == ' '){
		printf("temp_line av ++ %s\n", temp_line);
		temp_line++;
		printf("temp_line ap ++ %s\n", temp_line);
		i++;
	}
	int j=0;
        while(temp_line[j] == name[j] && temp_line[j] != '\0' && name[j] != '\0'){
		j++;
	}
	if(name[j] == '\0'){
		*position = i + j - strlen(name);
		return 1;
	}
	*position = 0;
	return 0;
}

void path_value(char *str){
	PATH = strdup(str);
}

void home_value(char *str){
	HOME = strdup(str);
}


int fill_variables(char* line){
   char value[1024];
   int position;
   if(line[0] == '#'){
	printf("Comment line ignored\n");
	return 0;
   }
   printf("%s\n", line);
   if(start_with(line, "export", &position)){
	int i;
	position = position + strlen("export");
	while(line != '\0' && line[position] == ' ')
		position++;
	char * copy_line = line;
	for(i = 0; copy_line[i + position] != '\0'; i++)
		copy_line[i] = copy_line[i+position]; 
	line[i] = '\0';
   }
   position=0;
   if(start_with(line, "PATH", &position)){
	int i;
	position = position + strlen("PATH");
	if(line[position] == '='){
		position++;
		for(i = 0; line[i + position] != '\0'; i++)
			value[i] = line[i+position]; 	
		value[i] = '\0';
   		printf("Name=%s Value=%s","PATH", value);
		path_value(value);
	}
   }
   position=0;
   if(start_with(line, "HOME", &position)){
	int i;
	position = position + strlen("HOME");
	if(line[position] == '='){
		position++;
		for(i = 0; line[i + position] != '\0'; i++)
			value[i] = line[i+position]; 	
		value[i] = '\0';
   		printf("Name=%s Value=%s","HOME", value);

		home_value(value);
		//change_home_directory();
	}
   }
}

int read_file(char *filename){
	FILE *fd;
	char buffer[4096];
	if((fd=fopen(filename, "r"))==NULL){
    		perror("File can't be opened");
		return -1;
	}
	int i = 0;
	while(fgets(buffer, sizeof(buffer), fd) != NULL){
	    printf("Line %d:", i++);
	    fill_variables(buffer);	    
       	}
    fclose(fd);
    return 0;
}

int read_profile(){
	char* profil = PROFILE;
	if(read_file(profil) == -1){
		printf("Error while reading file:\n  %s\n", profil);
		return -1;
	}
	return 0;
}

/*
int main(){
	char* file_name = ".profile";
	if(-1 == read_file(file_name)){
		printf("Error reading file: %s\n", file_name);
		return 1;
	}
	return 0;
}
*/
