#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define MAX 35

void 
stc(int *pp, int array[], int arlen) 
/* send array to child process */  
{
  int i;

  close(pp[0]);
  for(i=0; i<arlen; i++)
    write(pp[1], array+i, sizeof(int));
  close(pp[1]);
}

int *
filter(int prime, int rfd, int *nlen)
{
  int n = 0;
  int * narray;

  *nlen = 0; 
  narray = (int *) malloc(MAX * sizeof(int));
  
  do{
    n = read(rfd, narray+(*nlen), sizeof(int));
    if(narray[*nlen] % prime != 0 && n > 0)
      (*nlen)++;
  } while(n>0);

  return narray;
}

void
cproc(int rfd)
/* child process */
{
  int n;
  int prime;
  int nlen;     /* filtered array's len */
  int *narray;  /* filtered array's address */
  int pp[2];  /* new pipe */
  int pid;

  n = read(rfd, &prime, sizeof(int));
  if(n == 0)
    exit(0); /* prime filter finished */
  else
    printf("prime %d\n", prime);
  
  narray = filter(prime, rfd, &nlen);

  pipe(pp);
  pid = fork();
  if(pid > 0){
    stc(pp, narray, nlen);
    wait(0);
    exit(0); // need exit ?
  } else{
    close(pp[1]);
    cproc(pp[0]);
  }
}

int 
main(int argc, char *argv[])
{
  int pid;
  int p[2];       /* pipe */
  int array[MAX-1];

  pipe(p);
  pid = fork();

  int i;
  if(pid > 0){
    /* init array */
    for(i=2; i<=MAX; i++)
      array[i-2] = i;
    stc(p, array, MAX-1);
    wait(0);
  } else{
    close(p[1]);
    cproc(p[0]);
  }
  exit(0);
}
