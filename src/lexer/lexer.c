#include <stdlib.h>
#include <string.h>
#include "lexer/lexer.h"
#include "lexer/token_utils.h"

Token nextToken(const char *input, int *current) {
    Token token;
    char *buffer;
    int buffer_size;

    buffer = calloc(2, sizeof(char));
    buffer_size = 2;
    buffer[0] = input[*current];
    buffer[1] = '\0';
    (*current)++;

    token.type = getType(buffer);
    token.value = NULL;

    if (token.type == TOKEN_TYPE_BLANK) {
        free(buffer);
        return token;
    }

    do {
        char *tmp;

        tmp = realloc(buffer, (buffer_size + 1) * sizeof(char));
        if (tmp == NULL) {
            free(buffer);
            exit(1);
        }
        buffer = tmp;

        buffer[buffer_size - 1] = input[*current];
        buffer[buffer_size] = '\0';
        (*current)++;
        buffer_size++;
    } while (token.type == getType(buffer) && *current < (int) strlen(input));

    token.value = calloc(buffer_size - 1, sizeof(char));
    memset(token.value, '\0', buffer_size - 1);
    strncpy(token.value, buffer, buffer_size - 2);
    (*current)--;

    free(buffer);

    return token;
}

TokenList *tokenize(const char *input) {
    TokenList *tokens;
    Token token;
    int current;

    tokens = newTokenList();
    current = 0;

    while (current < (int) strlen(input)) {
        token = nextToken(input, &current);
        if (token.value == NULL) continue;
        addToken(tokens, token);
    }

    return tokens;
}
