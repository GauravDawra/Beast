include_dirs = ../Parser ../FileDependency ../Logger ./ ../../vendor/taskflow

CXX ?= g++
FLAGS = -std=c++2a $(include_dirs:%=-I%) $(DEFINES) -pthread

ifeq ("$(MODE)", "RELEASE")
FLAGS += -O3
endif

OBJ_DIR = ./bin_int

all: $(OBJ_DIR)/Shell.o $(OBJ_DIR)/Executor.o ShellInterface.o

CPP = Shell.cpp Executor.cpp
OBJ = $(CPP:%.cpp=$(OBJ_DIR)/%.o)
DEP = $(OBJ:%.o=%.d)

-include $(DEP)

$(OBJ_DIR)/Shell.o: Shell.cpp | $(OBJ_DIR)
	${CXX} ${FLAGS} -c $< -MMD -o $@

$(OBJ_DIR)/Executor.o: Executor.cpp | $(OBJ_DIR)
	${CXX} ${FLAGS} -c $< -MMD -o $@

ShellInterface.o: $(OBJ)
	ld -r $(OBJ) -o ShellInterface.o

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) ShellInterface.o

.PHONY: all clean