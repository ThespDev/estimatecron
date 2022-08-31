#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct Program{
	int minutes;
	char[41] name;
}


struct Program programs[20];

void readfile(char file[]){
	//OPEN FILE
	FILE *info = fopen(file,"r");
	// CHECKING FOR EOF OR ERROR
	char line [100];
	while(fgets(line,sizeof line, info) !=  NULL){
		char command[10][40];
		int i = 0;
		while(line[i] != '\n' ){
			command[0][i] = line[i];
			i++;
			while(isspace(line[i])){
				printf("%d",line[i]);
				i++;
			}
			
		}
		printf("%s\n",command[0]);
		
	//	int i = 0;
	//	char * token = strtok(line, " \t");
	//	char command[100][40];
	//	strcpy(command[0],token);
//		printf("THIS IS THE COMMAND: %s\n",command[0]);
//		while(token != NULL){
//			token = strtok(NULL, " \t");
//			printf("this is the token %s\n",token);
			//strcpy(command[1],token);
		}

	
		//printf("this is the command name: %s\n",command);

	
	fclose(info);
		//printf("LINE content is : %s",line); // print file contents
	}
	
	//CLOSE FILE



int main (int argc, char *argv[]){
	readfile(argv[1]);
	return 0;
}

