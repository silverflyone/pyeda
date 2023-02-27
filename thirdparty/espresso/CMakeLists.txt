# version 3.11 or later of CMake needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(
    espresso
    VERSION 0.1
    DESCRIPTION "Espresso library")

include_directories(${PROJECT_SOURCE_DIR}/include)

set(INCLUDES include/espresso.h include/main.h include/mincov_int.h include/set.h include/sparse_int.h include/sparse.h include/utility.h)
set(SOURCES src/cofactor.c src/cols.c src/compl.c src/contain.c src/cubestr.c src/cvrin.c src/cvrm.c src/cvrmisc.c src/cvrout.c src/dominate.c src/espresso.c src/essen.c src/exact.c src/expand.c src/gasp.c src/gimpel.c src/globals.c src/hack.c src/indep.c src/irred.c src/main.c src/matrix.c src/mincov.c src/opo.c src/pair.c src/part.c src/primes.c src/reduce.c src/rows.c src/set.c src/setc.c src/sharp.c src/sminterf.c src/solution.c src/sparse.c src/unate.c src/verify.c ${INCLUDES})

add_library(espresso ${SOURCES})

# PUBLIC needed to make both headers and library available elsewhere in project
target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR})

# Tell compiler to use C++20 features. The code doesn't actually use any of them.
target_compile_features(espresso PUBLIC cxx_std_20)