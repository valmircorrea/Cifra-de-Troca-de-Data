LIB_DIR = ./lib
INC_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./build
BIN_DIR = ./bin
DOC_DIR = ./doc

CC = g++
CPPLAGS = -Wall -pedantic -ansi -std=c++11 -I. -I$(INC_DIR)

RM = rm -rf
RM_TUDO = rm -fr

PROG = cifrar
PROG2 = decifrar

.PHONY: all clean debug doc doxygen gnuplot init valgrind

all: init $(PROG) $(PROG2)

debug: CFLAGS += -g -O0
debug: $(PROG)

init:
	@mkdir -p $(BIN_DIR)/
	@mkdir -p $(OBJ_DIR)/

########################## CIFRA #########################
$(PROG): $(OBJ_DIR)/cifrar.o
	@echo "====================================================="
	@echo "Ligando o alvo $@"
	@echo "====================================================="		
	$(CC) $(CPPLAGS) -o $(BIN_DIR)/$@ $^
	@echo "*** [Executavel $(PROG) criado em $(BIN_DIR)] ***"
	@echo "====================================================="

$(OBJ_DIR)/cifrar.o: $(SRC_DIR)/cifrar.cpp
	$(CC) -c $(CPPLAGS) -o $@ $<

######################### DECIFRA ########################
$(PROG2): $(OBJ_DIR)/decifrar.o
	@echo "====================================================="
	@echo "Ligando o alvo $@"
	@echo "====================================================="		
	$(CC) $(CPPLAGS) -o $(BIN_DIR)/$@ $^
	@echo "*** [Executavel $(PROG2) criado em $(BIN_DIR)] ***"
	@echo "====================================================="

$(OBJ_DIR)/decifrar.o: $(SRC_DIR)/decifrar.cpp
	$(CC) -c $(CPPLAGS) -o $@ $<

clean:
	@echo "====================================================="
	@echo "Limpando pastas $(BIN_DIR) e $(OBJ_DIR)"
	@echo "====================================================="
	$(RM) $(BIN_DIR)/*
	$(RM) $(OBJ_DIR)/*