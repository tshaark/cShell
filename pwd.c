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
extern char name_proc[5000005][100];
extern char a[100][1000];
extern char path[1024],pathOriginal[1024];


int rsh_pwd(char **args)
{
	printf("%s\n",path );
}
void pwd(char * pathOriginal,char * path)
{
	int n=strlen(path);
	int n1=strlen(pathOriginal);
	if(n>=n1)
	{
		char str[100];
		for(int i=0;i<n-n1;i++)
			str[i+1]=path[n1+i];
		str[0]='~';
		for(int i=0;i<n-n1+1;i++) {
			path[i] = str[i];
		}
		path[n-n1+1] = '\0';
	}
}