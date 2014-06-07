#ifndef AFFICHE_TAS_H
#define AFFICHE_TAS_H

/*===================*/
/* Definition du tas */
/*===================*/
#define TAILTAS 127	/* l'indice max et la taille de la plus grande donnee possible */
#define TAILMIN 2	/* le plus petit bloc utilisable */

char tas[TAILTAS+1];
int libre;		/* indice du premier bloc libre dans le tas */

/*===========================*/
/* AFFICHE LE CONTENU DU TAS */
/*===========================*/
void afficher_tas(void);

/*==============================*/
/* INITIALISE LE CONTENU DU TAS */
/*==============================*/
/* quand celui-ci ne contient pas de donnees */
void tas_init(void);

/*===================*/
/* LIBERATION DU TAS */
/*===================*/
void tas_free (char *ptr);

/*====================================*/
/* STRATEGIE DE PLACEMENT : FIRST FIT */
/*====================================*/
int first_fit (int taille, int *pred);

/*=============================================*/
/* IMPLEMENTATION DE LA STRATEGIE DE PLACEMENT */
/*=============================================*/
/* ici first_fit*/
char *tas_malloc (size_t taille);

#endif
