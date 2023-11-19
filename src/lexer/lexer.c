#include <stdlib.h>
#include <string.h>
#include "lexer/lexer.h"
#include "lexer/token_utils.h"

Token nextToken(FILE *input) {
    Token token;
    char *buffer;
    int buffer_size;

    // Initialize buffer
    buffer = calloc(2, sizeof(char));
    buffer_size = 2;
    buffer[0] = (char) getc(input);
    buffer[1] = '\0';

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
        buffer[buffer_size - 1] = (char) getc(input);
        buffer[buffer_size] = '\0';

        // Update the index and buffer size
        buffer_size++;
    } while (token.type == getType(buffer));

    // Assign buffer minus the last character to token value
    token.value = calloc(buffer_size - 1, sizeof(char));
    memset(token.value, '\0', buffer_size - 1);
    strncpy(token.value, buffer, buffer_size - 2);
    // Go back one character
    fseek(input, -1, SEEK_CUR);

    // Free buffer
    free(buffer);

    return token;
}

void tokenize(TokenStack **dst, FILE *input) {
    TokenStack *tokens;
    Token token;
    long length, current;

    // Initialize variables
    initializeTokenStack(&tokens);
    fseek(input, 0, SEEK_END);
    length = ftell(input);
    fseek(input, 0, SEEK_SET);
    current = 0;

    // Loop until the end of the input
    while (current < length) {
        token = nextToken(input);  // Get the next token
        if (token.value == NULL) continue;  // Skip if the token value is NULL
        pushToken(tokens, token);
        if (current == length - 1) break; // Exit if the end of the input is reached
        current = ftell(input);
    }

    // Assign tokens to dst
    *dst = tokens;
}
