# Mettre dans SCHEDPATH le repertoire ou se trouve libsched.a
# et sched.h
SCHEDPATH = /Infos/lmd/2005/licence/ue/li324-2006fev/libsched/src 

CFLAGS = -Wall -I$(SCHEDPATH) -m32

all: main scen test_sch

main: main.o 
	gcc $(CFLAGS) -o main main.o -L$(SCHEDPATH) -lsched -L$(SCHEDPATH) -lelf 


scen: scen.o 
	gcc $(CFLAGS) -o scen scen.o -L$(SCHEDPATH) -lsched -L$(SCHEDPATH) -lelf 

test_sch: test_sch.o
	gcc $(CFLAGS) -o test_sch test_sch.o -L$(SCHEDPATH) -lsched -L$(SCHEDPATH) -lelf

main.o: main.c
	gcc $(CFLAGS) -c main.c

scen.o: scen.c
	gcc $(CFLAGS) -c scen.c

test_sch.o : test_sch.c
	gcc $(CFLAGS) -c test_sch.c

clean: 
	rm -f main main.o scen scen.o test_sch test_sch.o
