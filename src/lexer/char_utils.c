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
    char *buffer, *tmp, c;
    int buffer_size, buffer_current, str_size;
    bool escape;

    // Initialize variables
    buffer_size = (int) strlen(str);
    str_size = buffer_size;
    buffer_current = 0;
    buffer = calloc(buffer_size, sizeof(char));
    escape = false;

    for (int i = 0; i < str_size; i++, buffer_current++) {
        escape = false;
        // Check for escape characters
        switch (str[i]) {
            case '\a':
                c = 'a';
                escape = true;
                break;
            case '\b':
                c = 'b';
                escape = true;
                break;
            case '\f':
                c = 'f';
                escape = true;
                break;
            case '\n':
                c = 'n';
                escape = true;
                break;
            case '\r':
                c = 'r';
                escape = true;
                break;
            case '\t':
                c = 't';
                escape = true;
                break;
            case '\v':
                c = 'v';
                escape = true;
                break;
        }

        if (escape) {
            // Reallocate buffer to fit the next character
            tmp = realloc(buffer, (buffer_size + 1) * sizeof(char));
            if (tmp == NULL) {
                free(buffer);
                exit(1);
            }
            buffer = tmp;

            // Append the next character to the buffer
            buffer[buffer_size - 1] = '\\';
            buffer[buffer_size] = c;
            buffer_size++;
            buffer_current++;
        } else {
            buffer[buffer_current] = str[i];
        }
    }

    return buffer;
}
