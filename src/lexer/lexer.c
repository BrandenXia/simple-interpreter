#include <stdlib.h>
#include <string.h>
#include "lexer/lexer.h"
#include "lexer/token_utils.h"

Token nextToken(const char *input, int *current) {
    Token token;
    char *buffer;
    int buffer_size;

    // Initialize buffer
    buffer = calloc(2, sizeof(char));
    buffer_size = 2;
    buffer[0] = input[*current];
    buffer[1] = '\0';
    (*current)++;

    // Initialize token
    token.type = getType(buffer);
    token.value = NULL;

    // Return a token with NULL value if the token type is TOKEN_TYPE_BLANK
    if (token.type == TOKEN_TYPE_BLANK) {
        free(buffer);
        return token;
    }

    // Loop until the token type changes
    do {
        char *tmp;

        // Reallocate buffer to fit the next character
        tmp = realloc(buffer, (buffer_size + 1) * sizeof(char));
        if (tmp == NULL) {
            free(buffer);
            exit(1);
        }
        buffer = tmp;

        // Append the next character to the buffer
        buffer[buffer_size - 1] = input[*current];
        buffer[buffer_size] = '\0';

        // Update the index and buffer size
        (*current)++;
        buffer_size++;
    } while (token.type == getType(buffer) && *current < (int) strlen(input));

    // Assign buffer minus the last character to token value
    token.value = calloc(buffer_size - 1, sizeof(char));
    memset(token.value, '\0', buffer_size - 1);
    strncpy(token.value, buffer, buffer_size - 2);
    // Go back one character
    (*current)--;

    // Free buffer
    free(buffer);

    return token;
}

void tokenize(TokenList **dst, const char *input) {
    TokenList *tokens;
    Token token;
    int current;

    // Initialize variables
    initializeTokenList(&tokens);
    current = 0;

    // Loop until the end of the input
    while (current < (int) strlen(input)) {
        token = nextToken(input, &current);  // Get the next token
        if (token.value == NULL) continue;  // Skip if the token value is NULL
        addToken(tokens, token);
    }

    // Assign tokens to dst
    *dst = tokens;
}
