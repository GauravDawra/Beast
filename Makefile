include_dirs := src/Parser src/FileDependency src/ShellInterface src/Logger src/Parallelizer src/ vendor/taskflow

VENDOR = vendor/
export VENDOR

CC ?= g++

ifeq ("$(MODE)", "DEBUG")
DEFINES += -DBEAST_DEBUG
else
DEFINES += -DBEAST_RELEASE
endif

FLAGS = -std=c++2a $(include_dirs:%=-I%) $(DEFINES)
SUBDIRS := src/Logger src/Parser src/FileDependency src/ShellInterface src/Parallelizer

export CC
export DEFINES
export FLAGS

all: $(SUBDIRS) main

$(SUBDIRS):
	make -C $@

main: main.cpp src/FileDependency/fileDependency.o src/ShellInterface/ShellInterface.o src/Logger/logger.o src/Parallelizer/TaskScheduler.o
	$(CC) $(FLAGS) -lparser -Lsrc/Parser src/FileDependency/fileDependency.o src/ShellInterface/ShellInterface.o src/Logger/logger.o src/Parallelizer/TaskScheduler.o main.cpp -o ./main
#	./main < ./src/Parser/beast.build
# 	src/Parser/variable_type.cpp src/Parser/scanner.cpp src/Parser/parser.cpp src/Parser/Memory.cpp

run: | main
	./main

clean:
#	$(MAKE) clean $(SUBDIRS:%=-C %)
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
  	done
	rm main

.PHONY: all $(SUBDIRS) run