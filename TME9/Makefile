#LIBPATH=/Infos/lmd/2005/licence/ue/li324-2006fev/libmem
LIBPATH=./libmem
INC=$(LIBPATH)/include
CC=gcc
CFLAGS=-Wall -D_DEBUG_  # Commenter cette ligne pour desactiver les affichages 
STRATEGIES=LRU. Fifo.  # Liste des strategies

all: mainFifo mainLRU

algorithm:$(STRATEGIES)

%.:
	$(CC) $(CFLAGS) -c $@c -I$(INC) -o $@o

mainLRU: LRU.
	$(CC) $(CFLAGS) -I$(INC) $@.c *.o -o $@ -L$(LIBPATH)/lib -lmem

mainFifo: Fifo.
	$(CC) $(CFLAGS) -I$(INC) $@.c *.o -o $@ -L$(LIBPATH)/lib -lmem

.PHONY: all prope clean run1 run2

proper:	
	rm -f *~

clean: proper
	rm -f *~ *.o mainLRU mainFifo 

run1:	
	./mainFifo < bench

run2:
	./mainLRU < bench
