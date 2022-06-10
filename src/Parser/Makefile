
CXX ?= g++
include_dirs = ./ ../Logger ../ShellInterface
FLAGS = -std=c++2a $(include_dirs:%=-I%) $(DEFINES) -pthread

ifeq ("$(MODE)", "RELEASE")
FLAGS += -O3
endif

OBJ_DIR = ./bin_int

all: scanner.cpp parser.cpp $(OBJ_DIR)/parser.o $(OBJ_DIR)/scanner.o $(OBJ_DIR)/Memory.o $(OBJ_DIR)/variable_type.o $(OBJ_DIR)/DepFileParser.o parser.o

scanner.cpp: main.lpp
	flex main.lpp

parser.cpp: main.ypp
	bison main.ypp

CPP = parser.cpp scanner.cpp Memory.cpp variable_type.cpp DepFileParser.cpp

OBJ = $(CPP:%.cpp=$(OBJ_DIR)/%.o)
DEP = $(OBJ:%.o=%.d)

-include $(DEP)

$(OBJ_DIR)/parser.o : parser.cpp | $(OBJ_DIR)
	${CXX} ${FLAGS} -c $< -MMD -o $@

$(OBJ_DIR)/scanner.o : scanner.cpp | $(OBJ_DIR)
	${CXX} ${FLAGS} -c $< -MMD -o $@

$(OBJ_DIR)/Memory.o : Memory.cpp | $(OBJ_DIR)
	${CXX} ${FLAGS} -c $< -MMD -o $@

$(OBJ_DIR)/variable_type.o : variable_type.cpp | $(OBJ_DIR)
	${CXX} ${FLAGS} -c $< -MMD -o $@

parser.o: $(OBJ) #$(OBJ_DIR)/parser.o $(OBJ_DIR)/scanner.o $(OBJ_DIR)/variable_type.o
	ld -r $(OBJ) -o parser.o	# to link into one object file
#	ar cr libparser.a $(OBJ)	# to make static library
#	g++-11 $(FLAGS) -shared -fpic $(OBJ) -o libsparser.dylib -Wl,-install_name,@rpath/libsparser.dylib
# 	install_name_tool -id @rpath/<lib-name> <lib-path/name> # to change the LC_ID_DYLIB
#	${CC} ${FLAGS} -c $(OBJ) -o ./build/beast_parser.o
#	${CC} -xar $(OBJ) -o parser.a
#	${CC} -std=c++2a variable_type.cpp scanner.cpp parses.cpp Memory.cpp -o ./build/main -DYYDEBUG=1
#	${CC} ${FLAGS} $(OBJ_DIR)/variable_type.o scanner.cpp parser.cpp Memory.cpp -DPARSER_TEST -o ./build/main
# 	${CC} -std=c++2a variable_type.cpp scanner.cpp parser.cpp Memory.cpp test.cpp -o ./build/main
#	echo "main created"

$(OBJ_DIR)/DepFileParser.o : DepFileParser.cpp | $(OBJ_DIR)
	${CXX} ${FLAGS} -c $< -MMD -o $@

# run: main
#	./build/main < beast.build

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

test_parser:
	${CXX} ${FLAGS} $(OBJ_DIR)/variable_type.o scanner.cpp parser.cpp Memory.cpp -DPARSER_TEST -o ./build/main

test: test.cpp
	${CXX} -std=c++2a test.cpp -o ./build/test && ./build/test

clean:
	rm -rf $(OBJ_DIR) parser.o

.PHONY: all clean