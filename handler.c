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

extern char name_proc[5000005][100];

void handler(int sig)
{
	int stat,i;
	for(i=0;i<5000005;i++)
	{
		if(waitpid(i,&stat,WNOHANG) && name_proc[i][0]!='\0')
		{
			printf("\n%s with pid %d exited normally (PRESS ENTER TO CONTINUE)\n",name_proc[i],i);
			name_proc[i][0] = '\0';
		}
	}
}