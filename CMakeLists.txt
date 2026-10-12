cmake_minimum_required(VERSION 4.3)
project(CompressionToolkit C)

set(CMAKE_C_STANDARD 11)

add_executable(compressionToolkit src/main.c
        src/rle.c
        include/rle.h
        src/file.c
        include/file.h
        src/cli.c
        include/cli.h
)

target_include_directories(compressionToolkit PRIVATE include)
