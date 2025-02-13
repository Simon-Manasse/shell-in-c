// Includes
#include <stdlib.h>
#include <stdio.h>

// headers
#include "./textInput/readline.h"
#include "./textInput/splitlines.h"
#include "./builtin/builtin.h"

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
