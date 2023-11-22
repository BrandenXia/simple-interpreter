AUTOMAKE_OPTIONS=foreign subdir-objects
bin_PROGRAMS=simple_interpreter
CommonFlags=-Wall -Wextra -Wpedantic -Werror -std=c11

simple_interpreter_CFLAGS=$(CommonFlags) -I ${top_srcdir}/include
simple_interpreter_SOURCES=\
${top_srcdir}/src/main.c \
${top_srcdir}/src/lexer/lexer.c \
${top_srcdir}/src/lexer/char_utils.c \
${top_srcdir}/src/lexer/token.c \
${top_srcdir}/src/lexer/token_utils.c \
${top_srcdir}/src/parser/ast.c \
${top_srcdir}/src/parser/parser.c \
${top_srcdir}/src/parser/ast_utils.c \
${top_srcdir}/src/cli/cli.c \
${top_srcdir}/src/runner/var_hash_map.c \
${top_srcdir}/src/runner/evaluate.c \
${top_srcdir}/src/runner/operators.c \
${top_srcdir}/src/runner/runner.c