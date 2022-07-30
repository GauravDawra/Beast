cmake_minimum_required(VERSION 3.19)

project(Beast)
set(TARGET beast)

set(CMAKE_CXX_STANDARD 20)

if(NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL Release)
    set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O3 -pthread")
    add_compile_definitions(BEAST_RELEASE)
    message("${CMAKE_BUILD_TYPE} ${CMAKE_CXX_FLAGS}")
else()
    add_compile_definitions(BEAST_DEBUG)
endif()


add_executable (${TARGET}
        main.cpp
        )

set(moduleList Parser; Logger; FileDependency; ShellInterface; Parallelizer)

foreach(module ${moduleList})
    add_subdirectory(src/${module} ${module})
endforeach()

target_link_libraries(${TARGET} ${moduleList})

list(TRANSFORM moduleList PREPEND src/)

target_link_directories(${TARGET} PRIVATE ${moduleList})
target_include_directories(${TARGET} PRIVATE
        ${moduleList}
        vendor/taskflow
        vendor/cxxopts/include)

