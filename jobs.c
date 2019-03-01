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
extern char a[100][1000];
extern char path[1024],pathOriginal[1024];
extern int bgProcCount=0;

int rsh_overkill(char **args)
{
	int i=0;
	for(i=0;i < 5000005;i++)
	{
		if(name_proc[i][0] != '\0' && bgProcCount > 0)
		{
			kill(i,SIGKILL);
			name_proc[i][0] = '\0';
			bgProcCount--;
		}
	}
	return 1;
}
int rsh_jobs(char **args)
{
	int i=0,count=1;
	char Process[1000];
	char status;
    int temp;
	char * temp2;
	for(i=0;i< 5000005;i++)
	{
		if(name_proc[i][0] != '\0')
	  	{
				sprintf(Process, "/proc/%d/stat", i);
			    FILE * stat = fopen(Process, "r");
						
				fscanf(stat, "%d %s %c",&temp,&temp2, &status);
				if(status == 'T')
			  		printf("[%d] Stopped %s %d\n", count, name_proc[i], i);
			    else 
			  		printf("[%d] Running %s %d\n", count, name_proc[i], i);
				count++;
		}
	}
	return 1;
}
int rsh_kjob(char **args)
{
	int job_number=atoi(args[1]);
	int count=0,i=0;
	for(i=0;i<5000005;i++)
	{	
		if(name_proc[i][0] != '\0')
		{
			count++;
		}
		if(count == job_number)
		{
			break;
		}
	} 
	int sig=atoi(args[2]);
	kill(i,sig);
	return 1;
}
int rsh_bg(char **args)
{
	int i=0;
	int count= 0;
	for(i=0;i < 5000005;i++)
	{
		if(name_proc[i][0] != '\0')
		{
			count++;
		}
		if(count == atoi(args[1]))
		{
			break;
		}
	}
	kill(i,SIGCONT);
	name_proc[i][0] = '\0';
	return 1;
}
int rsh_fg(char **args)
{
	int i=0;
	int count= 0;
	for(i=0;i < 5000005;i++)
	{
		if(name_proc[i][0] != '\0')
		{
			count++;
		}
		if(count == atoi(args[1]))
		{
			break;
		}
	}
	kill(i,SIGCONT);
	waitpid(-1,NULL,WUNTRACED);
}
