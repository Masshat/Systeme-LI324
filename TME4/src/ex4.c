#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main ()
{
  pid_t child_pid;
  int i=0;

  while (i < 2)
    {
      /* Crée un processus fils. */
      child_pid = fork ();
      
      if (child_pid > 0) {
	/* Nous sommes dans le processus parent. Attente 10 secondes. */
	sleep (10);
      }
      else {
	/* Nous sommes dans le processus fils. Sortie immédiate. */
	exit (0);
      }
      
      i++;
    }
  
  return 0;
}
