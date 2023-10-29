#include <stdlib.h>
#include "lexer/token.h"

inline const char *tokenTypeToString(TokenType type) {
    switch (type) {
        case TOKEN_TYPE_OBJECT:
            return "OBJECT";
        case TOKEN_TYPE_OPERATOR:
            return "OPERATOR";
        case TOKEN_TYPE_NUMBER:
            return "NUMBER";
        case TOKEN_TYPE_STRING:
            return "STRING";
        case TOKEN_TYPE_L_PAREN:
            return "L_PAREN";
        case TOKEN_TYPE_R_PAREN:
            return "R_PAREN";
        case TOKEN_TYPE_END:
            return "END";
        case TOKEN_TYPE_BLANK:
            return "BLANK";
        case TOKEN_TYPE_UNKNOWN:
            return "UNKNOWN";
    }
}

const char *OPERATORS[] = {"+", "-", "*", "/", "^", "%", "=", "==", "!=", ">", "<", ">=", "<=", "&&", "||", "!", ""};

const char L_PARENS[] = "({[";

const char R_PARENS[] = ")}]";

const char QUOTES[] = "\"'";

const char ENDS[] = ";";

TokenList *newTokenList() {
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
    node->data = token;
    node->next = NULL;

    if (list->head == NULL) {
        list->head = node;
    } else {
        list->tail->next = node;
    }

    list->tail = node;
    list->size++;
}