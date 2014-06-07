#include "LRU.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	initLRU(Swapper*);
void	referenceLRU(Swapper*,unsigned int frame);
unsigned int chooseLRU(Swapper*);
void	finalizeLRU(Swapper*);

typedef struct {
	unsigned int clock;
	unsigned int * age;
} InfoLRU;

InfoLRU *LRUref;

int initLRUSwapper(Swapper*swap,unsigned int frames){
 return	initSwapper(swap,frames,initLRU,referenceLRU,chooseLRU,finalizeLRU);
}

int initLRU(Swapper*swap)
{
  /* A ecrire en TME */
  int i=0;
  LRUref = (InfoLRU *) malloc(sizeof(InfoLRU)*swap->frame_nb);
  
  while (i != swap->frame_nb)
    {
      LRUref[i].clock = 0;
      LRUref[i].age = (unsigned int *) malloc(sizeof(unsigned int));
      *(LRUref[i].age) = 0;
      i++;
    }
  
  return EXIT_SUCCESS;
}

void referenceLRU(Swapper*swap,unsigned int frame)
{
  /* A ecrire en TME */
  return;
}

unsigned int chooseLRU(Swapper*swap)
{
  /* A ecrire en TME */
  int i=0;
  int ref=9999;

  while (i<swap->frame_nb)
    {
      LRUref[i].clock++;
      if (swap->frame[i] == -1) { ref = i; }
      i++;
    }
  
  if (ref != 9999)
    {
      *(LRUref[ref].age) = LRUref[ref].clock;
      return ref;
    }
  
  /*Remise a zero*/
  i=0;
  ref=0;
  
  while (i<swap->frame_nb)
    {
      if (*(LRUref[ref].age) > *(LRUref[i].age)) { ref = i; } 
      i++;
    }
  
  *(LRUref[ref].age) = LRUref[ref].clock;
  
  return ref;
}

void finalizeLRU(Swapper*swap)
{
  /* A ecrire en TME */
  free(LRUref);
  /*return;*/
}
