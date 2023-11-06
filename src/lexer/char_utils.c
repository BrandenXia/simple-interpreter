#include <string.h>
#include "lexer/char_utils.h"

bool inArrayChar(const char array[], const char c) {
    unsigned long length;

    length = strlen(array);

    for (unsigned int i = 0; i < length; i++) {
        if (array[i] == c) {
            return true;
        }
    }

    return false;
}

bool allChar(const char *str, bool (*func)(const char)) {
    for (int i = 0; i < (int) strlen(str); i++) {
        if (!func(str[i])) {
            return false;
        }
    }

    return true;
}

bool matchStringStart(const char *str, const char *match[]) {
    for (int i = 0; match[i][0] != '\0'; i++) {
        if (strncmp(str, match[i], strlen(str)) == 0) {
            return true;
        }
    }

    return false;
}

int countChar(const char *str, const char c) {
    int count;

    count = 0;

    for (int i = 0; i < (int) strlen(str); i++) {
        if (str[i] == c) {
            count++;
        }
    }

    return count;
}

bool isAlpha(const char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isDigit(const char c) {
    return c >= '0' && c <= '9';
}
