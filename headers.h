#define RSH_RL_BUFSIZE 1024
#define RSH_TOK_BUFSIZE 64
#define RSH_TOK_DELIM " \t\r\n\a"
#define RSH_NUM_BUILTINS 15


char name_proc[5000005][100];
char a[100][1000];
char path[1024],pathOriginal[1024];
int k=0,mainPID;
int bgProcCount=0;

int rsh_launch(char **args);
int rsh_cd(char **args);
int rsh_quit(char **args);
int rsh_pwd(char **args);
void checkPermissions(mode_t filemode);
void print_time(struct stat attr);
int rsh_pinfo (char ** args);
int rsh_ls(char **args);
int rsh_remindme(char **args);
int rsh_clock(char **args);
int rsh_echo(char **args);
void handler(int sig);
int rsh_exec(char **args);
int rsh_launch(char **args);
void pwd(char * pathOriginal,char * path);
char *rsh_read_line(void);
char **rsh_split_line(char *line);
int rsh_sep_semicolon(char * line,int k);
void rsh_loop();
int rsh_setenv(char **args);
int rsh_unsetenv (char **args);
int rsh_overkill(char **args);
int rsh_jobs(char **args);
int rsh_kjob(char **args);
int rsh_bg(char **args);
int rsh_fg(char **args);
int rsh_redirect(char **args);
int rsh_append(char **args);
int rsh_pipe(char** args);