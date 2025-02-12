#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Define
#define ISKASH_RL_BUFSIZE 1024
#define ISKASH_TOK_BUFSIZE 64
#define ISKASH_TOL_DELIM " \t\r\n\a"

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

char **iskaSh_split_line(char *line)
{
  int bufsize = ISKASH_TOK_BUFSIZE, position=0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens){
    fprintf(stderr, "iskaSh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line,ISKASH_TOL_DELIM);
  while (token != NULL) {
    tokens[position] =token;
    position++;
    
    if (position  >= bufsize){
      bufsize+=ISKASH_TOK_BUFSIZE;
      tokens=realloc(tokens,bufsize*sizeof(char*));
      if (!tokens){
        fprintf(stderr, "iskaSh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token=strtok(NULL,ISKASH_TOL_DELIM);
  }
tokens[position]=NULL;
  return tokens;
}


char *iskaSh_read_line(void){
  int bufsize = ISKASH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char)* bufsize);
  int c;

  if (!buffer){
    fprintf(stderr, "iskaSh: allocation error\n");
    exit(EXIT_FAILURE);
  }
  while (1){
    // Read a character
    c = getchar();

    // If we hit EOF, replace it with a null character and return.
    if (c == EOF || c=='\n'){
      buffer[position] = '\0';
      return buffer;
    }
    else {
      buffer[position] = c;
    }
    position++;

    // If we have exceeded the buffer, reallocate.
    if(position >=bufsize){
      bufsize+= ISKASH_RL_BUFSIZE;
      buffer = realloc(buffer,bufsize);
      if (!buffer){
        fprintf(stderr, "iskaSh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
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
