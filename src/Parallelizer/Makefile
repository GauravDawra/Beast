CC ?= g++
include_dirs = ../FileDependency ../ShellInterface ../Parser ./ ../../vendor/taskflow ../Logger
FLAGS = -std=c++2a $(include_dirs:%=-I%) $(DEFINES) -pthread

OBJ_DIR = ./bin_int
CPP := TaskScheduler.cpp
OBJ = $(CPP:%.cpp=$(OBJ_DIR)/%.o)
DEP = $(OBJ:%.o=%.d)

all: $(OBJ_DIR)/TaskScheduler.o TaskScheduler.o

-include $(DEP)

$(OBJ_DIR)/TaskScheduler.o: TaskScheduler.cpp | $(OBJ_DIR)
	$(CC) $(FLAGS) -c -MMD $< -o $@

TaskScheduler.o: $(OBJ)
#	right now just moving the object from bin_int
#	ld -r $(OBJ) -o Parallelizer.o
	cp $(OBJ) . # changing this mv to cp took me more than half an hour to debug :')

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) TaskScheduler.o

.PHONY: all