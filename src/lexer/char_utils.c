#include <string.h>
#include <stdlib.h>
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

char *unescape(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    int str_size = (int) strlen(str);
    char *buffer = calloc(2 * str_size + 1, sizeof(char));
    if (buffer == NULL) {
        return NULL;
    }

    int buffer_current = 0;
    for (int i = 0; i < str_size; i++) {
        char c = str[i];
        bool escape = false;
        char escape_char;

        switch (c) {
            case '\a':
                escape_char = 'a';
                escape = true;
                break;
            case '\b':
                escape_char = 'b';
                escape = true;
                break;
            case '\f':
                escape_char = 'f';
                escape = true;
                break;
            case '\n':
                escape_char = 'n';
                escape = true;
                break;
            case '\r':
                escape_char = 'r';
                escape = true;
                break;
            case '\t':
                escape_char = 't';
                escape = true;
                break;
            case '\v':
                escape_char = 'v';
                escape = true;
                break;
            default:
                escape_char = c;
                break;
        }

        if (escape) {
            buffer[buffer_current++] = '\\';
            buffer[buffer_current++] = escape_char;
        } else {
            buffer[buffer_current++] = c;
        }
    }

    return buffer;
}
