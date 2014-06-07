#include "Fifo.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int initFifo(Swapper*);
unsigned int fifoChoose(Swapper*);
void fifoReference(Swapper*,unsigned int frame);
void finalizeFifo(Swapper*);

int initFifoSwapper(Swapper*swap,unsigned int frames)
{
  return initSwapper(swap,frames,initFifo,NULL,fifoChoose,finalizeFifo);
}

int initFifo(Swapper*swap)
{
  /* A ecrire en TME */
  
  swap->private_data = (int *) malloc(sizeof (int));
  *((int *)(swap->private_data)) = 0;
  
  return EXIT_SUCCESS;
}

unsigned int fifoChoose(Swapper*swap)
{
  /* A ecrire en TME */
  
  int i = 0;
  
  while (i<swap->frame_nb)
    {
      if (swap->frame[i] == -1) { return i; }
      i++;
    }
  
  *((int *)(swap->private_data)) = *((int *)(swap->private_data))+1;
  
  if (*((int *)(swap->private_data)) == swap->frame_nb+1) { *((int *)(swap->private_data)) = 1; }
  
  return *((int *)(swap->private_data))-1;
}

void finalizeFifo(Swapper*swap)
{
  /* A ecrire en TME */
  
  free(swap->private_data);
  /*return;*/
}
