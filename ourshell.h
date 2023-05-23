#ifndef OURSHELL_H
#define OURSHELL_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

char* get_location(char* command);
void execmd(char **argv);
	
#endif
