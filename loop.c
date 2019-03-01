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

extern int rsh_launch(char **args);
extern int rsh_cd(char **args);
extern int rsh_quit(char **args);
extern int rsh_pwd(char **args);
extern void checkPermissions(mode_t filemode);
extern void print_time(struct stat attr);
extern int rsh_pinfo (char ** args);
extern int rsh_ls(char **args);
extern int rsh_remindme(char **args);
extern int rsh_clock(char **args);
extern int rsh_echo(char **args);
extern void handler(int sig);
extern int rsh_exec(char **args);
extern int rsh_launch(char **args);
extern void pwd(char * pathOriginal,char * path);
extern char *rsh_read_line(void);
extern char **rsh_split_line(char *line);
extern int rsh_sep_semicolon(char * line,int k);
extern void rsh_loop();
extern int rsh_setenv(char **args);
extern int rsh_unsetenv (char **args);
extern int rsh_overkill(char **args);
extern int rsh_jobs(char **args);
extern int rsh_kjob(char **args);
extern int rsh_bg(char **args);
extern int rsh_fg(char **args);
extern int rsh_redirect(char **args);
extern int rsh_append(char **args);
extern int rsh_pipe(char** args);

extern char name_proc[5000005][100];
extern char a[100][1000];
extern char path[1024],pathOriginal[1024];
extern int k=0,mainPID;
extern int bgProcCount=0;


#define RSH_RL_BUFSIZE 1024
#define RSH_TOK_BUFSIZE 64
#define RSH_TOK_DELIM " \t\r\n\a"
#define RSH_NUM_BUILTINS 15

void rsh_loop()
{
	char usr[100],s[1024];
	getlogin_r(usr,sizeof(usr));
	char hostname[100];
	gethostname(hostname, sizeof(hostname));	
	getcwd(pathOriginal,1024);
	char *line;
	char **args;
	int status,k=0;
	do
	{
		getcwd(path,1024);
		pwd(pathOriginal,path);
		printf("%s@%s:%s$",usr,hostname,path);
		line = rsh_read_line();
		k=rsh_sep_semicolon(line,k);	
		for(int i=0;i<k+1;i++)
		{
			args= rsh_split_line(a[i]);
			status= rsh_exec(args);
			signal(SIGCHLD, handler);
			free(args);
		}
		memset(a,0,sizeof(a));
		free(line);
		k=0;
	}while(status);
}