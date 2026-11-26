cmake_minimum_required(VERSION 3.20)
project(lattice LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(lattice
    src/rational.cpp
    src/matrix.cpp
)
target_include_directories(lattice PUBLIC include)
target_compile_options(lattice PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-Wpedantic;-Wconversion>
)

add_executable(lattice_tests tests/test_main.cpp)
target_link_libraries(lattice_tests PRIVATE lattice)

enable_testing()
add_test(NAME lattice_tests COMMAND lattice_tests)
