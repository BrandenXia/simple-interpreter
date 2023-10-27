#include <stdlib.h>
#include "token.h"

inline const char *tokenTypeToString(TokenType type) {
    switch (type) {
        case OBJECT:
            return "OBJECT";
        case OPERATOR:
            return "OPERATOR";
        case NUMBER:
            return "NUMBER";
        case STRING:
            return "STRING";
        case L_PAREN:
            return "L_PAREN";
        case R_PAREN:
            return "R_PAREN";
        case END:
            return "END";
        case BLANK:
            return "BLANK";
        case UNKNOWN:
            return "UNKNOWN";
    }
}

const char *OPERATORS[] = {"+", "-", "*", "/", "^", "%", "=", "==", "!=", ">", "<", ">=", "<=", "&&", "||", "!", ""};

const char L_PARENS[] = "({[";

const char R_PARENS[] = ")}]";

const char QUOTES[] = "\"'";

const char ENDS[] = ";";

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