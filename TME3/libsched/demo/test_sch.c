#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <sched.h>


/* Fonction utilisateur*/
void MonProc(int *pid) {
  long i;
  for (i=0;i<8E7;i++)
    if (i%(long)4E6 == 0)
      printf("%d - %ld\n",*pid, i);
  printf("############ FIN PROC %d\n\n", *pid );
}


int RandomElect(void) 
{
  int i;
  
  printf("RANDOM Election !\n");
  
  do 
    {
      i = (int) ((float)MAXPROC*rand()/(RAND_MAX+1.0));
    } while (Tproc[i].flag != RUN);
  
  return i;
}


int main (int argc, char *argv[]) 
{
  int i;
  int *j;
  
  /* Créer 3 processus*/
  for (i = 0; i < 3; i++) 
    {
      j = (int *) malloc(sizeof(int));
      *j= i;
      CreateProc((function_t)MonProc,(void *)j, 0);
    }
  
  /* Exemples de changement de paramètres
  /* Définir une nouvelle primitive d'election avec un quantum de 2 secondes*/
  SchedParam(NEW, 10, RandomElect);
  
  /* Redéfinir le quantum par defaut*/
  SchedParam(PREMPT, 10, NULL);
  
  /* Passer en mode batch*/
  SchedParam(BATCH, 0, NULL);
  
  /* Lancer l'ordonnanceur en mode non "verbeux"*/
  sched(0);
  
  /* Imprimer les statistiques*/
  PrintStat();
  
  return EXIT_SUCCESS;
}
