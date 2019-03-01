## RUNNING

- run "make"

- execute by using "./rsh"

- type "exit" to exit the shell

## FEATURES

#### ls command
###### Usage:
- ls takes arguments as flags (in the form -(flagname)).
- If there is no directory mentioned, it lists the files of current directory

* "ls" - lists in alphabetical order
* "ls -a" - display hidden files
* "ls -l" - long list
* "ls -al"/"ls -la" - long list including hidden files

- Similarities to real command: "ls -a" displays files sorted in alphabetical order (NOT CONSIDERING THE PREPENDED '.')  

#### cd command
* "cd (absolute path)" - goes to absolute path
* "cd" - goes to ~/
* "cd ~/(pathname)" - goes to ~/(pathname)
* "cd .." - goes to previous directory
* "cd ." - goes to same directory

#### echo command
* "echo text" - prints "text"
* "echo 'text' " - prints "text"

#### pwd command
* "pwd" - prints absolute path of present working directory

#### pinfo command
* "pinfo" : prints the process related info of the shell program 
* "pinfo <pid>" : prints the process info about given pid
- pid -- 
- Process status -- {R/S/S+/Z}
- Memory
- Executable path -- (Absolute path - includes ~/ if executable is present inside the shell directory)
   
#### piping,redirection,setenv,unsetenv,bg,fg,overkill,kjob,jobs,quit.
# cShell
