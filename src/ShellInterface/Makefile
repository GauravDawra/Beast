include_dirs = ../Parser ../FileDependency ../Logger ./ ../../vendor/taskflow

CC = g++-11
FLAGS = -std=c++2a -fopenmp $(include_dirs:%=-I%)
OBJ_DIR = ./bin_int

all: $(OBJ_DIR)/Shell.o $(OBJ_DIR)/Executor.o main

CPP = Shell.cpp Executor.cpp
OBJ = $(CPP:%.cpp=$(OBJ_DIR)/%.o)
DEP = $(OBJ:%.o=%.d)

-include $(DEP)

$(OBJ_DIR)/Shell.o: Shell.cpp | $(OBJ_DIR)
	${CC} ${FLAGS} -c $< -MMD -o $@

$(OBJ_DIR)/Executor.o: Executor.cpp | $(OBJ_DIR)
	${CC} ${FLAGS} -c $< -MMD -o $@

main: $(OBJ)
	ld -r $(OBJ) -o ShellInterface.o

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

.PHONY: main