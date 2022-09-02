#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

//struct Program{
//	int minutes;
//	char[41] name;
//};


//struct Program programs[20];

void readfile(char file[]){
	
	char tokens[40][100];
	int i = 0;
	//OPEN FILE
	FILE *info = fopen(file,"r");
	char line [100];
	while(fgets(line,sizeof line, info) !=  NULL){
	//	char command[10][40];
	//	int i = 0;
	//	while(line[i] != '\n' ){
	//		command[0][i] = line[i];
	//		i++;
	//		while(isspace(line[i])){
	//			printf("%d",line[i]);
	//			i++;
	//		}
	//		
	//	}
	//	printf("%s\n",command[0]);
		
		for (char *p = strtok(line," \t\n\0"); p != NULL; p = strtok(NULL, " ")){
  			strcpy(tokens[i] , p);
			printf("token=%s\n", p);
			printf("tokens variable = %s\n",tokens[i]);
			i++;
			printf("------------------------\n");
		}



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

	for(int j = 0; j< 8; j++){
			printf("--test:%s\n",tokens[j]);

		}
	int num = atoi(tokens[1]);
	printf("NUMBER : %d\n", num);
	fclose(info);
		//printf("LINE content is : %s",line); // print file contents
	}
	
	//CLOSE FILE



int main (int argc, char *argv[]){
	readfile(argv[1]);
	return 0;
}

