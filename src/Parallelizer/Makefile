include_dirs = ../FileDependency ../ShellInterface ../Parser ./ ../../vendor/taskflow ../Logger
FLAGS = -std=c++2a $(include_dirs:%=-I%) $(DEFINES)

OBJ_DIR = ./bin_int
CPP := TaskScheduler.cpp
OBJ = $(CPP:%.cpp=$(OBJ_DIR)/%.o)
DEP = $(OBJ:%.o=%.d)

all: $(OBJ_DIR)/TaskScheduler.o main

-include $(DEP)

$(OBJ_DIR)/TaskScheduler.o: TaskScheduler.cpp | $(OBJ_DIR)
	$(CC) $(FLAGS) -c -MMD $< -o $@

main: $(OBJ)
#	ld -r $(OBJ) -o Parallelizer.o
	mv $(OBJ) .
$(OBJ_DIR):
	mkdir $(OBJ_DIR)

.PHONY: main