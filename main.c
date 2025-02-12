#define MACSKA_RL_BUFSIZE 1024

char *macska_read_line(void){
  int bufsize = MACSKA_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char)* bufsize);
  int c;

  if (!buffer){
    fprintf(stderr, "macska: allocation error\n");
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
      bufsize+= MACSKA_RL_BUFSIZE;
      buffer = realloc(buffer,bufsize);
      if (!buffer){
        fprintf(stderr, "macska: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

void macska_loop(void){
  char *line;
  char **args;
  int status;

  do {
    printf("> ");
    line = macska_read_line();
    args = macska_split_line(line);
    status = macska_execute(args);

    free(line);
    free(args)
  } while (status);
}

int int main(int argc, char *argv[])
{
 // load config files, if any


  // Run command loop
  macska_loop();

  //Perform shutdown/cleanup

  return EXIT_SUCCESS;
}
