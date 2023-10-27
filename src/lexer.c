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
    token = malloc(sizeof(Token));
    token->type = BLANK;
    token->value = malloc(sizeof(char));

    while (current <= strlen(input)) {
        TokenType type;
        char *c;
        char *tmp;

        c = malloc(sizeof(char));
        *c = input[current];
        type = getType(c);

        if (type == token->type) {
            tmp = realloc(token->value, sizeof(token->value) + sizeof(char));
            if (tmp == NULL) {
                exit(1);
            }
            tmp = strcat(tmp, c);
            token->value = tmp;
            free(c);
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