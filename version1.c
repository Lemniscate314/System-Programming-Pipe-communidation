/**MBOUP Issa*

/**version1*/
/** Each childreceives 2 terminals from a sub-interval in which it searches for prime numbers and displays them
on the screen*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <string.h>
#define MaxBuffer 64
char res[20000];
  int BORNER[2000];
char BUFFER[MaxBuffer];
int est_premier(int n)
{
  int i;
  if(n<2) return 0;
  if(n==2) return 1;
  if(n%2==0) return 0;
  for(i=3;i*i<n;i=2+i)
    if(n%i==0) return 0;
  return 1;

}
int main(int argc, char **argv)
{
  
  pid_t pid;
  int pip[10][2];/** 10 communication tubes connecting the father to each child*/
  int *status;
  
  int lu,j,len;
  
  for(int i=0;i<10;i++)
    {
      if(pipe(pip[i])==-1) /**Création du tube*/
	{
	  perror("Erreur dans la création tube");
	  exit(1);
        }
      
      pid = fork();/**Create the ith child process*/
      
      if(pid==-1)
	{
	  perror("Erreur");
	  exit(1);
	}
      
      if(pid ==0)
	{
	  close(pip[i][1]);
	  int red = read(pip[i][0],BORNER,sizeof(int));
	  for(j = *BORNER;j<*BORNER+200;j++)
      	  
	    if(est_premier(j)==1)
	      {
		len = sprintf(res,"%d",j);
		write(1,"\t",strlen("\t"));
		write(1,res,len);   
		
	      }
	  exit(0);
	}
      
      else
	{
	  close(pip[i][0]);
	  *BORNER = 200*i; /
/** We send only one terminal and the child deduces the second one*/
	  write(pip[i][1],BORNER,sizeof(int));
	  close(pip[i][1]);	      
	  waitpid(pid, status,0);
	  
	}
    }
	  
          
  
}
