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

extern char a[100][1000];


int  rsh_sep_semicolon(char * line,int k)
{
	int n=strlen(line),j=0;
	for (int i = 0; i < n; ++i)
	{
		if(line[i] != ';')
			a[k][j++]=line[i];
		else
		{
			k++;
			j=0;
		}
	}
	return k;
}