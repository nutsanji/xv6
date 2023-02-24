#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc, char *argv[])
{
  int pid;
  int pp[2];  //parent pipe
  int cp[2];  //child pipe
  char buffer[4];

  pipe(pp);
  pipe(cp);
  pid = fork();

  if(pid > 0){
    write(pp[1], "ping", 4);
    close(pp[1]);

    wait(0);
    read(cp[0], buffer, 4);
    close(cp[0]);
    printf("%d: received pong\n", getpid());
  } else{
    read(pp[0], buffer, 4);
    close(pp[0]);
    printf("%d: received ping\n", getpid());

    write(cp[1], "pong", 4);
    close(cp[1]);
  }

  exit(0);
}

