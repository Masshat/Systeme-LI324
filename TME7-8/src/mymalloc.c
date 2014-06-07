#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "affiche_tas.h"

int main()
{
  /*initialisation du tas*/
  tas_init();
  
  /*affichage du tas*/
  afficher_tas();
  
  char *c1,*c2,*c3,*c4;
  
  /*ECRITURE EN MEMOIRE*/
  if((c1=tas_malloc(10))==NULL) {printf("ERROR\n");}
  strcpy(c1,"tp1");
  
  if((c2=tas_malloc(9))==NULL)  {printf("ERROR\n");}
  strcpy(c2,"tp2");
  
  if((c3=tas_malloc(5))==NULL)  {printf("ERROR\n");}
  strcpy(c3,"tp3");
  
  /*affichage du tas*/
  afficher_tas();

  /*liberation de la variable c2 et affichage du tas*/
  tas_free(c2);
  afficher_tas();
  
  /*ECRITURE EN MEMOIRE*/
  if((c4=tas_malloc(8))==NULL)  {printf("ERROR\n");}
  strcpy(c4,"systeme");
  
  /*affichage du tas*/
  afficher_tas();
  
  return EXIT_SUCCESS;
}
