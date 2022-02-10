include_dirs := src/Parser src/FileDependency src/ShellInterface src/Logger src/

CC = g++-11
DEFINES = -DBEAST_DEBUG
FLAGS = -std=c++2a -fopenmp $(include_dirs:%=-I%) $(DEFINES)
SUBDIRS := src/Parser/ src/FileDependency src/ShellInterface src/Logger

export DEFINES

all: $(SUBDIRS) main

$(SUBDIRS):
	make -C $@

main: main.cpp
	$(CC) $(FLAGS) -lparser -Lsrc/Parser src/FileDependency/fileDependency.o src/ShellInterface/ShellInterface.o src/Logger/logger.o main.cpp -o ./main -rpath src/Parser
	./main
#	./main < ./src/Parser/beast.build
# 	src/Parser/variable_type.cpp src/Parser/scanner.cpp src/Parser/parser.cpp src/Parser/Memory.cpp
.PHONY: all $(SUBDIRS) main