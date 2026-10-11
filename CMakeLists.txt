cmake_minimum_required(VERSION 4.3)
project(CompressionToolkit C)

set(CMAKE_C_STANDARD 11)

add_executable(compressionToolkit src/main.c
        src/rle.c
        include/rle.h
        tests/rle_test.c
        tests/rle_test.h
)

target_include_directories(compressionToolkit PRIVATE include)
