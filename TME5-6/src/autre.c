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

// A completer
#define EMET 0
#define RECEPT1 1
#define RECEPT2 2
#define RECEPT3 3
#define RECEPT4 4
#define RECEPT5 5
#define NBRECEPT 6

/************************************************************/

/* definition de la memoire partagee */ 

// A completer
typedef struct {
  int a;
} t_segpart;
t_segpart *nb_recepteurs , *buffer; /* Pointeur sur le segment */

/************************************************************/

/* variables globales */ 
int emet_pid[NE], recep_pid[NR]; 

/************************************************************/

/* traitement de Ctrl-C */ 

void handle_sigint(int sig) { 
  int i;
  for (i = 0; i < NE; i++) kill(emet_pid[i], SIGKILL); 
  for (i = 0; i < NR; i++) kill(recep_pid[i], SIGKILL); 
  det_sem(); 
  det_shm((char *)nb_recepteurs); 
  det_shm((char *)buffer);
} 

/************************************************************/

/* fonction EMETTEUR */ 

// A completer - contient les instructions executees
// par un emetteur
void emettre (int indice)
{
  int i,j;
  for (i=0;;i++)
    {
      P(EMET);
      nb_recepteurs->a = 0;
      printf("EMET n°%d ecrit : %d dans le buffer\n",indice,i+indice);
      buffer->a = i+indice;
      for (j=1; j<=NR;j++) V(j);
    }
}

/************************************************************/

/* fonction RECEPTEUR */ 

// A completer - contient les instructions executees
// par un recepteur

void reception (int indice)
{
  int i;
  for (i=0;;i++)
    {
      P(indice);
      printf("RECEPT  n°%d recoit : %d\n",indice,buffer->a);
      P(NBRECEPT);
      nb_recepteurs->a++;
      printf("Nombre de recepteurs : %d\n",nb_recepteurs->a);
      if (nb_recepteurs->a == NR)
	{
	  nb_recepteurs->a = 0;
	  V(EMET);
	}
      V(NBRECEPT);
    }
}

/************************************************************/

int main() { 
  struct sigaction action;
  /* autres variables (a completer) */
  int semid,i;
    
  setbuf(stdout, NULL);

  /* Creation du segment de memoire partagee */

  // A completer
  if ( (nb_recepteurs = init_shm(sizeof(t_segpart))) == NULL) 
    {
      perror("init_shm");
      exit(1);
    }
  nb_recepteurs->a = 0;
  
  /* creation des semaphores */ 

  // A completer
  if ((semid = creer_sem(NR+2)) == -1) 
    {
      perror("creer_sem");
      exit(1);
    }
 
  /* initialisation des semaphores */ 

  // A completer
  init_un_sem(EMET,1);
  init_un_sem(RECEPT1,0);
  init_un_sem(RECEPT2,0);
  init_un_sem(RECEPT3,0);
  init_un_sem(RECEPT4,0);
  init_un_sem(RECEPT5,0);
  init_un_sem(NBRECEPT,1);

  /* creation des processus emetteurs */ 
  for (i=0; i < NE ;i++)
    {
      if ((emet_pid[i] = fork()) == -1)
	{
	  perror("fork");
	  exit(0);
	}
      else if (emet_pid[i] == 0)
	{
	  emettre(i);
	}
    }

  // A completer - les pid des processus crees doivent
  // etre stockes dans le tableau emet_pid

  /* creation des processus recepteurs */ 

  // A completer - les pid des processus crees doivent
  // etre stockes dans le tableau recep_pid
  for (i=0; i < NR ;i++)
    {
      if ((recep_pid[i] = fork()) == -1)
	{
	  perror("fork");
	  exit(0);
	}
      else if (recep_pid[i] == 0)
	{
	  reception(i+1);
	}
    }

  /* redefinition du traitement de Ctrl-C pour arreter le programme */ 

  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  action.sa_handler = handle_sigint;
  sigaction(SIGINT, &action, 0); 
    
  pause();                    /* attente du Ctrl-C  */
  return EXIT_SUCCESS;
} 
