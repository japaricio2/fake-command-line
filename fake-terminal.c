#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 80 /* The maximum length command */


int main(void)
{
  char *args[MAX_LINE/2+1]; /* command line arguments */
  int should_run = 1; /* flag to determine when to exit program */

  while(should_run) {
    char *input = (char *)(malloc(MAX_LINE * sizeof(char)));

    printf("osh> ");
    fflush(stdout);
    fgets(input, MAX_LINE, stdin);
    input[strlen(input) - 1] = '\0';
    printf("INPUT: %s\n", input);

    pid_t pid = fork(); /* create pid variable which holds process id*/
	/* ^ fork() a child process; create a child process */

    if (pid == 0) {
      execvp(input, &input);
    }

    /*
    * After reading user input, the steps are:
    *(1) fork a child process using fork()
    *(2) the child process will invoke execvp()
    *(3) if command included &, parent will invoke wait()
    */
  }
  return 0;
}
