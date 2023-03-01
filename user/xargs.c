#include "kernel/types.h"
#include "kernel/param.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MAX 512

void xargs(char * cmd[])
{
  int pid;

  pid = fork();
  if(pid > 0)
    wait(0);
  else{
    exec(cmd[0], cmd);
  }
}

int
main(int argc, char *argv[])
{
  int i;
  char buf;
  char *p;
  char *cmd[MAXARG];
  char param[MAX];
  
  for(i = 1; i < argc; i++)
    cmd[i-1] = argv[i];
  
  p = param;
  while(read(0, &buf, sizeof(char))){
    if(buf != '\n')
      *p++ = buf;
    else{
      *p = '\0';
      p = param;
      cmd[argc-1] = param;
      xargs(cmd);
    }
  }
  exit(0);
}


