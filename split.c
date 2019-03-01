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

#define RSH_RL_BUFSIZE 1024
#define RSH_TOK_BUFSIZE 64
#define RSH_TOK_DELIM " \t\r\n\a"
#define RSH_NUM_BUILTINS 15



char **rsh_split_line(char *line)
{
	int bufsize = RSH_TOK_BUFSIZE;
	
	char **tokens=malloc(bufsize * sizeof(char*));
	char * token;
	if(!tokens)
	{
		fprintf(stderr,"rsh: allocation error\n");
		exit(EXIT_FAILURE);
	}
	token=strtok(line,RSH_TOK_DELIM);
	int i=0;
	while(token!=NULL)
	{
		tokens[i++]=token;
		if(i>=bufsize)
		{
			bufsize += RSH_TOK_BUFSIZE;
			tokens = realloc(tokens,bufsize * sizeof(char *));
			if(!tokens)
			{
				fprintf(stderr,"rsh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL,RSH_TOK_DELIM);
	}
	tokens[i] = NULL;
	return tokens;
}