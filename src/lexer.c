#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "token_utils.h"

TokenList *tokenize(char *input) {
    int current;
    TokenList *tokens;
    Token *token;

    current = 0;
    tokens = malloc(sizeof(TokenList));
    tokens->head = NULL;
    tokens->tail = NULL;
    tokens->size = 0;
    token = malloc(sizeof(Token));
    token->type = BLANK;
    token->value = malloc(sizeof(char));

    while (current <= strlen(input)) {
        TokenType type;
        char *c;

        c = malloc(sizeof(char));
        *c = input[current];
        type = getType(c);

        if (type == token->type) {
            char *tmp;
            tmp = realloc(token->value, sizeof(token->value) + sizeof(char));
            strncat(tmp, c, 1);
            if (tmp == NULL) {
                exit(1);
            }
            token->value = tmp;
        } else {
            if (token->type == BLANK) {
                free(token->value);
                free(token);
            } else {
                addToken(tokens, *token);
            }

            token = malloc(sizeof(Token));
            token->type = type;
            token->value = c;
        }

        current++;
    }

    return tokens;
}