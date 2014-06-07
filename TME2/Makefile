CC= gcc
CFLAGS= -W -Wall -ansi -pedantic -g
LDFLAGS= 
SRC= src
INC=
OBJ= obj
BIN= bin

all : directories MYTIMES NICE                     

directories: ${OBJ} ${BIN}

${OBJ}:
	mkdir -p ${OBJ}
${BIN}:
	mkdir -p ${BIN}

# =====
# OBJET
# =====

$(OBJ)/mytimes.o : $(SRC)/mytimes.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCFLAGS)

$(OBJ)/nice.o : $(SRC)/nice.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCFLAGS)

# ==========
# EXECUTABLE
# ==========

MYTIMES : $(OBJ)/mytimes.o
	$(CC) $(CFLAGS) -o $(BIN)/$@ $^ $(LDFLAGS)    

NICE : $(OBJ)/nice.o
	$(CC) $(CFLAGS) -o $(BIN)/$@ $^ $(LDFLAGS)    

.PHONY : all proper clean cleanall run

proper:
	rm -f *~

clean : proper
	rm -f $(OBJ)/*.o

cleanall: clean
	rm -r $(OBJ) $(BIN)

run:
	./$(BIN)/MYTIMES "./$(BIN)/NICE" "nice -19 ./$(BIN)/NICE"
