#include <string.h>
#include "lexer/char_utils.h"

bool inArrayChar(const char array[], const char c) {
    unsigned long length;

    length = strlen(array);

    for (int i = 0; i < length; i++) {
        if (array[i] == c) {
            return true;
        }
    }

    return false;
}

bool isAlpha(const char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isDigit(const char c) {
    return c >= '0' && c <= '9';
}