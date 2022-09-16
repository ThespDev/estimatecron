//  CITS2002 Project 1 2022
//  Student1:   23137892   NAYDENOV   PABLO
//  Student2:   22332371   BRYDON   RYAN

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 100
#define MAX_COMMAND_LENGTH 40
#define MAX_COMMAND_COUNT 20

struct Data {
  char file_info[MAX_COMMAND_COUNT][MAX_LINE_LENGTH];
  int linecount;
};
// * is represented by -1 in the struct for the time values
struct ScheduledTask {
  char programName[MAX_COMMAND_LENGTH + 1];
  int minute;
  int hour;
  int day;
  int month;
  int dayOfWeek;
};

struct Estimate {
  char programName[MAX_COMMAND_LENGTH + 1];
  int minutes;
};

struct Estimate estimates[MAX_COMMAND_COUNT];
struct ScheduledTask tasks[MAX_COMMAND_COUNT];

// Handling text to int conversion for ease of use later
int monthConverter(char month[]) {
  if (strcmp(month, "jan") == 0) {
    return 0;
  } else if (strcmp(month, "feb") == 0) {
    return 1;
  } else if (strcmp(month, "mar") == 0) {
    return 2;
  } else if (strcmp(month, "apr") == 0) {
    return 3;
  } else if (strcmp(month, "may") == 0) {
    return 4;
  } else if (strcmp(month, "jun") == 0) {
    return 5;
  } else if (strcmp(month, "jul") == 0) {
    return 6;
  } else if (strcmp(month, "aug") == 0) {
    return 7;
  } else if (strcmp(month, "sep") == 0) {
    return 8;
  } else if (strcmp(month, "oct") == 0) {
    return 9;
  } else if (strcmp(month, "nov") == 0) {
    return 10;
  } else if (strcmp(month, "dec") == 0) {
    return 11;
  } else if (*month == '*') {
    return -1;
  }
  // Checking that the cotains no non-digits so that it can
  // be compared between 0 and 12
  for (int j = 0; j < strlen(month); j++) {
    if (!isdigit(month[j])) {
      fprintf(stderr, "%s is not a valid month\n", month);
      exit(EXIT_FAILURE);
    }
  }

  if (atoi(month) >= 0 && atoi(month) < 12) {
    return atoi(month);
  }

  else {
    fprintf(stderr, "%s is not a valid month\n", month);
    exit(EXIT_FAILURE);
  }
}
// Handling text to int conversion for ease of use later
int dayConverter(char day[]) {
  if (strcmp(day, "sun") == 0) {
    return 0;
  } else if (strcmp(day, "mon") == 0) {
    return 1;
  } else if (strcmp(day, "tue") == 0) {
    return 2;
  } else if (strcmp(day, "wed") == 0) {
    return 3;
  } else if (strcmp(day, "thu") == 0) {
    return 4;
  } else if (strcmp(day, "fri") == 0) {
    return 5;
  } else if (strcmp(day, "sat") == 0) {
    return 6;
  } else if (*day == '*') {
    return -1;
  }
  // Checking that the cotains no non-digits so that it can
  // be compared between 0 and 7
  for (int j = 0; j < strlen(day); j++) {
    if (!isdigit(day[j])) {
      fprintf(stderr, "%s is not a valid day of the week\n", day);
      exit(EXIT_FAILURE);
    }
  }
  if (atoi(day) >= 0 && atoi(day) < 7) {
    return atoi(day);
  }

  else {
    fprintf(stderr, "%s is not a valid day of the week\n", day);
    exit(EXIT_FAILURE);
  }
}

