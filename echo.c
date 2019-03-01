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



int rsh_echo(char **args)
{
	char *arr=malloc(sizeof(char)*2048);

	char temp[1024];
	char *arg=args[1];
	int i=0,size=0,flag=0,k=0,lite=0;
	while(arg[i] != '\0')
	{
		i++;
	}
	size=i;
	for(i=0;i<size;i++)
	{
		if(arg[i] == '\"' && flag == 0 && lite==0)
		{
			flag=1;
			lite = 1;
		}
		else if(arg[i] == '\"' && flag == 1 && lite==1)
			flag=0;
		else if(arg[i] =='\'' && flag == 0 && lite == 0)
		{
			flag =1;
			lite=2;
		}
		else if(arg[i] == '\'' && flag == 1 && lite==2)
			flag=0;
		else
			arr[k++]=arg[i];
	}
	while(flag != 0)
	{
		printf(">");
		scanf("%s",temp);
		int n=strlen(temp);
		for(int i=0;i<n;i++)
		{
			if(temp[i]=='\"' && lite == 1)
				flag=0;
			else if(temp[i]=='\'' && lite == 2)
				flag=0;
			else
				arr[k++]=temp[i];
		}
	}
	printf("%s\n",arr );
	return 1;
}