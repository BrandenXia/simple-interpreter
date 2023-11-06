#ifndef SIMPLE_INTERPRETER_CHAR_UTILS_H
#define SIMPLE_INTERPRETER_CHAR_UTILS_H

#include <stdbool.h>

/*
 * Check if a character is in an array of characters.
 */
bool inArrayChar(const char array[], char c);

/*
 * Check if all characters in a string pass a function.
 */
bool allChar(const char *str, bool (*func)(char));

/*
 * Check if a string starts or all matches a string in an array of strings.
 */
bool matchStringStart(const char *str, const char *match[]);

/*
 * Count the number of times a character appears in a string.
 */
int countChar(const char *str, char c);

/*
 * Check if a character is a letter.
 */
bool isAlpha(char c);

/*
 * Check if a character is a digit.
 */
bool isDigit(char c);

#endif //SIMPLE_INTERPRETER_CHAR_UTILS_H
