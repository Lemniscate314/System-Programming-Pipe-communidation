/**MBOUP Issa*/

/**version2*/
/** Each son receives 2 terminals of a sub-interval in which it searches for the prime numbers and displays them
on the screen*/
/** Our way of proceeding is such as we do not distribute not two bounds but only one, it is thus with the son process to deduce the second one
We distribute only the lower bound 
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <string.h>
#define MaxBuffer 2000
char res[2000];
char *end ="|";
  int BORNER[2000];
char BUFFER[MaxBuffer];
char *fin = " 997 ";
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
int contient (char *ch1, char *ch2)/**This function allows you to check if a string is contained in another string */
{
 for(int i = 0; i<strlen(ch2)+1;i++)
   {
     for(int i = 0; i<strlen(ch2);i++)
       if(ch1[i]!=ch2[i]) break;
     continue;
     if(i == strlen(ch2)) return 0;
   }
  return 1;
}
	      
int main(int argc, char **argv) // p the number of processes and n the number of intervals
{
  
  pid_t pid;
  /** 10 communication pipes connecting the father to each son*/
  int *status;;
  int lu,j,len;
  int n=10;
  int p = 10;
  int m;
  int tmp = (int)((1000/n)*p);
  printf("Please indicate the number of processes:");
  scanf("%d",&p);
  printf("Please indicate the number of divisions of the interval: ");
  scanf("%d",&n);
  int pip[2*p][2];
  m = p;
  int tab[n];//** This array contains all our lower bounds*/
  for(int i =0;i<n;i++) tab[i] = (1000/n)*i;
  
  int COUNTER  =n/p;
  
  for(int i=0;i<p;i++)
    {
      if(pipe(pip[i])==-1 || pipe(pip[10+i])==-1) /**Creation of the pipe*/
	{
	  perror("Error in pipe creation");
	  exit(1);
        }
      
      pid = fork();/**Creation of the ith child process**/
     
      if(pid==-1)
	{
	  perror("Error");
	  exit(1);
	}
      if(pid ==0)
	{
	  close(pip[i][1]);
	  close(pip[i+10][0]);
	  int red;
	  while((red= read(pip[i][0],BORNER,sizeof(int)))!=0)
	    {
	      if(*BORNER == -1) break;
	      for(j = *BORNER;j<(*BORNER + (int) 1000/n) ;j++)
		if(est_premier(j)==1)
		  {
		     write(pip[i+10][1],"\t",strlen("\t"));
		    
		    len = sprintf(res,"%d",j);
		   
		    write(pip[i+10][1],res,len);
		    if(j==997) exit(0);
	
	           } 
	      
	     
	      char *fini = "|";
	       write(pip[i+10][1],fini,len);
	      
	    
	    }
         
	 close(pip[i][0]);
	  close(pip[i+10][1]);

	 
	}
      else 
	{
	  close(pip[i][0]);
	  close(pip[i+10][1]);
	  *BORNER =(1000/n)*i;/** we first send a bound to each child*/
	  if(*BORNER > 1000) break;
	  
	  write(pip[i][1],BORNER,sizeof(int));
	  
	  if(i== p-1)
	     while(1)
	        {
		  COUNTER = p;
                   for(int j = 0; i<p;j++)
		     {
		       int lu;
		       if(( lu = read(pip[j+10][0],BUFFER,2000))!=0)
			 {
			   write(1,BUFFER,lu);
			   
		       
		       if(contient(BUFFER,end))
			 {
			   if(m==n)
			     {
			        *BORNER = -1;
	                         write(pip[j][1],BORNER,sizeof(int));
		                 waitpid(pid, status,0);
	                         close(pip[j][1]);
	                         close(pip[j+10][0]);
	                         exit(0);
			     }
			   else
			     {
			       COUNTER++;
		               *BORNER = tab[m];
	                        write(pip[j][1],BORNER,sizeof(int));
		                m = m+1;
		             }
		  
		         }
		      
			 }
		       
			   break;
			 
	     
        
	    
                    }
    
	  
	  
 
	 
	}
    }
  
      
    }
  
}
