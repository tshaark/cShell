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




int rsh_cd(char **args)
{
	char path[1024];
	if(args[1] == NULL)
		fprintf(stderr,"rsh: expected argument to \"cd\"\n");
	else
	{
		char * arg=args[1];
		getcwd(path,1024);
		if(chdir(args[1])!=0)
			perror("rsh");
	}
	return 1;
}