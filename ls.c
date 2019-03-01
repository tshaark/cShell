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


extern void checkPermissions(mode_t filemode);
extern void print_time(struct stat attr);;


int rsh_ls(char **args)
{
	DIR *mydir;
	char *arg=args[1];
    struct dirent *myfile;
    struct stat mystat;
	if(args[1] == NULL)
	{
		 mydir = opendir(".");
		 while((myfile = readdir(mydir)) != NULL)
		 {
		 	 stat(myfile->d_name, &mystat); 
		 	 if(myfile->d_name[0] != '.' )
		 		 printf("%s ", myfile->d_name);
		 }
		 printf("\n");
    }
    else if(arg[0] == '-' && arg[1] == 'a' && arg[2] == '\0')
    {
    	mydir = opendir(".");
		 while((myfile = readdir(mydir)) != NULL)
		 {
		 	 stat(myfile->d_name, &mystat); 
		 	 printf("%s ", myfile->d_name);
		 }
		 printf("\n");
    }
    else if(arg[0] == '-' && arg[1] == 'l' && arg[2] == 'a' || arg[0] == '-' && arg[1] == 'a' && arg[2] == 'l')
    {
   		if(args[2] == NULL)
   			mydir = opendir(".");
   		else
   			mydir = opendir("args[2]");
    	while((myfile = readdir(mydir)) != NULL)
    	{
        	stat(myfile->d_name, &mystat);
        	checkPermissions(mystat.st_mode);
        	printf("%2ld ",mystat.st_nlink);
        	struct group *grp;
			struct passwd *pwd;
			pwd = getpwuid(mystat.st_uid);
			printf("%s ", pwd->pw_name);
			grp = getgrgid(mystat.st_gid);
			printf("%s ", grp->gr_name);
			printf("%7zu ",mystat.st_size );
			print_time(mystat);
        	printf(" %s\n", myfile->d_name);
    	}
    }
    else if(arg[0] == '-' && arg[1] == 'l' && arg[2] == '\0')
    {
   		if(args[2] == NULL)
   			mydir = opendir(".");
   		else
   			mydir = opendir(args[2]);
    	while((myfile = readdir(mydir)) != NULL)
    	{
        	if(myfile->d_name[0] != '.')
        	{
        		stat(myfile->d_name, &mystat);
        		checkPermissions(mystat.st_mode);
        		printf("%2ld ",mystat.st_nlink);
        		struct group *grp;
				struct passwd *pwd;
				pwd = getpwuid(mystat.st_uid);
				printf("%s ", pwd->pw_name);
				grp = getgrgid(mystat.st_gid);
				printf("%s ", grp->gr_name);
				printf("%7zu ",mystat.st_size );
				print_time(mystat);
        		printf(" %s\n", myfile->d_name);
        	}
    	}
    }
    return 1;
}