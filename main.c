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
#include "headers.h"
#include <fcntl.h> 


// extern char name_proc[5000005][100];
// extern char a[100][1000];
// extern char path[1024],pathOriginal[1024];
// extern int k=0,mainPID;
// extern int bgProcCount=0;


int (*builtin_func[])(char **) ={
	&rsh_cd,
	&rsh_quit,
	&rsh_pwd,
	&rsh_echo,
	&rsh_ls,
	&rsh_pinfo,
	&rsh_remindme,
	&rsh_clock,
	&rsh_setenv,
	&rsh_unsetenv,
	&rsh_overkill,
	&rsh_jobs,
	&rsh_kjob,
	&rsh_bg,
	&rsh_fg
};
char *builtin_str[]={
	"cd",
	"quit",
	"pwd",
	"echo",
	"ls",
	"pinfo",
	"remindme",
	"clock",
	"setenv",
	"unsetenv",
	"overkill",
	"jobs",
	"kjob",
	"bg",
	"fg"
};
int rsh_redirect(char **args)
{
	pid_t pid = fork();
	pid_t wpid;
	int status;
	if (pid == 0)
    { 
    	int i,fd0,fd1,in=0,out=0,count1=0,count2=0;
    	char input[64],output[64][64],append[64][64];
   		for(i=0;args[i]!='\0';i++)
    	{
        	if(strcmp(args[i],"<")==0)
        	{        
        	    args[i]=NULL;
        	    strcpy(input,args[i+1]);
           	    in=1;           
        	}               

        	else if(strcmp(args[i],">")==0)
        	{      
        	    args[i]=NULL;
        	    strcpy(output[count1],args[i+1]);
        	    count1++;
        	    out=1;
        	}      
   		}
    	if(in == 1)
    	{   
    		if((fd0=open(input,O_RDONLY,0))<0)
    			perror("Couldn't open input file");
    		if(dup2(fd0,0)<0)
    			perror("Error in dup2");
    		close(fd0);
       	}
       	if(out == 1)
       	{
    		for(i=0;i<count1;i++)
    		{
 				if((fd1=open(output[i], O_WRONLY | O_TRUNC | O_CREAT ,0644))< 0)
    			 	perror("Couldn't open output file");
    			if(dup2(fd1,1)<0)
    			 	perror("Error in dup2");
    			close(fd1);
    		}
    	}
    	if(execvp(args[0], args) == -1)
   		{
       		printf("%s: command not found\n",args[0]);
       	}
	}
    else if((pid) < 0)
    {     
        perror("fork() failed!");
    }
    else
    {                                  
      do
      {
        wpid = waitpid(pid, &status, WUNTRACED);
      }while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}
int rsh_append(char **args)
{
	pid_t pid = fork();
	pid_t wpid;
	int status;
	if (pid == 0)
    { 
    	int i,fd,count=0;
    	char append[64][64];
   		for(i=0;args[i]!='\0';i++)
    	{
          	if(strcmp(args[i],">>")==0)
        	{      
        	    args[i]=NULL;
        	    strcpy(append[count],args[i+1]);
        	    count++;
        	}      
   		}
   		for(i=0;i<count;i++)
   		{
   			if((fd=open(append[i], O_WRONLY | O_APPEND | O_CREAT ,0644))< 0)
   			 	perror("Couldn't open output file");
   			if(dup2(fd,1)<0)
   			 	perror("Error in dup2");
   			close(fd);
    	}
    	if(execvp(args[0], args) == -1)
   		{
       		printf("%s: command not found\n",args[0]);
       	}
	}
    else if((pid) < 0)
    {     
        perror("fork() failed!");
    }
    else
    {                                  
      do
      {
        wpid = waitpid(pid, &status, WUNTRACED);
      }while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}
int rsh_pipe(char** args) 
{
	 int status,flag1=0	;
  	 int fd1[2];

  	int fd2[2];

	int i=0;
	int j =0;
	int kk =0;
	int flag=1;
    char **commands=malloc(256 * sizeof(char*));
    int m = 0;
    int count = 0,pipeNum= 0;
  
    char * r = args[0];
    pid_t pid;
    while(r!=NULL)
	{
      if (strncmp(args[m],"|",1)==0)
		 pipeNum++;
      m++;
      r = args[m];
    }
  	count=pipeNum+1;
	while(args[j]!=NULL && flag==1)
	{
		kk = 0;
		char * d = args[j];
		while((strncmp(d,"|",1)!=0))
		{
			commands[kk]=d;
			j++;
			d = args[j];
			if(d == NULL){
				flag = 0;
				kk++;
				break;
			}
			kk++;
		}
		commands[kk] = NULL;
		j++;

		if (i%2 != 0)
			pipe(fd1);
		else
			pipe(fd2);

		pid = fork();

		//Error on being unable to fork the process
		if(pid < 0)
			perror("Fork() failed!");


		//In the child process
		if (pid == 0)
		{
			
			if (i==0)
			{
				dup2(fd2[1],1);
			}
			else if (i==pipeNum){
				if(count%2==0)
				{
				dup2(fd2[0],0);
				}
				else
				{
				dup2(fd1[0],0);
				}
			}

			else
			{
				if(i%2==1)
				{
				dup2(fd2[0],0);
				dup2(fd1[1],1);
				}
				else
				{
				dup2(fd1[0],0);
				dup2(fd2[1],1);
				}
			}
			int s=0;
			for(s=0;commands[s]!= NULL;s++)
			{
				if(strcmp(commands[s],"<") == 0 || strcmp(commands[s],">") == 0)
				{
					rsh_redirect(commands);
				}
			}
			if (execvp(commands[0],commands)==-1)
			{
				printf("%s: command not found\n",commands[0]);
				kill(getpid(),SIGTERM);
			}
		}
		else
		{
			if(i==0)
			{
				close(fd2[1]);
			}

			else if(i==pipeNum)
			{
				if(count%2==0){
					close(fd2[0]);
				}
				else{
					close(fd1[0]);
				}
			}

			else{
				if(i%2==1)
				{
				close(fd1[1]);
				close(fd2[0]);
				}
				else{
				close(fd2[1]);
				close(fd1[0]);
				}
			}
		}
        waitpid(pid,NULL,0);
        i++;

}
return 1;

} 

int rsh_exec(char **args)
{
	int flag = -1;
	if(args[0]==NULL)
		return 1;
	for (int i = 0; args[i]!= '\0' ; ++i)
	{
		if(strcmp(args[i],"|")==0)
		{
			if(flag == 2)
				flag = 3;
			else	
				flag=0;
		}
		else if(strcmp(args[i],">>")==0)
		{
			flag = 1;
		}
		else if(strcmp(args[i],"<") == 0 || strcmp(args[i],">")==0)
		{
			flag = 2;
		}
	}
	// printf("flag is %d",flag);
	if(flag == 0 || flag == 3)
		return rsh_pipe(args);
	if(flag == 1)
		return rsh_append(args);
	if(flag == 2)
		return rsh_redirect(args);

	if(args[0]!=NULL)
	{
		for(int i=0;i<RSH_NUM_BUILTINS;i++)
			if(strcmp(args[0],builtin_str[i]) == 0)
			{
				// printf("HELLO BUDDY!");
				return (*builtin_func[i])(args);
			}
	}
	return rsh_launch(args);
}
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
int rsh_overkill(char **args)
{
	int i=0;
	for(i=0;i < 5000005;i++)
	{
		if(name_proc[i][0] != '\0')
		{
			// printf("bakaboi");
			kill(i,SIGKILL);
			name_proc[i][0] = '\0';
			// bgProcCount--;
		}
	}
	return 1;
}
int rsh_jobs(char **args)
{
	int i=0,count=1;
	char Process[1000];
	char status;
    int temp;
	char * temp2;
	for(i=0;i< 5000005;i++)
	{
		if(name_proc[i][0] != '\0')
	  	{
				sprintf(Process, "/proc/%d/stat", i);
			    FILE * stat = fopen(Process, "r");
						
				fscanf(stat, "%d %s %c",&temp,&temp2, &status);
				if(status == 'T')
			  		printf("[%d] Stopped %s %d\n", count, name_proc[i], i);
			    else 
			  		printf("[%d] Running %s %d\n", count, name_proc[i], i);
				count++;
		}
	}
	return 1;
}
int rsh_kjob(char **args)
{
	int job_number=atoi(args[1]);
	int count=0,i=0;
	for(i=0;i<5000005;i++)
	{	
		if(name_proc[i][0] != '\0')
		{
			count++;
		}
		if(count == job_number)
		{
			break;
		}
	} 
	int sig=atoi(args[2]);
	kill(i,sig);
	return 1;
}
int rsh_bg(char **args)
{
	int i=0;
	int count= 0;
	for(i=0;i < 5000005;i++)
	{
		if(name_proc[i][0] != '\0')
		{
			count++;
		}
		if(count == atoi(args[1]))
		{
			break;
		}
	}
	kill(i,SIGCONT);
	name_proc[i][0] = '\0';
	return 1;
}
int rsh_fg(char **args)
{
	int i=0;
	int count= 0;
	for(i=0;i < 5000005;i++)
	{
		if(name_proc[i][0] != '\0')
		{
			count++;
		}
		if(count == atoi(args[1]))
		{
			break;
		}
	}
	kill(i,SIGCONT);
	waitpid(-1,NULL,WUNTRACED);
}


int main(int argc,char **argv)
{	
	rsh_loop();
	return EXIT_SUCCESS;
}