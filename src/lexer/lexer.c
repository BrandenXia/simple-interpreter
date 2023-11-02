#include <stdlib.h>
#include <string.h>
#include "lexer/lexer.h"
#include "lexer/token_utils.h"

TokenList *tokenize(const char *input) {
    int current;
    TokenList *tokens;
    Token *token;

    current = 0;
    tokens = newTokenList();

    while (current <= (int) strlen(input)) {
        TokenType type;
        char *tmp;

        token = malloc(sizeof(Token));
        tmp = malloc(sizeof(char));

        strncat(tmp, &input[current], 1);
        token->type = getType(tmp);

        if (token->type == TOKEN_TYPE_UNKNOWN) {
            token->value = malloc(sizeof(char));
            strncpy(token->value, tmp, 1);
            addToken(tokens, *token);
            free(tmp);
            free(token);
            current++;
            continue;
        }

        do {
            current++;
            strncat(tmp, &input[current], 1);
            type = getType(tmp);
        } while (type == token->type && current <= (int) strlen(input));

        token->value = malloc(sizeof(tmp) - sizeof(char));
        strncpy(token->value, tmp, strlen(tmp) - 1);
        addToken(tokens, *token);
        free(tmp);
        free(token);
    }

    return tokens;
}
