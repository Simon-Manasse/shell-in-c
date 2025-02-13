// Includes
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ncurses.h>

// headers
#include "./textInput/launch.h"
#include "./textInput/readline.h"
#include "./textInput/splitlines.h"



// Function declarations for builtin shell commands:
int iskaSh_cd(char **args);
int iskaSh_help(char **args);
int iskaSh_exit(char **args);

// List of builtin commands, followed by their corresponding functions.
char *builtin_str[]={
  "cd",
  "help",
  "exit"
};

int (*builtin_func[]) (char **) = {
  &iskaSh_cd,
  &iskaSh_help,
  &iskaSh_exit
};

int iskaSh_num_builtins(){
  return sizeof(builtin_str) / sizeof(char *);
}

// Builtin function implemetations
int iskaSh_cd(char **args){
  if (args[1]== NULL){
    fprintf(stderr, "iskaSh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0){
      perror("iskaSh");
    }
  }
  return 1;
}

int iskaSh_help(char **args){
  int i;
  printf("Simon Mansse's iskaSh\n");
  printf("Type program names and arguments and hit enter.\n");
  printf("The following are built in:\n");

  for (i=0;i<iskaSh_num_builtins();i++) {
    printf(" %s\n",builtin_str[i]);
  }
  printf("Use the man command for information on other programs.\n");
  return 1;
}

int iskaSh_exit(char **args){
  return 0;
}

int iskaSh_execute(char **args){
  int i;

  if (args[0] == NULL) {
    //empty command was entered
    return 1;
  }

  for (i = 0; i < iskaSh_num_builtins() ; i++) {
    if (strcmp(args[0], builtin_str[i]) == 0){
      return (*builtin_func[i])(args);
    }
  }

  return iskaSh_launch(args);
}

void iskaSh_loop(void){
  char *line;
  char **args;
  int status;

  do {
    printf("> ");
    line = iskaSh_read_line();
    args = iskaSh_split_line(line);
    status = iskaSh_execute(args);

    free(line);
    free(args);
  } while (status);
}

int main(int argc, char *argv[])
{
 // load config files, if any


  // Run command loop
  iskaSh_loop();

  //Perform shutdown/cleanup

  return EXIT_SUCCESS;
}
