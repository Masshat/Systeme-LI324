CC= gcc
CFLAGS= -W -Wall -ansi -g
LDFLAGS= 
SRC= src
INC=
OBJ= obj
BIN= bin

all : directories EX1 EX2 EX3 EX4                     

directories: ${OBJ} ${BIN}

${OBJ}:
	mkdir -p ${OBJ}
${BIN}:
	mkdir -p ${BIN}

# =====
# OBJET
# =====

$(OBJ)/ex1.o : $(SRC)/ex1.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCFLAGS)

$(OBJ)/ex2.o : $(SRC)/ex2.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCFLAGS)

$(OBJ)/ex3.o : $(SRC)/ex3.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCFLAGS)

$(OBJ)/ex4.o : $(SRC)/ex4.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCFLAGS)

# ==========
# EXECUTABLE
# ==========

EX1 : $(OBJ)/ex1.o
	$(CC) $(CFLAGS) -o $(BIN)/$@ $^ $(LDFLAGS)    

EX2 : $(OBJ)/ex2.o
	$(CC) $(CFLAGS) -o $(BIN)/$@ $^ $(LDFLAGS)    

EX3 : $(OBJ)/ex3.o
	$(CC) $(CFLAGS) -o $(BIN)/$@ $^ $(LDFLAGS)    

EX4 : $(OBJ)/ex4.o
	$(CC) $(CFLAGS) -o $(BIN)/$@ $^ $(LDFLAGS)    

.PHONY : all proper clean cleanall run1 run2 run3 run4

proper:
	rm -f $(SRC)/*~ $(INC)/*~ *~

clean : proper
	rm -f $(OBJ)/*.o $(BIN)/*

cleanall: clean
	rm -r $(OBJ) $(BIN)

run1:
run2:
run3:
run4:
