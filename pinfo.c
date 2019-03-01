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

int rsh_pinfo (char ** args)
{
    int pid; 
	char pathRoot[1024];
	getcwd(	pathRoot,1024);
    char Proc[1000];
    strcpy(Proc, "/proc/");
    if(args[1]) 
        strcat(Proc, args[1]);
    else 
        strcat(Proc, "self");
    char Stats[100];
    strcpy(Stats, Proc);
    strcat(Stats, "/stat");
    FILE * stat = fopen(Stats, "r");
    if(!stat)
    {
    	printf("this process does not exist\n");
    	return 1;
    }
    char status,name[20];
    fscanf(stat, "%d", &pid);
    fscanf(stat, "%s", name);
    fscanf(stat, "%c", &status);
    printf("pid: %d\n", pid);
    printf("Process Status: %c\n", status);
    fclose(stat);
    strcpy(Stats, Proc); 
    strcat(Stats, "/statm");
    FILE * mem = fopen(Stats, "r");
    int memSize;
    fscanf(mem, "%d", &memSize);
    printf("Memory: %d\n", memSize);
    fclose(mem);
    char exePath[1024];
    strcpy(Stats, Proc);
    strcat(Stats, "/exe");
    readlink(Stats, exePath, sizeof(exePath));
    int sameChar = 0, base = strlen(pathRoot);
    for(sameChar = 0; sameChar < base; sameChar++)
        if(pathRoot[sameChar] != exePath[sameChar]) 
        	break;;
    char relPath[1000];
    if(sameChar == base)
    {
        relPath[0] = '~';
        relPath[1] = '\0';
        strcat(relPath, (const char *)&exePath[base]);
    }
    else
    {
        strcpy(relPath, exePath);
        relPath[strlen(exePath)] = '\0';
    }
    
    printf("Executable Path: %s\n", relPath);
    return 1;
}