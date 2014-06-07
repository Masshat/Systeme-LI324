/*
  liste.c
  implementation des fonctions du type tyListe
  declare dans le fichier liste.h
*/

#include "liste.h"
#include <stdio.h>
#include <stdlib.h>

void creer(tyListe *liste)
{
    liste->tete = NULL;
    liste->fin = NULL;
}

void ajouter(tyListe *liste, int valeur)
{
  tyPtrElem nouveau = (tyPtrElem) malloc(sizeof(tyPtrElem*));

  nouveau->valeur = valeur ;
  nouveau->suiv = liste->tete ;
  nouveau->prec = NULL ;

  if (liste->tete == NULL)
    liste->tete = liste->fin = nouveau ;
  else
  {
    liste->tete->prec = nouveau ;
    liste->tete = nouveau ;
  }
}

void afficher(tyListe liste)
{ 
  tyPtrElem ptrTmp = liste.tete;

  while (ptrTmp != NULL)
  {
    printf("%d ",ptrTmp->valeur);
    ptrTmp = ptrTmp->suiv;
  }
  printf("\n");
}

int detruire(tyListe *liste)
{ 
  tyPtrElem poubelle;
  int i = 0;
  
  while (liste->fin != NULL)
  {
      poubelle = liste->fin;
      liste->fin = poubelle->prec;
      free(poubelle);
      i++;
  }
  
  liste->tete = NULL;
  
  return i;
}

int maxListe (tyListe liste)
{
  tyPtrElem elem=liste.tete;
  int max=0;

  while (elem != NULL)
    {
      if( max < elem->valeur ) 
	{
	  max = elem->valeur;
	}
      elem = elem->suiv;
    }
  
  return max;
}
