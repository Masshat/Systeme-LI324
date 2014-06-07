CC= gcc
CFLAGS= -W -Wall -ansi -pedantic -g
INCFLAGS= -I$(INC)
LDFLAGS=                    
SRC= src
INC= include
OBJ= obj
BIN= bin
EXEC= TESTLISTE

all : directories $(EXEC)                     

directories: ${OBJ} ${BIN}

${OBJ}:
	mkdir -p ${OBJ}
${BIN}:
	mkdir -p ${BIN}

# =====
# OBJET
# =====

$(OBJ)/liste.o : $(SRC)/liste.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCFLAGS)

$(OBJ)/testeliste.o : $(SRC)/testeliste.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCFLAGS)

# ==========
# EXECUTABLE
# ==========

$(EXEC) : $(OBJ)/liste.o $(OBJ)/testeliste.o
	$(CC) $(CFLAGS) -o $(BIN)/$@ $^ $(LDFLAGS)    

.PHONY : all proper clean cleanall run

proper:
	rm -f $(SRC)/*~ $(INC)/*~ *~

clean : proper
	rm -f $(OBJ)/*.o $(BIN)/*

cleanall: clean
	rm -r $(OBJ) $(BIN)

run:
	./$(BIN)/$(EXEC)