// RETURNS THE AMOUNT OF DAYS IN A MONTH BASED OFF INTEGER GIVEN (0-11)
int daysInMonth(int month) {
  if (month < 0 || month > 11) {
    fprintf(stderr, "%i is not a valid month\n", month);
  }
  int daysOfMonths[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  return daysOfMonths[month];
}

// PARSES EXACT ARGUMENTS AND STORES INTO GLOBAL STRUCT
// ARRAY OF TASKS OR ESTIMATES
void parseData(struct Data filedata, int fileNum) {
  switch (fileNum) {
  // ESTIMATE PARSING
  case 1:
    for (int i = 0; i < filedata.linecount; i++) {
      char *word = strtok(filedata.file_info[i], " \t\n\0");
      strcpy(estimates[i].programName, word);
      word = strtok(NULL, " \t\n\0");
      // Checking for valid number of minutes before storing in struct
      for (int j = 0; j < strlen(word); j++) {
        if (!isdigit(word[j])) {
          fprintf(stderr, "%s is not a valid amount of minutes\n", word);
          exit(EXIT_FAILURE);
        }
      }
      estimates[i].minutes = atoi(word);
    }

    break;

  // SCHEDULE PARSING
  case 2:
    for (int i = 0; i < filedata.linecount; i++) {
      // MINUTES (0-59)
      char *word = strtok(filedata.file_info[i], " \t\n\0");
      if (*word == '*') {
        tasks[i].minute = -1;
      }

      else {
        // Checking validty of minutes before storing
        for (int j = 0; j < strlen(word); j++) {
          if (!isdigit(word[j])) {
            fprintf(stderr, "%s is not a valid amount of minutes\n", word);
            exit(EXIT_FAILURE);
          }
        }

        if (atoi(word) < 0 || atoi(word) > 59) {
          fprintf(stderr, "%s is not a valid minute\n", word);
          exit(EXIT_FAILURE);
        }
        tasks[i].minute = atoi(word);
      }
      // HOURS (0-23)

      word = strtok(NULL, " \t\n\0");
      if (*word == '*') {
        tasks[i].hour = -1;
      } else {
        // Checking validty of hours before storing
        for (int j = 0; j < strlen(word); j++) {
          if (!isdigit(word[j])) {
            fprintf(stderr, "%s is not a valid amount of minutes\n", word);
            exit(EXIT_FAILURE);
          }
        }

        if (atoi(word) < 0 || atoi(word) > 23) {
          fprintf(stderr, "%s is not a valid hour\n", word);
          exit(EXIT_FAILURE);
        }
        tasks[i].hour = atoi(word);
      }
      // DAY OF MONTH (1-31)
      word = strtok(NULL, " \t\n\0");
      int days;
      // Checking basic validty of days before storing in var
      // actual date to month validity checked after month is tokenised
      if (*word == '*') {
        days = -1;
      } else {
        for (int j = 0; j < strlen(word); j++) {
          if (!isdigit(word[j])) {
            fprintf(stderr, "%s is not a valid day of the month\n", word);
            exit(EXIT_FAILURE);
          }
        }

        days = atoi(word);
      }
      // MONTH (0-11 OR jan,feb....)

      word = strtok(NULL, " \t\n\0");
      int month = monthConverter(word);
      // Logic for day-month */! combinations:
      //  *-!* :  no need to check: days unknown
      //  !*-!* : Check if days is valid in month
      //  *-* : No need to check, month unknown
      //  !*-* : No need to check, month unknown

      if (month == -1 && days != -1) {
        tasks[i].month = month;
        if (days <= 31 && days >= 0) {
          tasks[i].day = days;
        } else {
          fprintf(stderr,
                  "%d is not a valid number of days for the given month\n",
                  days);
          exit(EXIT_FAILURE);
        }

      } else if (month != -1 && days != -1) {
        int numberOfDays = daysInMonth(month);
        tasks[i].month = month;
        if (days <= numberOfDays && days >= 0) {
          tasks[i].day = days;
        } else {
          fprintf(stderr,
                  "%d is not a valid number of days for the given month\n",
                  days);
          exit(EXIT_FAILURE);
        }

      } else if (days == -1 && month == -1) {
        tasks[i].month = month;
        tasks[i].day = days;
      }

      word = strtok(NULL, " \t\n\0");
      int dayOfWeek = dayConverter(word);
      tasks[i].dayOfWeek = dayOfWeek;

      word = strtok(NULL, " \t\n\0");
      strcpy(tasks[i].programName, word);
    }
    break;
  }
}

// OPEN AND READ THE crontab-file AND estimates-file
struct Data readfile(char file_name[]) {

  // STORE THE LINES FROM THE FILE
  struct Data data;
  // OPEN THE FILE
  FILE *file_data = fopen(file_name, "r");

  /*PRINT ERROR IF UNABLE TO OPEN FILE
   CHECK FOR DATA ERRORS IN BOTH FILES - IF ANY ERRORS ONLY THE FIRST SHOULD BE
   REPORTED AND THEN THE PROGRAM SHOULD TERMINATE */
  if (file_data == NULL) {
    printf("Unable to open the file %s\n", file_name);
    exit(EXIT_FAILURE);
  }

  int line_number = 0;

  // CHECK FOR END OF FILE (EOF) OR ANY ERROR WHILE READING
  char line[MAX_LINE_LENGTH];
  while (fgets(line, sizeof line, file_data) != NULL) {
    int charCounter = 0;
    // Iterating through line to find first non whitespace character
    //  and check if it's a #
    while (isspace(line[charCounter])) {
      charCounter++;
    }
    // CHECKING FIRST NON WHITESPACE FOR COMMENT LINE
    if (line[charCounter] == '#') {
      continue;
    }
    strcpy(data.file_info[line_number], line);
    line_number++;
  }
  // Line numbers used for looping variables in the parsing
  data.linecount = line_number;
  // CLOSE FILE
  fclose(file_data);
  return data;
}

int getyear() {
  time_t currenttime = time(NULL);
  struct tm tm = *localtime(&currenttime);
  return tm.tm_year;
}

int first_day_of_month(int month) {

  struct tm tm;
  //  SET ALL FIELDS OF tm TO ZERO TO MAKE SOME FIELDS 'UNKNOWN'
  memset(&tm, 0, sizeof(tm));

  //  INITIALIZE THE FILEDS THAT WE ALREADY KNOW
  tm.tm_mday = 1;
  tm.tm_mon = month; // 0=Jan, 1=Feb, ....
  tm.tm_year = getyear();
  mktime(&tm);
  //  RETURN THE INTEGER MONTH VALUE
  return tm.tm_wday; // 0=Sun, 1=Mon, .....
}

void simulateMonth(int month, int numTasks, int numEstimates) {
  int currMinute = 0;
  int currHour = 0;
  int currDay = 1;
  int currMonth = month;
  int currDayOfWeek = first_day_of_month(month);
  int minutesinMonth = daysInMonth(month) * 24 * 60;
  int timesRun[numTasks];
  memset(timesRun, 0, sizeof(timesRun));
  int processTimers[20];
  memset(processTimers, 0, sizeof(processTimers));
  int processCounter = 0;
  int currentMax = 0;
  // Looping over each minute in the month
  for (int i = 0; i < minutesinMonth; i++) {
    // CHECK IF COMMAND NEEDS TO BE RUN
    for (int j = 0; j < numTasks; j++) {
      // If every time value matches up to a task by iterating
      //  through the schedule check if there is space in the array
      // processTimers for the process to 'run'
      if ((tasks[j].minute == currMinute || tasks[j].minute == -1) &&
          (tasks[j].hour == currHour || tasks[j].hour == -1) &&
          (tasks[j].day == currDay || tasks[j].day == -1) &&
          (tasks[j].month == currMonth || tasks[j].month == -1) &&
          (tasks[j].dayOfWeek == currDayOfWeek || tasks[j].dayOfWeek == -1)) {
        bool taskFound = false;
        int foundIndex;
        for (int k = 0; k < numEstimates; k++) {
          // Finding the estimate value for the task by iterating over all the
          // estimates
          if (strcmp(estimates[k].programName, tasks[j].programName) == 0) {
            taskFound = true;
            foundIndex = k;
          }
        }
        if (taskFound) {
          bool listFull = false;
          int l = 0;
          while (processTimers[l] != 0) {
            l++;
            if (l > 19) {
              listFull = true;
              break;
            }
          }
          if (!listFull) {
            processTimers[l] = estimates[foundIndex].minutes;
            timesRun[j] += 1;
            processCounter++;
          }
        } else if (!taskFound) {
          fprintf(stderr, "There is no given estimate for the task: %s\n",
                  tasks[j].programName);
          exit(EXIT_FAILURE);
        }
      }
    }
    // Keeping track of the max number of processes
    // Over the month
    if (processCounter > currentMax) {
      currentMax = processCounter;
    }
    currMinute++;
    // After a minute passses, decrement all process timers
    for (int j = 0; j < 20; j++) {
      if (processTimers[j] == 0) {
        continue;
      } else {
        processTimers[j]--;
        // If the process timer is 0 after a decrement
        // That means it is finished
        if (processTimers[j] == 0) {
          processCounter--;
        }
      }
    }
    // Time is evalutated with a series of remainders %
    // To allow for the 0-59,0-23 ect structure of time
    currMinute = currMinute % 60;
    if (currMinute == 0) {
      currHour++;
      currHour = currHour % 24;
      if (currHour == 0) {
        currDay++;
        currDayOfWeek++;
        currDayOfWeek = currDayOfWeek % 7;
      }
    }
  }
  // Finding the task that was run the most
  // As well as summing up the number of tasks run
  int mostRun = 0;
  int mostRunIndex = 0;
  int commandsInvoked = 0;
  for (int i = 0; i < numTasks; i++) {
    commandsInvoked += timesRun[i];
    if (timesRun[i] > mostRun) {
      mostRun = timesRun[i];
      mostRunIndex = i;
    }
  }

  printf("The most frequently executed command was: %s\n The total number of "
         "commands invoked was: %d\n The max number of commands running at a "
         "time was: %d\n",
         tasks[mostRunIndex].programName, commandsInvoked, currentMax);
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("%d", argc);
    fprintf(stderr, "Incorrect number of arguments, usage: ./estimatecron  "
                    "month  crontab-file  estimates-file \n");
    exit(EXIT_FAILURE);
  }
  struct Data crontab = readfile(argv[2]);
  struct Data estimates = readfile(argv[3]);
  parseData(estimates, 1);
  parseData(crontab, 2);
  int convertedMonth = monthConverter(argv[1]);
  simulateMonth(convertedMonth, crontab.linecount, estimates.linecount);
  return 0;
}
