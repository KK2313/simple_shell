#ifndef OURSHELL_H
#define OURSHELL_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

<<<<<<< HEAD

/** Used Prototypes */
int identify_program(data_of_program *data);
char **divide_path(data_of_program *data);
int scan_file(char *entire_path);

char *get_env_var(char *env_var, data_of_program *data);

int str_len(char *str);
char *str_dup(char *str);
int str_compare(char *str1, char *str2, int number);
char *str_join(char *str1, char *str2);
void str_rev(char *str);

typedef struct info
{
char *program_name;
char *input_line;
char *command_name;
int exec_counter;
int file_descriptor;
char **toks;
char **env;
char **alias_list;
} data_of_program;

typedef struct builtins
{
char *builtin;
int (*function)(data_of_program *data);
} builtins;
=======
void execmd(char **argv);
char *get_location(char *command);
>>>>>>> c319b385b41461630c93263a402f2fe7dba18e82

#endif
