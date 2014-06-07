# Mettre dans SCHEDPATH le repertoire ou se trouve libsched.a
# et sched.h
CC=gcc
CFLAGS= -Wall -g -m32
LIBFLAGS=
INCFLAGS= -I$(INC)
SRC=src
INC=include
LIB=lib
OBJ=obj
BIN=bin
EXEC = TEST_dir TEST_list_FAT TEST_cat TEST_mv_file TEST_del_file TEST_create_file TEST_append_file TEST_append2_file TEST_read_dir

all: directories $(EXEC)

directories: $(LIB) $(BIN)

$(LIB):
	 mkdir -p $(LIB)

$(BIN):
	 mkdir -p $(BIN)

# =====
# OBJET
# =====
$(OBJ)/test_dir.o: $(SRC)/test_dir.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCFLAGS)

$(OBJ)/test_list_FAT.o: $(SRC)/test_list_FAT.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCFLAGS)

$(OBJ)/test_cat.o: $(SRC)/test_cat.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCFLAGS)

$(OBJ)/test_mv_file.o: $(SRC)/test_mv_file.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCFLAGS)

$(OBJ)/test_del_file.o: $(SRC)/test_del_file.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCFLAGS)

$(OBJ)/test_create_file.o: $(SRC)/test_create_file.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCFLAGS)

$(OBJ)/test_append_file.o: $(SRC)/test_append_file.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCFLAGS)

$(OBJ)/test_append2_file.o: $(SRC)/test_append2_file.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCFLAGS)

$(OBJ)/test_read_dir.o: $(SRC)/test_read_dir.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCFLAGS)

$(OBJ)/func_FS_FAT.o: $(SRC)/func_FS_FAT.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCFLAGS)

# ============
# BIBLIOTHEQUE
# ============
${LIB}/libfichiers.a : ${OBJ}/func_FS_FAT.o ${OBJ}/fat.o
	ar -rs $@ $^

# ==========
# EXECUTABLE
# ==========
TEST_dir: $(OBJ)/test_dir.o $(LIB)/libfichiers.a
	gcc $(CFLAGS) -o $(BIN)/$@ $^

TEST_list_FAT: $(OBJ)/test_list_FAT.o $(LIB)/libfichiers.a
	gcc $(CFLAGS) -o $(BIN)/$@ $^

TEST_cat: $(OBJ)/test_cat.o $(LIB)/libfichiers.a
	gcc $(CFLAGS) -o $(BIN)/$@ $^

TEST_del_file: $(OBJ)/test_del_file.o $(LIB)/libfichiers.a
	gcc $(CFLAGS) -o $(BIN)/$@ $^

TEST_mv_file: $(OBJ)/test_mv_file.o $(LIB)/libfichiers.a
	gcc $(CFLAGS) -o $(BIN)/$@ $^

TEST_create_file: $(OBJ)/test_create_file.o $(LIB)/libfichiers.a
	gcc $(CFLAGS) -o $(BIN)/$@ $^

TEST_append_file: $(OBJ)/test_append_file.o $(LIB)/libfichiers.a
	gcc $(CFLAGS) -o $(BIN)/$@ $^

TEST_append2_file: $(OBJ)/test_append2_file.o $(LIB)/libfichiers.a
	gcc $(CFLAGS) -o $(BIN)/$@ $^

TEST_read_dir: $(OBJ)/test_read_dir.o $(LIB)/libfichiers.a
	gcc $(CFLAGS) -o $(BIN)/$@ $^

.PHONY: all proper clean cleanall zero complet

proper:
	rm -f *~ $(SRC)/*~ $(INC)/*~

clean:proper
	rm -f $(OBJ)/test_*.o $(OBJ)/func_FS_FAT.o $(BIN)/* $(LIB)/*

cleanall:clean
	rm -r $(BIN) $(LIB)

zero:
	rm -f disque_image*
	cp sauvegarde/disque_image* .

complet:
	@echo "***************************"
	@echo "*  LISTAGE DU REPERTOIRE  *"
	@echo "***************************"
	@echo ""
	./$(BIN)/TEST_dir
	@echo ""
	@echo "****************************"
	@echo "*  CHANGEMENT NOM FICHIER  *"
	@echo "****************************"
	@echo ""
	./$(BIN)/TEST_mv_file fichier4 fichier6
	@echo ""
	@echo "****************************"
	@echo "* AFFICHAGE CONTENU FICHIER *"
	@echo "****************************"
	@echo ""
	./$(BIN)/TEST_cat fichier1
	@echo ""
	@echo "****************************"
	@echo "*   SUPPRESSION FICHIER    *"
	@echo "****************************"
	@echo ""
	./$(BIN)/TEST_del_file fichier3
	@echo ""
	@echo "****************************"
	@echo "*   CREATION FICHIER VIDE  *"
	@echo "****************************"
	@echo ""
	./$(BIN)/TEST_create_file fichier5
	@echo ""
	@echo "****************************"
	@echo "*ALLOCATION BLOC DE DONNEES*"
	@echo "****************************"
	@echo ""
	./$(BIN)/TEST_list_FAT
	@echo ""
	@echo "****************************"
	@echo "* AJOUT DONNEES FIN FICHIER*"
	@echo "****************************"
	@echo ""
	@echo "#== append_file ==#"
	@echo ""
	./$(BIN)/TEST_append_file fichier1	
	@echo ""
	@echo "#== append2_file ==#"
	@echo ""
	./$(BIN)/TEST_append2_file fichier2 Bonjour
