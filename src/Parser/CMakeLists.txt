set(TARGET Parser) # setting the Parser library name
if(WIN32)
    set(SCANNER "win_scanner.cpp")
else()
    set(SCANNER "unix_scanner.cpp")
endif()
add_library(${TARGET}  STATIC
        parser.cpp
        ${SCANNER}
        Memory.cpp
        variable_type.cpp
        DepFileParser.cpp)

target_include_directories(${TARGET} PRIVATE ../ShellInterface ../Logger)
