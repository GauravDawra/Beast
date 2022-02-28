CC ?= g++
include_dirs = ./
FLAGS = -std=c++2a $(include_dirs:%=-I%) $(DEFINES) -pthread

ifeq ("$(MODE)", "RELEASE")
FLAGS += -O3
endif

OBJ_DIR = ./bin_int
CPP := Logger.cpp Error.cpp
OBJ = $(CPP:%.cpp=$(OBJ_DIR)/%.o)
DEP = $(OBJ:%.o=%.d)

all: $(OBJ_DIR)/Logger.o $(OBJ_DIR)/Error.o logger.o

-include $(DEP)

$(OBJ_DIR)/Logger.o: Logger.cpp | $(OBJ_DIR)
	$(CC) $(FLAGS) -c -MMD $< -o $@

$(OBJ_DIR)/Error.o: Error.cpp | $(OBJ_DIR)
	$(CC) $(FLAGS) -c -MMD $< -o $@

logger.o: $(OBJ)
	ld -r $(OBJ) -o logger.o

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) logger.o

.PHONY: all clean
