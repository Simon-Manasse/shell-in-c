#ifndef BUILTIN_H_
#define BUILTIN_H_

// Function declarations for builtin shell commands:
int iskaSh_cd(char **args);
int iskaSh_help(char **args);
int iskaSh_exit(char **args);
int iskaSh_execute(char **args);
#endif // !BUILTIN_H_
