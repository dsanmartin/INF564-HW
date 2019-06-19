EXE = tarea2
EXE2 = insertion

SRC_DIR = ./src
OBJ_DIR = ./obj

MKDIR  = mkdir -p
RM		 = rm -rf 

SRC = $(filter-out $(SRC_DIR)/insertion.c, $(wildcard $(SRC_DIR)/*.c))
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = gcc

CFLAGS = -Wall -O3
LDFLAGS = #-Llib
LDLIBS = -lm

.PHONY: all clean

all: directories $(EXE) $(EXE2)

$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(EXE2): $(OBJ_DIR)/insertion.o
	$(CC) $^ -o $@ 

$(OBJ_DIR)/insertion.o: src/insertion.c
	$(CC) $(CFLAGS) -c $<  -o $@

directories:
	$(MKDIR) $(OBJ_DIR)

clean:
	$(RM) $(OBJ_DIR)