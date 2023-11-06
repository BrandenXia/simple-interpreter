#ifndef SIMPLE_INTERPRETER_CHAR_UTILS_H
#define SIMPLE_INTERPRETER_CHAR_UTILS_H

#include <stdbool.h>

bool inArrayChar(const char array[], char c);

bool allChar(const char *str, bool (*func)(char));

bool matchStringStart(const char *str, const char *match[]);

int countChar(const char *str, char c);

bool isAlpha(char c);

bool isDigit(char c);

#endif //SIMPLE_INTERPRETER_CHAR_UTILS_H
