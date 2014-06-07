/* Diffusion tampon N case */

#include <stdio.h> 
#include <unistd.h> 
#include <signal.h> 
#include <libipc.h>

/************************************************************/

/* definition des parametres */ 

#define NE          2     /*  Nombre d'emetteurs         */ 
#define NR          5     /*  Nombre de recepteurs       */ 
#define NMAX        3     /*  Taille du tampon           */ 

/************************************************************/

/* definition des semaphores */ 

// A completer

#define EMET 8 
#define REC {0,1,2,3,4} /*NR*/
#define NBR {5,6,7} /*NBR*/
#define MUTEXE 9
#define NBRSEM 10

/************************************************************/

/* definition de la memoire partagee */ 

// A completer

typedef struct
{
  int a[NMAX];
  int nbrecep[NMAX];
  int ie;
} t_segpart;
t_segpart *sp;

/************************************************************/

/* variables globales */ 
int emet_pid[NE], recep_pid[NR]; 
int tab_r[NR]=REC;
int tab_nbr[NMAX]=NBR;

/************************************************************/

/* traitement de Ctrl-C */ 

void handle_sigint(int sig) 
{ int i;
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
  int recep=0;
  int ie;
  
  while(1)
    {
      P(EMET);
      
      P(MUTEXE);
      ie=sp->ie;
      sp->ie=(sp->ie+1)%NMAX;
      V(MUTEXE);
      (sp->a)[ie]++;
      printf("#== EMET : %d => T%d = Value (%d) ==#\n",i,ie,sp->a[ie]);
      sp->nbrecep[ie]=NR;
      while(recep!=NR)
	{
	  V(tab_r[recep]);
	  recep++;
	}
      recep=0;
      sleep(1);
    }
}

/************************************************************/

/* fonction RECEPTEUR */ 

// A completer - contient les instructions executees
// par un recepteur
void recep_f(int i)
{
  int value=0;
  int ir=0;
  
  while(1)
    {
      P(tab_r[i]);
      value=sp->a[ir];
      printf("RECEP %d => Value (%d) = T%d\n",i,value,ir);
      ir=(ir+1)%NMAX;
      P(tab_nbr[ir]);
      sp->nbrecep[ir]--;
      
      if(sp->nbrecep[ir]==0)
	V(EMET);
      V(tab_nbr[ir]);
      sleep(1);
    }
}

/************************************************************/

int main() 
{ 
  struct sigaction action;
  /* autres variables (a completer) */
  int semID,i;
  setbuf(stdout, NULL);

  /* Creation du segment de memoire partagee */

  // A completer
  if ( (sp=(t_segpart *)init_shm(sizeof(t_segpart))) == NULL)
    {
      perror("ERROR : init_shm");
      return EXIT_FAILURE;
    }

  /* creation des semaphores */ 

  // A completer
  if ( (semID = creer_sem(NBRSEM)) == -1)
    {
      perror("ERROR : creer_sem");
      return EXIT_FAILURE;
    }

  /* initialisation des semaphores */ 
    
  // A completer
  i=0;

  /*recepteur*/
  while(i!=NR)
    {
      init_un_sem(i,0);
      i++;
    }

  /*compteur par case : NBR*/
  while(i!=NR+NMAX)
    {
      init_un_sem(i,1);
      i++;
    }

  /*emet init a n case*/
  init_un_sem(EMET,NMAX);
  init_un_sem(MUTEXE,1);
  
  i=0;
  while(i!=NR)
    {
      sp->a[i] = -1;
      sp->nbrecep[i] = -1; 
      i++;
    }
  sp->ie = 0;

  /* creation des processus emetteurs */ 

  // A completer - les pid des processus crees doivent
  // etre stockes dans le tableau emet_pid
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
  
  /* creation des processus recepteurs */ 

  // A completer - les pid des processus crees doivent
  // etre stockes dans le tableau recep_pid
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
  
  /* redefinition du traitement de Ctrl-C pour arreter le programme */ 

  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  action.sa_handler = handle_sigint;
  sigaction(SIGINT, &action, 0); 

  pause();                     /* attente du Ctrl-C */
  return EXIT_SUCCESS;
} 
