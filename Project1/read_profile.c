#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>
#include <unistd.h>


#define PROFILE "/.profile"
#define HOME_ENV_NAME "HOME"
#define PATH_ENV_NAME "PATH"

char *PATH = NULL;
char *HOME = NULL;

void path_value(char *str){
	PATH = strdup(str);
}

void home_value(char *str){
	HOME = strdup(str);
}

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


int fill_variables(char* line){
   char value[1024];
   int position;
   if(line[0] == '#')
   {
#if DEBUG
	printf("Comment line ignored\n");
#endif
	return 0;
   }
#if DEBUG
   printf("%s\n", line);
#endif
   if(start_with(line, "export", &position)){
	int i;
	position = position + strlen("export");
	while(line != '\0' && line[position] == ' ')
		position++;
	for(i = 0; line[i + position] != '\0'; i++)
		line[i] = line[i+position]; // ERREUR	
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
		if(value[i-1] == '\n')
			value[i-1] = '\n';
		else
			value[i] = '\n';
#if DEBUG
   		printf("Name=%s Value=%s","PATH", value);
#endif
		path_value(value);
	}
   }
   position=0;
   if(start_with(line, "HOME", &position)){
	int i;
	position = position + strlen("HOME");
	if(line[position] == '=')
	{
		position++;
		for(i = 0; line[i + position] != '\0'; i++)
			value[i] = line[i+position]; 	
		if(value[i-1] == '\n')
			value[i-1] = '\n';
		else
			value[i] = '\n';
#if DEBUG
   		printf("Name=%s Value=%s","HOME", value);
#endif
		home_value(value);
		change_home_directory();
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
#if DEBUG
	    printf("Line %d:", i++);
#endif
	    fill_variables(buffer);	    
       	}
    	fclose(fd);
}

void read_profile_file(){
	char* profil = PROFILE;
	if(read_file(profil) == -1){
#if DEBUG
		printf("Error while reading file:\n  %s\n", profil);
#endif
	}
}


int main(){
	char *line1 = "export HOME=/usr/src";
	int i1 = fill_variables(line1);
	printf(" filla variable %d\n", i1);
/*	
	char *line2 = "export HOME=/usr/src";
	int i2 = fill_variables(line1);
	printf(" filla variable %d\n", i2);
	printf("home = %s \n ", HOME);
	printf("path = %s \n ", PATH);
	char *line3 = "export PATH=/usr/src";
	int i3 = fill_variables(line1);
	printf(" filla variable %d\n", i3);
	printf("home = %s \n ", HOME);
	printf("path = %s \n ", PATH);
	char *line4 = " ";
	int i4 = fill_variables(line1);
	printf(" filla variable %d\n", i4);
	printf("home = %s \n ", HOME);
	printf("path = %s \n ", PATH);
*/
	return 0;
}