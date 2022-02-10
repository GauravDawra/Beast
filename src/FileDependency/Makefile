CC = g++-11
include_dirs = ../Parser ./
FLAGS = -std=c++2a $(include_dirs:%=-I%)

OBJ_DIR = ./bin_int
CPP := Filesystem.cpp Graph.cpp
OBJ = $(CPP:%.cpp=$(OBJ_DIR)/%.o)
DEP = $(OBJ:%.o=%.d)

all: $(OBJ_DIR)/Filesystem.o $(OBJ_DIR)/Graph.o main

-include $(DEP)

$(OBJ_DIR)/Graph.o: Graph.cpp | $(OBJ_DIR)
	$(CC) $(FLAGS) -c -MMD $< -o $@

$(OBJ_DIR)/Filesystem.o: Filesystem.cpp | $(OBJ_DIR)
	$(CC) $(FLAGS) -c -MMD $< -o $@

main: $(OBJ)
	ld -r $(OBJ) -o fileDependency.o

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

.PHONY: main
