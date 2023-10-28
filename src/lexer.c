#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "utils/token_utils.h"

TokenList *tokenize(char *input) {
    int current;
    TokenList *tokens;
    Token *token;

    current = 0;
    tokens = malloc(sizeof(TokenList));
    tokens->head = NULL;
    tokens->tail = NULL;
    tokens->size = 0;

    while (current <= strlen(input)) {
        TokenType type;
        char* tmp;

        token = malloc(sizeof(Token));
        tmp = malloc(sizeof(char));

        strncat(tmp, &input[current], 1);
        token->type = getType(tmp);

        if (token->type == BLANK) {
            current++;
            continue;
        }

        do {
            current++;
            strncat(tmp, &input[current], 1);
            type = getType(tmp);
        } while (type == token->type && current <= strlen(input));

        token->value = malloc(sizeof(tmp) - sizeof(char));
        strncpy(token->value, tmp, strlen(tmp) - 1);
        addToken(tokens, *token);
    }

    return tokens;
}