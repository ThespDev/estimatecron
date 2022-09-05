//  CITS2002 Project 1 2022
//  Student1:   23137892   NAYDENOV   PABLO
//  Student2:   22332371   BRYDON   RYAN

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/*
 crontab-file
 minute - int (0 to 59)
 hour - int (0 to 24)
 day - int (0 to 31) this is dependent on the day obviously
 month - int (0 to 12)
 day_name - string(Sun, Mon, Tues etc)
 command - string
 
 estimates- file
 minutes - int
 command - string
 

 * Open and read crontab-file and estimates-file
 
 * Each contain at most 20 Non-comment lines and each line will be at most 100 characters long and each command name will be atleast 40 charaters long

 * Check for data errors in both files - if any errors only the first should be reported and then the program should terminate
 
 * Every command name appearing in the crontab-file will also appear in the estimates-file
 
 * Skip all "comment" lines that begin with a - #
 
 * The project should simuate the execution of the commands in the crontab-file for the month specified onn the command-line. (No consideration for leap-year or leap seconds needed)
 
 * At most 20 processes will ever be executing at the same time (during the same minute) and mutilple instances of the same command may run at the same time
 
 * The program only needs to simulate the execution pf processes for the requested month and current year and all processes terminated before the end of the requested month

 * Given the month we need to determine - commands that run in that month nd count how many times each command runs
 
*/

// struct Program{
//	int minutes;
//	char[41] name;
// };


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

