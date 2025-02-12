#define ISKASH_RL_BUFSIZE 1024
#define ISKASH_TOK_BUFSIZE 64;
#define ISKASH_TOL_DELIM " \t\r\n\a";
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
    free(args)
  } while (status);
}

int int main(int argc, char *argv[])
{
 // load config files, if any


  // Run command loop
  iskaSh_loop();

  //Perform shutdown/cleanup

  return EXIT_SUCCESS;
}
