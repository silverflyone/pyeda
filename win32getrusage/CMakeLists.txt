# version 3.11 or later of CMake needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(
    win32getrusage
    VERSION 0.1
    DESCRIPTION "win32getrusage port taken from postgres")

include_directories(${PROJECT_SOURCE_DIR}/include)

set(INCLUDES include/win32getrusage.h)
set(SOURCES src/win32getrusage.c ${INCLUDES})

add_library(win32getrusage ${SOURCES})

# PUBLIC needed to make both headers and library available elsewhere in project
target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Tell compiler to use C++20 features. The code doesn't actually use any of them.
target_compile_features(win32getrusage PUBLIC cxx_std_20)

