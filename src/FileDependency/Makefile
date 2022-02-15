CC ?= g++
include_dirs = ../Logger ../Parser ./
FLAGS = -std=c++2a $(include_dirs:%=-I%) $(DEFINES)

OBJ_DIR = ./bin_int
CPP := Filesystem.cpp Graph.cpp
OBJ = $(CPP:%.cpp=$(OBJ_DIR)/%.o)
DEP = $(OBJ:%.o=%.d)

all: $(OBJ_DIR)/Filesystem.o $(OBJ_DIR)/Graph.o fileDependency.o

-include $(DEP)

$(OBJ_DIR)/Graph.o: Graph.cpp | $(OBJ_DIR)
	$(CC) $(FLAGS) -c -MMD $< -o $@

$(OBJ_DIR)/Filesystem.o: Filesystem.cpp | $(OBJ_DIR)
	$(CC) $(FLAGS) -c -MMD $< -o $@

fileDependency.o: $(OBJ)
	ld -r $(OBJ) -o fileDependency.o

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) fileDependency.o

.PHONY: all clean
