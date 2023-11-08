#include <stdlib.h>
#include "lexer/token.h"

const char *UNARY_OPERATORS[] = {"!", ""};

const char *BINARY_OPERATORS[] = {"+", "-", "*", "/", "^", "%", "=", "==", "!=", ">", "<", ">=", "<=", "&&", "||", ""};

const char L_PARENS[] = "({[";

const char R_PARENS[] = ")}]";

const char QUOTES[] = "\"'";

const char ENDS[] = ";\n";

void initializeTokenList(TokenList **dst) {
    TokenList *list;

    list = malloc(sizeof(TokenList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    *dst = list;
}

void freeTokenList(TokenList *list) {
    TokenNode *node, *next;

    for (node = list->head; node != NULL;) {
        next = node->next;
        free(node->token.value);
        free(node);
        node = next;
    }

    free(list);
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
