cmake_minimum_required(VERSION 3.26)
project(simple_interpreter C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Werror")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address,undefined -g")

include_directories(include)

add_executable(simple_interpreter
    src/main.c
    src/lexer/lexer.c
    src/lexer/char_utils.c
    src/lexer/token.c
    src/lexer/token_utils.c
    src/parser/ast.c
    src/parser/parser.c
    src/parser/ast_utils.c
    src/cli/cli.c
    src/runner/var_hash_map.c
    src/runner/evaluate.c
    src/runner/operators.c
    src/runner/runner.c
)