#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// gcc p3.c -o p3
// ./p3

bool check(long int calorie, long int time, long int table[], long int total, int func) 
  {
    // func is 0 for add because first time record is appear, 1 for replace because it should exists

    // checks if time provides is in [0, 23] inclusive
    if ((time < 0) || (23 < time)) {
      printf("Error: %li not valid time.\n", time);
      return false;
    }

    // if func is 1, it is replacing so check if record exists
    if (func == 1){
      if (table[time] == -1) {
      printf("Error: Meal does not exist in the record.\n");
      return false;
      }
      total -= table[time];
    }

    // if func is 0, it is adding so check if record exists
    if (func == 0){
      if (table[time] != -1) {
      printf("Error: Meal does already exist in the record.\n");
      return false;
      }
    }

    // checks if provided calorie for one hour or total calorie will exceeds limit of 2500
    if ((2500 < calorie) || (2500 < (calorie + total))) {
      printf("Error: Caloric intake exceeds the 2500 calories limit.\n");
      return false;
    }

    // checks if provided calorie for one hour or total calorie will exceeds limit of 2500
    if (calorie < 1) {
      printf("Error: Caloric entered was 0 or negative.\n");
      return false;
    }

    // checks if any calories was intaked within the 2 hours previous
    for (int i = 1; i < 3; i++){
      if (-1 < time - i) {
        if (table[time-i] > -1) {
          printf("Error: Cannot have multiple meals in less than 3 hours.\n");
          return false;
        }
      }
    }

    // checks if any calories was intaked within the 2 hours after
    for (int i = 1; i < 3; i++){
      if (24 > time + i) {
        if (table[time+i] > -1) {
          printf("Error: Cannot have multiple meals in less than 3 hours.\n");
          return false;
        }
      }
    }

    return true;
  }


int main(int argc, char const *argv[])
  {
    long int cal_hours[24]; // table to store calories per hour
    for (int i = 0; i < 24; i++)
    {
      cal_hours[i] = -1;
    }

    long int total = 0; // total calories
    long int calorie = 0; // calorie in input
    long int time = 0; // time in input
    int function = -1; // function for checking, add = 0, replace = 1

    char input[1048]; // instantiate input string

    // get input, strip ending newline from terminal and then get first token of input while spliting at spaces
    //printf("Please enter a string\n");
    printf("$ ");
    fgets(input, 1048, stdin);
    char *token;
    //printf("Command:%s", input);
    token = strtok(input, "\n");
    token = strtok(token, " ");

    // while loop runs until "quit" is the input
    while (strcmp(token, "quit")!=0) 
      {
        // function variable to indicate if input is valid
        function = -1;

        // if printplan, print calories per hour in sequential order
        if (strcmp(token, "printplan")==0) 
          {
          for (int i = 0; i < 24; i++) 
            {
            if (cal_hours[i] > -1) 
              {
              printf("%i %li\n", i, cal_hours[i]);
              }
            }
          }

        else 
          {
          // function = 0, so check knows
          if (strcmp(token, "add")==0) 
            {
            function = 0;
            }
        
          // function = 1, so check knows
          if (strcmp(token, "replace")==0) 
            {
            function = 1;
            }
          
          // if function = -1, it was not printplan, add, replace, or quit
          if (function == -1) 
            {
            printf("Invalid command\n");
            }
          
          else 
            {
            // get calorie and time from input
            token = strtok(NULL, " ");
            calorie = strtol(token, NULL, 10);
            token = strtok(NULL, " ");
            time = strtol(token, NULL, 10);

            // checks if request is valid
            if (check(calorie, time, cal_hours, total, function)) 
              {
              // for replace, remove old amount of calories from total
              if (function == 1) 
                {
                total -= cal_hours[time];
                }
              // add calorie into table for hour, add to total
              cal_hours[time] = calorie;
              total += calorie;
              }
            }
          }

      // get input, strip ending newline from terminal and then get first token of input while spliting at spaces
      printf("$ ");
      fgets(input, 1048, stdin);
      //printf("Command:%s", input);
      token = strtok(input, "\n");
      token = strtok(token, " ");
      }

    return 0;
  }
