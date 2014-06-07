#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/resource.h>


int main (int argc,char* argv[])
{
  int taille,i;
  int status;
  struct rusage stats;
  double user, syst;
  pid_t pid;
  
  if (argc < 2)
    {
      printf("Usage : ./EX3 chaine liste_fichier\n");
      return EXIT_FAILURE;
    }
  
  taille = argc - 1;
  
  
  for (i=2; i<= taille ; i++)
    {
      if ((pid = fork()) == 0)
	{
	  execlp("grep","grep",argv[1],argv[i]);
	  perror("FAIL EXEC");
	  exit (EXIT_FAILURE);
	}
    }

  while (wait3(&status,0,&stats) != -1)
    {
      printf("\n Fils : %ld\n",pid);
      
      user = stats.ru_utime.tv_sec*1000000+stats.ru_utime.tv_usec;
      syst = stats.ru_stime.tv_sec*1000000+stats.ru_stime.tv_usec;
            
      printf("Temps utilisateur : %f µs\n",user);
      printf("Temps systeme : %f µs\n\n",syst);
    }
  
  printf("Pere\n");

  return EXIT_SUCCESS;
}
