/* Diffusion tampon 1 case */

#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <signal.h> 
#include <libipc.h>

/************************************************************/

/* definition des parametres */ 

#define NE          2     /*  Nombre d'emetteurs         */ 
#define NR          5     /*  Nombre de recepteurs       */ 

/************************************************************/

/* definition des semaphores */ 
#define REC {0,0,0,0,0}
#define EMET 5
#define NBR 6
// A completer
        
/************************************************************/

/* definition de la memoire partagee */ 
typedef struct
{
  int a;
  int nbrecep;
} t_segpart;
t_segpart *sp;
// A completer

/************************************************************/

/* variables globales */ 
int emet_pid[NE], recep_pid[NR]; 
int tab_sem_rec[NR]=REC; 

/************************************************************/

/* traitement de Ctrl-C */ 

void handle_sigint(int sig) { 
  int i;
  for (i = 0; i < NE; i++) kill(emet_pid[i], SIGKILL); 
  for (i = 0; i < NR; i++) kill(recep_pid[i], SIGKILL); 
  det_sem(); 
  det_shm((char *)sp); 
} 

/************************************************************/

/* fonction EMETTEUR */ 

// A completer - contient les instructions executees
// par un emetteur
void emet_f(int i)
{
  int value=0;
  int recep=0;
  while(1)
    {
      P(EMET);
      sp->a=value;
      printf("emet %d **** ecris %d et libire recepA\n",i,value);
      sp->nbrecep=5;
      while(recep!=NR)
	{
	  V(recep);
	  recep++;
	}
      recep=0;
      sleep(1);
      value++;
    }
}



/************************************************************/

/* fonction RECEPTEUR */ 

void recep_f(int i)
{
  int value=0;
  sleep(2);
  
  while(1)
    {
      P(i);
      value=sp->a;
      printf("recep %d **** lit %d\n",i,value);
      P(NBR);
      sp->nbrecep--;
      if(sp->nbrecep==0)
	V(EMET);
      V(NBR);
      sleep(1);
    }
}
// A completer - contient les instructions executees
// par un recepteur

/************************************************************/

int main()
{ 
  struct sigaction action;
  /* autres variables (a completer) */
  int semid;
  setbuf(stdout, NULL);

  /* Creation du segment de memoire partagee */
  if((sp=(t_segpart *)init_shm(sizeof(t_segpart))) == NULL)
    {
      perror("init_shm");
      exit(1);
    }
  // A completer

  /* creation des semaphores */ 
  if((semid=creer_sem(2+NR)) == -1)
    {
      perror("creer_sem");
      exit(1);
    }
  // A completer

  /* initialisation des semaphores */ 
  int i=0;
  while(i!=NR)
    {
      init_un_sem(i,0);
      i++;
    }
  init_un_sem(EMET,1);
  init_un_sem(NBR,1);
  // A completer
  sp->a=-1;
  /* creation des processus emetteurs */ 
  i=0;
  while(i!=NE)
    {
      if((emet_pid[i]=fork())==-1)
	{
	  perror("fork");
	  exit(2);
	}
      if(emet_pid[i]==0)
	{
	  emet_f(i);
	}
      i++;
    }
  // A completer - les pid des processus crees doivent
  // etre stockes dans le tableau emet_pid

  /* creation des processus recepteurs */ 

  i=0;
  while(i!=NR)
    {
      if((recep_pid[i]=fork())==-1)
	{
	  perror("fork");
	  exit(2);
	}
      if(recep_pid[i]==0)
	{
	  recep_f(i);
	}
      i++;
    }
  // A completer - les pid des processus crees doivent
  // etre stockes dans le tableau recep_pid
  /* redefinition du traitement de Ctrl-C pour arreter le programme */ 
  
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  action.sa_handler = handle_sigint;
  sigaction(SIGINT, &action, 0);
  pause();                    /* attente du Ctrl-C  */
  return EXIT_SUCCESS;
} 
