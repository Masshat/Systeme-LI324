#include <stdio.h>
#include <ctype.h>

#include "affiche_tas.h"

/*===========================*/
/* AFFICHE LE CONTENU DU TAS */
/*===========================*/
void afficher_tas()
{
  int i, j;
  
  printf("******************\n");
  printf("  AFFICHAGE TAS   \n");
  printf("******************\n");
  
  for (i = 0; i < 8; i++)
    {
      for (j = 0; j < 16; j++) {printf("%4d", j + 16*i);}
      printf("\n");
      for (j = 0; j < 16; j++) {printf("%4d", tas[j + 16*i]);}
      printf("\n");
      for (j = 0; j < 16; j++)
	{ 
	  if (isalnum(tas[j + 16*i])) {printf("%4c", tas[j + 16*i]);}
	  else {printf("    ");}
        }
      printf("\n\n");
    }
  printf("---------------------------------------------------------------\n\n");
}

/*==============================*/
/* INITIALISE LE CONTENU DU TAS */
/*==============================*/
void tas_init()
{
  libre = 0;
  tas[0] = TAILTAS;
  tas[1] = -1;
}

/*===================*/
/* LIBERATION DU TAS */
/*===================*/
void tas_free (char *ptr)
{
  int liberer = libre;
  libre = (ptr-1)-tas;
  tas[libre+1] = liberer;
}

/*====================================*/
/* STRATEGIE DE PLACEMENT : FIRST FIT */
/*====================================*/
int first_fit (int taille, int *pred) /*error == -1*/
{
  int mem = libre;

  while (tas[mem] < taille+1)
    {
      *pred = mem;
      mem = tas[mem+1];
    }

  return mem;
}

/*=============================================*/
/* IMPLEMENTATION DE LA STRATEGIE DE PLACEMENT */
/*=============================================*/
char *tas_malloc (size_t taille)
{
  int pred;
  int p;
  
  p=first_fit(taille,&pred);

  if (p == libre)
    {
      libre += p + taille-1;
      tas[libre] = tas[p] - taille-1;
      tas[libre+1] = tas[p+1];
      tas[p] = taille;
      printf("#== p (libre) : %d ==#\n",p);
    }
  else if (tas[p]-taille < TAILMIN)
    {
      tas[p+taille+1] = tas[p] - taille-1;
      tas[p+taille+2]=tas[p+1];
      tas[pred+1]+=taille+1;
      tas[p]=taille;
      printf("#== Else if : %d ==#\n",p);
    }
  else
    {
      tas[pred+1] = tas[p+1];
      printf("#== Else : %d ==#\n",p);
    }
  
  return &tas[p+1];
}
