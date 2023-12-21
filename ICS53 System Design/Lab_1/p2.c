#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// gcc p2.c -o p2
// ./p2

int main(int argc, char const *argv[])
  {
    // get user sentence/string
    char input[1048];
    char original[1048];
    //printf("Please enter a string\n");
    fgets(input, 1048, stdin);

    strcpy(original, input);

    // get user delimiters
    char delim[1048];
    //printf("Please enter delimiters\n");
    fgets(delim, 1048, stdin);

    char * token = strtok(input, delim);

    // run until no more tokens from user input
    while (token != NULL)
    {
      printf ("%s\n",token);

      // goes to next to token
      token = strtok (NULL, delim);
    }

    printf("%s", original);
    return 0;
  }


