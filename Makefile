include_dirs := src/Parser src/FileDependency src/ShellInterface src/Logger src/Parallelizer src/ vendor/taskflow

VENDOR = vendor/
export VENDOR

CC = g++-11
DEFINES = -DBEAST_DEBUG
FLAGS = -std=c++2a $(include_dirs:%=-I%) $(DEFINES)
SUBDIRS := src/Parser/ src/FileDependency src/ShellInterface src/Logger src/Parallelizer

export CC
export DEFINES
export FLAGS

all: $(SUBDIRS) main

$(SUBDIRS):
	make -C $@

main: main.cpp
	$(CC) $(FLAGS) -lparser -Lsrc/Parser src/FileDependency/fileDependency.o src/ShellInterface/ShellInterface.o src/Logger/logger.o src/Parallelizer/TaskScheduler.o main.cpp -o ./main -rpath src/Parser
	./main
#	./main < ./src/Parser/beast.build
# 	src/Parser/variable_type.cpp src/Parser/scanner.cpp src/Parser/parser.cpp src/Parser/Memory.cpp
.PHONY: all $(SUBDIRS) main