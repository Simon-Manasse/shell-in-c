#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "splitlines.h" 


#define ISKASH_TOK_BUFSIZE 64
#define ISKASH_TOK_DELIM " \t\r\n\a"


char **iskaSh_split_line(char *line)
{
  int bufsize = ISKASH_TOK_BUFSIZE, position=0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens){
    fprintf(stderr, "iskaSh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line,ISKASH_TOK_DELIM);
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

    token=strtok(NULL,ISKASH_TOK_DELIM);
  }
tokens[position]=NULL;
  return tokens;
}
