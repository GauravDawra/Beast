
CC ?= g++
include_dirs = ./ ../Logger
FLAGS = -std=c++2a $(include_dirs:%=-I%) $(DEFINES)

OBJ_DIR = ./bin_int

all: scanner.cpp parser.cpp main $(OBJ_DIR)/parser.o $(OBJ_DIR)/scanner.o $(OBJ_DIR)/Memory.o $(OBJ_DIR)/variable_type.o libparser.a

scanner.cpp: main.lpp
	flex main.lpp

parser.cpp: main.ypp
	bison main.ypp

CPP = parser.cpp scanner.cpp Memory.cpp variable_type.cpp

OBJ = $(CPP:%.cpp=$(OBJ_DIR)/%.o)
DEP = $(OBJ:%.o=%.d)

-include $(DEP)

$(OBJ_DIR)/parser.o : parser.cpp | $(OBJ_DIR)
	${CC} ${FLAGS} -c $< -MMD -o $@

$(OBJ_DIR)/scanner.o : scanner.cpp | $(OBJ_DIR)
	${CC} ${FLAGS} -c $< -MMD -o $@

$(OBJ_DIR)/Memory.o : Memory.cpp | $(OBJ_DIR)
	${CC} ${FLAGS} -c $< -MMD -o $@

$(OBJ_DIR)/variable_type.o : variable_type.cpp | $(OBJ_DIR)
	${CC} ${FLAGS} -c $< -MMD -o $@

libparser.a: $(OBJ) #$(OBJ_DIR)/parser.o $(OBJ_DIR)/scanner.o $(OBJ_DIR)/variable_type.o
	ar cr libparser.a $(OBJ)	# to make static library
# 	ld -r $(OBJ) -o main.o	# to link into one object file
#	g++-11 $(FLAGS) -shared -fpic $(OBJ) -o libsparser.dylib -Wl,-install_name,@rpath/libsparser.dylib
# 	install_name_tool -id @rpath/<lib-name> <lib-path/name> # to change the LC_ID_DYLIB
#	${CC} ${FLAGS} -c $(OBJ) -o ./build/beast_parser.o
#	${CC} -xar $(OBJ) -o parser.a
#	${CC} -std=c++2a variable_type.cpp scanner.cpp parses.cpp Memory.cpp -o ./build/main -DYYDEBUG=1
#	${CC} ${FLAGS} $(OBJ_DIR)/variable_type.o scanner.cpp parser.cpp Memory.cpp -DPARSER_TEST -o ./build/main
# 	${CC} -std=c++2a variable_type.cpp scanner.cpp parser.cpp Memory.cpp test.cpp -o ./build/main
	echo "main created"

# run: main
#	./build/main < beast.build

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

test_parser:
	${CC} ${FLAGS} $(OBJ_DIR)/variable_type.o scanner.cpp parser.cpp Memory.cpp -DPARSER_TEST -o ./build/main

test: test.cpp
	${CC} -std=c++2a test.cpp -o ./build/test && ./build/test

clean:
	rm -rf $(OBJ_DIR) libparser.a

.PHONY: all clean