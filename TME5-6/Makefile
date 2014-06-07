IPCPATH = /Infos/lmd/2005/licence/ue/li324-2006fev/TME6-7/libipc/lib
CFLAGS = -Wall -I$(IPCPATH)
LIBFLAGS=-L$(IPCPATH) -lIPC
CC= gcc
SRC= src
OBJ= obj
BIN= bin

all: directories Tab1case TabNcase  

directories: ${OBJ} ${BIN}

${OBJ}:
	mkdir -p ${OBJ}
${BIN}:
	mkdir -p ${BIN}

# =====
# OBJET
# =====

$(OBJ)/Tab1case.o: $(SRC)/Tab1case.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ)/TabNcase.o: $(SRC)/TabNcase.c
	$(CC) -c $< -o $@ $(CFLAGS)

# ==========
# EXECUTABLE
# ==========

Tab1case: $(OBJ)/Tab1case.o
	$(CC) -o $(BIN)/$@ $^ $(LIBFLAGS)

TabNcase: $(OBJ)/TabNcase.o
	$(CC) -o $(BIN)/$@ $^ $(LIBFLAGS)

.PHONY: all proper clean cleanall

proper:
	rm -f *~ $(SRC)/*~

clean: proper
	rm -f $(OBJ)/*.o $(BIN)/*

cleanall: clean
	rm -r $(OBJ) $(BIN) 

# RUN

run1:
	./$(BIN)/Tab1case

run2:
	./$(BIN)/TabNcase
