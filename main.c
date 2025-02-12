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
    free(args);
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
