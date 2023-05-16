#ifndef OURSHELL_H
#define OURSHELL_H
#define BUFFER_SIZE 1024
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*functions from command_handlers.c - for executing commands*/
void print_command(char *command);

/*functions from strfunctions.c - for string manipulation*/
int _putchar(char c);
void exefork(char **arstr, char envp[])
#endif
