# version 3.11 or later of CMake needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(
    win32getopt
    VERSION 0.1
    DESCRIPTION "getopt port taken from https://www.codeproject.com/KB/Articles/getopt4win/getopt_mb_uni_src_2022.zip")

include_directories(${PROJECT_SOURCE_DIR}/include)

set(INCLUDES include/win32getopt.h)
set(SOURCES src/win32getopt.c ${INCLUDES})

add_definitions( -DEXPORTS_GETOPT )

add_library(win32getopt ${SOURCES})

# PUBLIC needed to make both headers and library available elsewhere in project
target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Tell compiler to use C++20 features. The code doesn't actually use any of them.
target_compile_features(win32getopt PUBLIC cxx_std_20)

