#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXFILS 2 /*Nombre de fils que le pere peut cree*/

int main (int argc,char* argv[])
{
  int taille,i;
  
  if (argc < 2)
    {
      printf("Usage : ./EX2 chaine liste_fichier\n");
      return EXIT_FAILURE;
    }

  taille = argc - 1;
   
  for (i=2; i<= taille ; i++)
    {
      if (i >= MAXFILS+2) 
	{
	  wait(NULL);
	  printf("Attente ...\n");
	  sleep (1);
	}

      if (fork() == 0)
	{
	  execlp("grep","grep",argv[1],argv[i]);
	  perror("FAIL EXEC");
	  exit (EXIT_FAILURE);
	}
    }

  
  /*Pere*/
  while (wait(0) != -1);
  printf("Pere\n");

  return EXIT_SUCCESS;
}
