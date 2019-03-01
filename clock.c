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



int rsh_clock(char **args)
{
	int i=1;
	while(i<=atoi(args[4]))
	{
		FILE * fd=fopen("/proc/driver/rtc","r");
		char * line1=NULL;
		char * line2=NULL;
		size_t n=0;
		getline(&line1,&n,fd);
		strtok(line1,":");
		line1=strtok(NULL," ");
		int m=strlen(line1);
		for (int j = 0; j < m; ++j)
		{
			if(line1[j] == '\n')
			{
				line1[j]='\0';
				break;
			}
		}
		getline(&line2,&n,fd);
		strtok(line2,":");
		line2=strtok(NULL," ");
		printf("%s,",line1 );
		printf("%s\n",line2 );
		sleep(atoi(args[2]));	
		i+=atoi(args[2]);
		fclose(fd);
	}

}