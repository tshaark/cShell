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
extern char name_proc[5000005][100];
extern char a[100][1000];
extern char path[1024],pathOriginal[1024];

char *rsh_read_line(void)
{
  int bufsize = RSH_RL_BUFSIZE;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c,i=0;
  if (!buffer)
  {
    fprintf(stderr, "rsh: allocation error\n");
    exit(EXIT_FAILURE);
  }
  while (1) {
    c = getchar();
    if (c == EOF || c == '\n')
    {
      buffer[i++] = '\0';
      return buffer;
    } 
    else 
    {
      buffer[i++] = c;
    }
    if (i >= bufsize)
    {
      bufsize += RSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer)
      {
        fprintf(stderr, "rsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}