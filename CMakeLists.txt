cmake_minimum_required(VERSION 3.26)
project(simple_interpreter C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(simple_interpreter
    src/main.c
    src/lexer.c
    src/char_utils.c
    src/token.c
    src/token_utils.c
)