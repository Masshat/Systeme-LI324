#include <stdio.h>                                                             
#include <stdlib.h>                                                            
#include <unistd.h>                                                            
#include <malloc.h>                                                            
#include <limits.h>                                                            
#include <sched.h>                                                             
                                                                               
void ProcLong(int *);                                                          
void ProcCourt(int *);                                                         
                                                                               
// Exemple de processus long (une simple bouble),                              
// Chaque processus long cr\351e a son tour 4 processus courts                    
//                                                                             
void ProcLong(int *pid) {                                                      
  long i;                                                                      
  static int cpt = 0;                                                          
                                                                               
  for (i=0;i<8E8;i++) {                                                        
    if (i%(long)1E7 == 0)  {                                                   
      int *tcpt = (int *) malloc(sizeof(int));                                 
      *tcpt = cpt;                                                             
      CreateProc((function_t)ProcCourt,(void *)tcpt, 10);                      
      cpt++;                                                                   
    }                                                                          
    if (i%(long)8E6 == 0)                                                      
      printf("Proc. Long %d - %ld\n",*pid, i);                                 
  }                                                                            
  printf("############ FIN LONG %d\n\n", *pid );                               
}                                                                              
                                                                               
                                                                               
// Processus court                                                             
void ProcCourt(int *pid) {                                                     
  long i;                                                                      
                                                                               
  for (i=0;i<8E7;i++)                                                          
    if (i%(long)4E5 == 0)                                                      
      printf("Proc. Court %d - %ld\n",*pid, i);                                
  printf("############ FIN COURT %d\n\n", *pid );                              
}                                                                              
                                                                               
                                                                               
                                                                               
// Exemples de primitive d'election definie par l'utilisateur                  
// Remarques : les primitives d'election sont appel\351es directement             
//             depuis la librairie. Elles ne sont app\351l\351es que si au           
//             moins un processus est \340 l'etat pret (RUN)                      
//             Ces primitives manipulent la table globale des processus        
//             d\351finie dans sched.h                                            
                                                                               
                                                                               
// Election al\351atoire                                                          
int RandomElect(void) {                                                        
  int i;                                                                       
                                                                               
  printf("RANDOM Election !\n");                                               
                                                                               
  do {                                                                         
    i = (int) ((float)MAXPROC*rand()/(RAND_MAX+1.0));                          
  } while (Tproc[i].flag != RUN);                                              
                                                                               
  return i;                                                                    
}                                                                              
                                                                               
                                                                               
// Election de SJF "Shortest Job Fisrt"                                        
int SJFElect(void) {                                                           
  int p, i;                                                                    
  double min_duration;                                                         
                                                                               
  for(i=0; i<MAXPROC; i++)                                                     
	if(Tproc[i].flag == RUN)                                                      
	{                                                                             
		min_duration = Tproc[i].duration;                                            
		p = i;                                                                       
		break;                                                                       
	}                                                                             
                                                                               
  for(i=p+1; i<MAXPROC; i++)                                                   
	if(Tproc[i].flag == RUN && min_duration > Tproc[i].duration)                  
	{                                                                             
		min_duration = Tproc[i].duration;                                            
		p = i;                                                                       
	}                                                                             
                                                                               
  return p;                                                                    
}                                         

int ApproxSJF (void)
{
  int p,i,max;

  p=GetElecProc();

  Tproc[p].prio -= 5;

  if (Tproc[p].prio < MINPRIO) {Tproc[p].prio = MINPRIO;}

  for(i=0; i<MAXPROC; i++)
    if(Tproc[i].flag == RUN)
      {
	max = Tproc[i].prio;
	p = i;
	break;
      }

  for(i=p+1; i<MAXPROC; i++)
    if(Tproc[i].flag == RUN && max < Tproc[i].prio)
      {
	max = Tproc[i].prio;
	p = i;
      }

  return p;
}
                     
int main (int argc, char *argv[]) {
  int i;
  int *j;  

  // Créer les processus long
  for  (i = 0; i < 2; i++) {
    j = (int *) malloc(sizeof(int));
    *j= i;
    CreateProc((function_t)ProcLong,(void *)j, 80);
  }

  // Definir une nouvelle primitive d'election sans quantum (batch)
  //SchedParam(NEW, 0, SJFElect);
  SchedParam(NEW, 1, ApproxSJF);

  // Lancer l'ordonnanceur en mode non "verbeux"
  sched(0);	

  // Imprimer les statistiques
  PrintStat();

  return EXIT_SUCCESS;

}

