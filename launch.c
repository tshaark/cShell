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
#define RSH_RL_BUFSIZE 1024
#define RSH_TOK_BUFSIZE 64
#define RSH_TOK_DELIM " \t\r\n\a"
#define RSH_NUM_BUILTINS 15

extern char name_proc[5000005][100];

int rsh_launch(char **args)
{
	pid_t pid,pid_wt;
	pid =fork();
	if(pid == 0)
	{
		if(execvp(args[0],args) == -1)
			perror("rsh");
		exit(EXIT_FAILURE);
	}
	else if(pid < 0)
		perror("rsh"); //fork me error
	else
	{
		int status;		
		if(args[1] != NULL && args[1][0] == '&')
		{
			strcpy(name_proc[pid],args[0]);
		}
		else
		{
			do{
				pid_wt=waitpid(pid,&status,WUNTRACED);
			}while(!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	} 
	return 1;
}