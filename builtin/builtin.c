#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include "builtin.h"
#include "../textInput/launch.h"




// List of builtin commands, followed by their corresponding functions.
char *builtin_str[]={
  "cd",
  "help",
  "exit",
  "touch",
  "listDir",
};

int (*builtin_func[]) (char **) = {
  &iskaSh_cd,
  &iskaSh_help,
  &iskaSh_exit,
  &iskaSh_touch,
  &iskaSh_listDir
};

int iskaSh_num_builtins(){
  return sizeof(builtin_str) / sizeof(char *);
};

// Sorts the string in an aplhabetical order
void sortString(char **array, int ammountOfItems){
int i,j;
char tmp[100];
for(i=0; i<ammountOfItems;i++){
    for (j=i+1;j<ammountOfItems;j++) {
      if(strcmp(array[i],array[j])>0){
        strcpy(tmp,array[i]);
        strcpy(array[i],array[j]);
        strcpy(array[j],tmp);
      }
    }
  }
};


// Builtin function implemetations
int iskaSh_listDir(char **args){
  DIR *d;
  struct dirent *dir;
  d = opendir(".");
  int amountOfFiles=0, i, j;
  char *dirFiles[100];

  if (d){
    while ((dir = readdir(d)) != NULL && amountOfFiles < 100) {
     // printf("%s\n", dir->d_name);
    dirFiles[amountOfFiles] = malloc(strlen(dir->d_name)+1);
      if (dirFiles[amountOfFiles]== NULL) {
        perror("iskaSh: Malloc error");
        return 1;
      }
      strcpy(dirFiles[amountOfFiles],dir->d_name);
      amountOfFiles++;
    }
  closedir(d);
  }
  sortString(dirFiles,amountOfFiles);

  for (i=0;i<amountOfFiles;i++) {
    printf("%s  ", dirFiles[i]);
    free(dirFiles[i]);
  }
  printf("\n");
  return 1;
}

int iskaSh_touch(char **args){
  FILE *fptr;
if (args[1]== NULL){
    fprintf(stderr, "iskaSh: expected argument to \"touch\"\n");
  } else {
   fptr = fopen(args[1],"w");
    fclose(fptr);
  }
  return 1;
}

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

