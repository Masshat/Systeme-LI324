CC= gcc
CFLAGS = -Wall -g
INCFLAGS= -I$(INC)
SRC= src
INC= include
OBJ= obj
BIN= bin
EXEC= mymalloc

all: directories $(EXEC)

directories: ${OBJ} ${BIN}

${OBJ}:
	mkdir -p ${OBJ}
${BIN}:
	mkdir -p ${BIN}

# =====
# OBJET
# =====

$(OBJ)/affiche_tas.o : $(SRC)/affiche_tas.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCFLAGS)

$(OBJ)/$(EXEC).o : $(SRC)/$(EXEC).c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCFLAGS)

# ==========
# EXECUTABLE
# ==========

$(EXEC) : $(OBJ)/affiche_tas.o $(OBJ)/$(EXEC).o
	$(CC) $(CFLAGS) -o $(BIN)/$@ $^

.PHONY: all prope clean cleanall run

proper :
	rm -f *~ $(INC)/*~ $(SRC)/*~

clean : proper
	rm -f $(OBJ)/*.o $(BIN)/$(EXEC)

cleanall: clean
	rm -r $(BIN) $(OBJ)

run:
	./$(BIN)/$(EXEC)
