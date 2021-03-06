/* Zolangi Ramirez, Jose Aparicio, Christian Soltero, Alvin Tsui*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 80 // max length command
#define BUFFER_SIZE 10 //size of buffer
#define DELIMETER "\n" //delimeter
int hist_num = 1;

int history(char *hist[], int current)
{
  int i = current;
	int hist_num2;
	if(hist_num < 10)
    hist_num2 = 1;
    else if(hist_num > 10)
      hist_num2 = hist_num - 10;
    do {
      if (hist[i]) {
        printf("%d  %s\n", hist_num2, hist[i]);
        hist_num2++;
      }
      i = (i + 1) % BUFFER_SIZE;
    } while (i != current);
    return 0;
}

/*//check if command includes &.
int hasAmpersand(char in[])
{
  int index = 0;
  while(in[index] != '\n'){
    if(in[index] == '&'){
      return 1;
    }
    index++;
  }
  return 0;
}
*/
int main(void)
{
  char input[MAX_LINE_LENGTH];
  char *hist[BUFFER_SIZE];
  int i, current = 0;

  char *args[MAX_LINE_LENGTH/2+1]; // command line arguments
  int should_run = 1; // flag to determine when to exit program

  for(i = 0; i <BUFFER_SIZE; i++)
    hist[i] =NULL;

  while(should_run) {

    char *input = (char *)(malloc(MAX_LINE_LENGTH * sizeof(char)));

    printf("osh> "); //prompt
    fflush(stdout); //flushes output
    fgets(input, MAX_LINE_LENGTH, stdin); //gets input and length of i

    if(input[strlen(input) - 1] == '\n')
      input[strlen(input) - 1] = '\0'; //removes the "/n"

    free(hist[current]);
    hist[current] = strdup(input);
  	current = (current + 1) % BUFFER_SIZE;
    hist_num++;
    if (strcmp(input, "history") == 0)
      history(hist, current);
    else if(strcmp(input, "!!") == 0)
      hist[current] = hist[current -1];
    else if (strcmp(input, "quit") == 0)
      break;
    // printf("INPUT: %s\n", input);

    pid_t pid = fork();//create pid variable which holds process id parent
    if(pid == 0) {
      execvp(input, &input);
      exit(0);
    }
    //here we wouldve had had to include pid = fork() to create a child process

    //if it does have an &, then we want both child and parent to execute
    /* if(hasAmpersand(input)){
      //if child process, execute
      if (pid == 0) {
        printf("X\n");
        execvp(args[0], args);
        exit(0);
      }
      //if parent process, execute
      else if (pid > 0) {
        printf("Y\n");
      }
      //if parent process, but no child, execute
      else{
        printf("Z\n");
      }
    }
    //if it does not have an &, then we want the parent to wait for the child to finish executing
    else{
      //if child process, execute
      if (pid == 0) {
        printf("R\n");
        execvp(args[0], args);
        exit(0);
      }
      //if parent process, wait and then execute
      else if (pid > 0) {
        wait(NULL);
        printf("S\n");
      }
      //if parent process, but no child, execute
      else{
        printf("T\n");
      }
    }*/
    /*
    * After reading user input, the steps are:
    *(2) the child process will invoke execvp()
    *(3) if command included &, parent will invoke wait()
    */
  }
  return 0;
}
