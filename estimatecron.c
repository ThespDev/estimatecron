//  CITS2002 Project 1 2022
//  Student1:   23137892   NAYDENOV   PABLO
//  Student2:   22332371   BRYDON   RYAN

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 100
#define MAX_COMMAND_LENGTH 40
#define MAX_COMMAND_COUNT 20

#define CURRENT_YEAR 2022
#define DAYS_PER_WEEK fine 7

/*ERRORS:
THROW ERROR IF TASK IN schedule BUT NOT estimates*/

struct Data{
	char file_info[MAX_COMMAND_COUNT][MAX_LINE_LENGTH];
};
// * == -1
struct ScheduledTask{
	char programName[MAX_COMMAND_LENGTH + 1];
	int minute;
	int hour;
	int day;
	int month;
	int dayofWeek;
};

struct Estimate{
	char programName[MAX_COMMAND_LENGTH +1];
	int minutes;
};

struct Estimate estimates[MAX_COMMAND_COUNT];
struct ScheduledTask tasks[MAX_COMMAND_COUNT];

void parseData(struct Data filedata, int fileNum){
	switch(fileNum){
		//ESTIMATE PARSING
		case 1:
			for(int i = 0; i < 1; i++){
			char *word = strtok(filedata.file_info[i]," \t\n\0");
			strcpy(estimates[i].programName,word);
			word = strtok(NULL," \t\n\0");
			estimates[i].minutes = atoi(word);
			}
			printf("THIS IS STORED IN THE STRUCT: %s\n", estimates[0].programName);
			printf("THIS IS STORED IN THE STRUCT: %d\n", estimates[0].minutes);
			break;
		//SCHEDULE PARSING
		case 2:
			break;
	}
}

// OPEN AND READ THE crontab-file AND estimates-file
struct Data readfile(char file_name[]){

    //STORE THE LINES FROM THE FILE
	struct Data data;
    //OPEN THE FILE
    FILE *file_data = fopen(file_name,"r");

    /*PRINT ERROR IF UNABLE TO OPEN FILE
     CHECK FOR DATA ERRORS IN BOTH FILES - IF ANY ERRORS ONLY THE FIRST SHOULD BE REPORTED AND THEN THE PROGRAM SHOULD TERMINATE */
    if(file_data == NULL){
        printf("Unable to open the file %s\n", file_name);
        exit(EXIT_FAILURE);
    }

    int line_number = 0;

    // CHECK FOR END OF FILE (EOF) OR ANY ERROR WHILE READING
    char line [MAX_LINE_LENGTH];
    while(fgets(line,sizeof line, file_data) !=  NULL){
	    int charCounter = 0;
	    while(isspace(line[charCounter])){
		charCounter++;
	    }
	    //CHECKING FIRST NON WHITESPACE FOR COMMENT LINE
	    if (line[charCounter] == '#'){
		printf("COMMENT LINE DETECTED: %s\n",line);
		continue;
	    }
	    strcpy(data.file_info[line_number],line);
	    line_number++;
	}
    //CLOSE FILE
    fclose(file_data);
    return data;
}

//RETURNS THE AMOUNT OF DAYS IN A MONTH BASED OFF INTEGER GIVEN (0-11)
int daysInMonth(int month) {
  if (month < 0 || month > 11){
	fprintf(stderr,"%i is not a valid month\n",month);
  }
  int daysOfMonths[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  return daysOfMonths[month];
}

int first_day_of_month(int month) {

  struct tm tm;
  //  SET ALL FIELDS OF tm TO ZERO TO MAKE SOME FIELDS 'UNKNOWN'
  memset(&tm, 0, sizeof(tm));

  //  INITIALIZE THE FILEDS THAT WE ALREADY KNOW
  tm.tm_mday = 1;
  tm.tm_mon = month; // 0=Jan, 1=Feb, ....
	tm.tm_year = CURRENT_YEAR-1900;
  mktime(&tm);
  printf("CURRENT YEAR %d\n",tm.tm_year);
  printf("CURRENT MONTH %d\n",tm.tm_mon);

  //  RETURN THE INTEGER MONTH VALUE
  return tm.tm_wday; // 0=Sun, 1=Mon, .....
}

void simulateMonth(int month) {
  int minute = 0;
  int hour = 0;
  int day = 1;
  int dayofWeek = first_day_of_month(month);
  int minutesinMonth = daysInMonth(month) * 24 * 60;
  for (int i = 0; i < minutesinMonth; i++) {
    printf("Iteration : %d\n Minute: %d , Hour: %d , Day: %d , DayOfWeek: %d\n",
           i, minute, hour, day, dayofWeek);
    // DO THE SIMULATION OF COMMANDS HERE

    minute++;
    minute = minute % 60;
    if (minute == 0) {
      hour++;
      hour = hour % 24;
      if (hour == 0) {
        day++;
        dayofWeek++;
        dayofWeek = dayofWeek % 7;
      }
    }
      
  }
}

int main(int argc, char *argv[]) {
  struct Data filedata = readfile(argv[1]);
  printf("LINE 1: %s\n",filedata.file_info[0]);
  parseData(filedata,1);
  return 0;
}
