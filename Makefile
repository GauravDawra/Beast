include_dirs := src/Parser src/FileDependency src/ShellInterface src/Logger src/Parallelizer src/ vendor/taskflow vendor/cxxopts/include

VENDOR = vendor/
export VENDOR

CC ?= g++

ifeq ("$(MODE)", "DEBUG")
DEFINES += -DBEAST_DEBUG
else
DEFINES += -DBEAST_RELEASE
FLAGS += -O3
endif

FLAGS += -std=c++2a $(include_dirs:%=-I%) $(DEFINES) -pthread
SUBDIRS := src/Logger src/Parser src/FileDependency src/ShellInterface src/Parallelizer

export CC
export DEFINES
export MODE
#export FLAGS

all: $(SUBDIRS) main

$(SUBDIRS):
	make -C $@

main: main.cpp src/Parser/parser.o src/FileDependency/fileDependency.o src/ShellInterface/ShellInterface.o src/Logger/logger.o src/Parallelizer/TaskScheduler.o
	$(CC) $(FLAGS) src/Parser/parser.o src/FileDependency/fileDependency.o src/ShellInterface/ShellInterface.o src/Logger/logger.o src/Parallelizer/TaskScheduler.o main.cpp -o ./main
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