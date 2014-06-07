/*
   liste.h
   interface (header) du type tyListe
*/

/*le type des elements de liste*/
struct sElem 
{
    int valeur;
    struct sElem* suiv;
    struct sElem* prec;
};

typedef struct sElem* tyPtrElem;

/*le type Liste*/
struct sListe 
{
      tyPtrElem tete;
      tyPtrElem fin;
};

typedef struct sListe tyListe;


/*creer : tyListe* -> void*/
/*creer (&l) initialise l a la liste vide*/
void creer(tyListe *liste);

/*detruire : tyListe* -> int
detruire (&l) desalloue chaque element de l,
              reinitialise l a la liste vide,
              et renvoie le nombre d'elements detruits*/
int detruire(tyListe *liste);

/*ajouter : tyListe* + int -> void
//ajouter (&l, v) alloue un nouvel element avec la valeur v,
//                ce nouvel element est accroche en tete de l*/
void ajouter(tyListe *liste, int valeur);

/*afficher : tyListe -> void
//afficher(l) affiche tous les elements de l a partir du premier*/
void afficher(tyListe liste);

/*afficher2 : tyListe -> void
//afficher2(l) affiche tous les elements de l a partir du dernier
//void afficher2(tyListe liste);*/


/*Calcul le max de la liste donnee en argument*/
int maxListe (tyListe liste);
