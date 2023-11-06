#include <stdlib.h>
#include "lexer/token.h"

const char *UNARY_OPERATORS[] = {"!", ""};

const char *BINARY_OPERATORS[] = {"+", "-", "*", "/", "^", "%", "=", "==", "!=", ">", "<", ">=", "<=", "&&", "||", ""};

const char L_PARENS[] = "({[";

const char R_PARENS[] = ")}]";

const char QUOTES[] = "\"'";

const char ENDS[] = ";";

TokenList *newTokenList(void) {
    TokenList *list;

    list = malloc(sizeof(TokenList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

void addToken(TokenList *list, Token token) {
    TokenNode *node;

    node = malloc(sizeof(TokenNode));
    node->token = token;
    node->next = NULL;

    if (list->head == NULL) {
        list->head = node;
    } else {
        list->tail->next = node;
    }

    list->tail = node;
    list->size++;
}
