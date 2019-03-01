#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <time.h>
#include <grp.h>
#include <sys/wait.h>
#include <fcntl.h> 
// #include "headers.h"

int rsh_unsetenv (char **args) {
	if (unsetenv(args[1]) != 0)
		 perror("rsh");
	return 1;
}

int rsh_setenv(char **args)
{
	if(args[2]==NULL)
		args[2]=" ";
	if(setenv(args[1],args[2],1) != 0)
		perror("rsh");
	return 1;
}