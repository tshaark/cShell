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


void print_time(struct stat attr)
{
    char time[50];
    strftime(time, 50, "%m-%d %H:%M", localtime(&attr.st_mtime));
    printf ("%s ", time);
}