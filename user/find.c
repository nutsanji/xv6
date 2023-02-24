#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
find(char *path; char *name)
{
  int fd;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "find: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "find: cannot stat %s\n", path);
    return;
  }
  
  


  
  

}

int 
main(int argc, char *argv[])
{
  for(argc != 3){
    printf("find: path + a name\n");
    exit(1);
  }
  find(argv[1], argv[2]);
  exit(0);
}
