/*
   testeliste.c
   experimentation du type tyListe
 */

#include "liste.h"
#include <stdio.h>

int main()
{
    tyListe donnee; int n;
    int max;
    /*creation d'une liste vide*/
    creer(&donnee);
    afficher(donnee);

    /*remplissage de la liste*/
    ajouter(&donnee, 2);
    ajouter(&donnee, 7);
    ajouter(&donnee, 3);
    ajouter(&donnee, 5);
    ajouter(&donnee, 1);

    /*affichage de la liste*/
    afficher(donnee);
    
    /*Max de la liste*/
    max = maxListe(donnee);
    printf("Le max de la liste est : %d\n",max);
    
    /*suppression de la liste (renvoi le nombre d'elements supprimes)*/
    n = detruire(&donnee);
    printf("%d element(s) supprime(s)\n", n);
    
    afficher(donnee);
    
    return(1);
}

