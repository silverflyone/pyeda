# version 3.11 or later of CMake needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(
    picosat
    VERSION 0.1
    DESCRIPTION "Picosat library")

set(HEADERS picosat.h)
set(SOURCES picosat.c ${HEADERS})

add_library(picosat ${SOURCES})

# PUBLIC needed to make both headers and library available elsewhere in project
target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR})

# Tell compiler to use C++20 features. The code doesn't actually use any of them.
target_compile_features(picosat PUBLIC cxx_std_20)

target_link_libraries(picosat win32getrusage win32getopt)
