EXE = tarea2

SRC_DIR = ./src
OBJ_DIR = ./obj

MKDIR  = mkdir -p
RM		 = rm -rf 

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CFLAGS += -Wall
LDFLAGS += #-Llib
LDLIBS += -lm

.PHONY: all clean

all: directories $(EXE)

$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

directories:
	$(MKDIR) $(OBJ_DIR)

clean:
	$(RM) $(OBJ_DIR)