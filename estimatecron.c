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

int first_day_of_month(int month, int year) {
  struct tm tm;

  //  SET ALL FIELDS OF tm TO ZERO TO MAKE SOME FIELDS 'UNKNOWN'
  memset(&tm, 0, sizeof(tm));

  //  INITIALIZE THE FILEDS THAT WE ALREADY KNOW
  tm.tm_mday = 1;
  tm.tm_mon = month - 1; // 0=Jan, 1=Feb, ....
  tm.tm_year = year - 1900;
  mktime(&tm);
  //  RETURN THE INTEGER MONTH VALUE
  return tm.tm_wday; // 0=Sun, 1=Mon, .....
}

void simulateMonth(int month) {
  int minute = 0;
  int hour = 0;
  int day = 1;
  int dayofWeek = first_day_of_month(month, CURRENT_YEAR);
  for (int i = 0; i < 44640; i++) {
    printf("Iteration : %d\n Minute: %d , Hour: %d , Day: %d , DayOfWeek: %d\n",
           i, minute, hour, day, dayofWeek);
    // DO the Simulation of Commands here

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

int main(int argc, char *argv[]) { return 0; }
