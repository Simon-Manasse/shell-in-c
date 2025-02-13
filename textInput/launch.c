#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "launch.h"

int iskaSh_launch(char **args){
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0){
  // Child process
  if (execvp(args[0],args) == -1){
      perror("iskaSh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0){
    // Error forking
    perror("iskaSh");
  }else {
    // Parent process
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}
