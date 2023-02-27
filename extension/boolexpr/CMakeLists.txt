# version 3.11 or later of CMake needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(
    boolexpr
    VERSION 0.1
    DESCRIPTION "Boolean expression library")


include_directories(${PROJECT_SOURCE_DIR}/include)

set(INCLUDES include/boolexpr.h include/memcheck.h include/share.h include/util.h include/primes-inl.h)
set(SOURCES src/argset.c src/array.c src/binary.c src/boolexpr.c src/bubble.c src/compose.c src/dict.c src/flatten.c src/nnf.c src/product.c src/set.c src/simple.c src/util.c src/vector.c ${INCLUDES})

set(TEST_INC test/boolexprtest.hpp)
set(TEST_SRC test/main.cpp test/boolexprtest.cpp test/test_argset.cpp test/test_array.cpp test/test_basic.cpp test/test_binary.cpp test/test_bubble.cpp test/test_compose.cpp test/test_dict.cpp test/test_flatten.cpp test/test_nnf.cpp test/test_product.cpp test/test_set.cpp test/test_simple.cpp test/test_vector.cpp ${TEST_INC})

add_library(boolexpr ${SOURCES})

# PUBLIC needed to make both headers and library available elsewhere in project
target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include)


# Tell compiler to use C++20 features. The code doesn't actually use any of them.
target_compile_features(boolexpr PUBLIC cxx_std_20)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(boolexpr_test ${INCLUDES} ${TEST_SRC})
target_link_libraries(boolexpr_test boolexpr gtest)
#add_test(NAME example_test COMMAND example)