#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <sys/time.h>
#include <unistd.h>

#define TICK ((double)sysconf(_SC_CLK_TCK))

/* ============================================================
   Donne le temps en micro-secondes de la commance en parametre
   ============================================================
*/
void lance_commande1 (char *commande)
{
  int time_exec;

  struct timeval debut, fin;
  gettimeofday(&debut,NULL);
  system(commande);
  gettimeofday(&fin,NULL);

  time_exec = (fin.tv_sec-debut.tv_sec) + (fin.tv_usec-debut.tv_usec)*0.000001;

  printf("La commande %s a mis %d (micro-secondes) pour s'executée\n",commande,time_exec);
}

/* ===============================================================================
   Donne le temps en secondes de la commance en parametre (beaucoup plus detaille)
   ===============================================================================
*/
void lance_commande2 (char *commande)
{
  struct tms debut, fin;
  clock_t debut_tot,fin_tot;
  double user,syst,user_fils,system_fils,total;
  
  debut_tot = times(&debut);
  system(commande);
  fin_tot = times(&fin);
  
  user = (double)(fin.tms_utime - debut.tms_utime)/TICK;
  syst = (double)(fin.tms_stime - debut.tms_stime)/TICK;
  user_fils = (double)(fin.tms_cutime - debut.tms_cutime)/TICK;
  system_fils = (double)(fin.tms_cstime - debut.tms_cstime)/TICK;
  total = (fin_tot - debut_tot)/TICK;
  
  printf("\nStatistiques de : %s \n",commande);
  printf("Temps total : %f \n",total);
  printf("Temps utilisateur : %f\n",user);
  printf("Temps systeme : %f\n",syst);
  printf("Temps utils. fils : %f\n",user_fils);
  printf("Temps sys. fils : %f\n",system_fils);
}

/* ==================================
   MAIN (execution de lance_commande2
   ==================================
*/
int main (int argc, char **argv)
{
  int i;
  
  for (i=1; i < argc; i++)
    {
      lance_commande2(argv[i]);
    }
  
  return EXIT_SUCCESS;
}
