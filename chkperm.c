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



void checkPermissions(mode_t filemode)
{
	printf(S_ISDIR(filemode) ? "d" : "-");
    putchar((filemode & S_IRUSR) ? 'r' : '-');
    putchar((filemode & S_IWUSR) ? 'w' : '-');
    putchar((filemode & S_IXUSR) ? 'x' : '-');
    putchar((filemode & S_IRGRP) ? 'r' : '-');
    putchar((filemode & S_IWGRP) ? 'w' : '-');
    putchar((filemode & S_IXGRP) ? 'x' : '-');
    putchar((filemode & S_IROTH) ? 'r' : '-');
    putchar((filemode & S_IWOTH) ? 'w' : '-');
    putchar((filemode & S_IXOTH) ? 'x' : '-');
}