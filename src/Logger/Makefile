CC = g++-11
include_dirs = ./
FLAGS = -std=c++2a $(include_dirs:%=-I%) $(DEFINES)

OBJ_DIR = ./bin_int
CPP := Logger.cpp Error.cpp
OBJ = $(CPP:%.cpp=$(OBJ_DIR)/%.o)
DEP = $(OBJ:%.o=%.d)

all: $(OBJ_DIR)/Logger.o $(OBJ_DIR)/Error.o main

-include $(DEP)

$(OBJ_DIR)/Logger.o: Logger.cpp | $(OBJ_DIR)
	$(CC) $(FLAGS) -c -MMD $< -o $@

$(OBJ_DIR)/Error.o: Error.cpp | $(OBJ_DIR)
	$(CC) $(FLAGS) -c -MMD $< -o $@

main: $(OBJ)
	ld -r $(OBJ) -o logger.o

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

.PHONY: main
