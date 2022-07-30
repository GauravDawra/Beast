set(TARGET Parser) # setting the Parser library name

add_library(${TARGET}  STATIC
        parser.cpp
        scanner.cpp
        Memory.cpp
        variable_type.cpp
        DepFileParser.cpp)

target_include_directories(${TARGET} PRIVATE ../ShellInterface ../Logger)
