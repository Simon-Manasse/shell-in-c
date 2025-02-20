#include <stdio.h>
#include <stdlib.h>
#include "./splitlines.h"

#define ISKASH_RL_BUFSIZE 1024

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
    if (c == EOF || c=='\n') {
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

