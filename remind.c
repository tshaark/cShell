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
// #include "headers.h"
#include <fcntl.h> 



int rsh_remindme(char **args)
{
	pid_t pid,pid_wt;
	pid =fork();
	if(pid == 0)
	{
		sleep(atoi(args[1]));
		printf("%s\n",args[2] );
	}
}