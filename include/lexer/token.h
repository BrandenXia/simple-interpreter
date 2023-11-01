#ifndef SIMPLE_INTERPRETER_TOKEN_H
#define SIMPLE_INTERPRETER_TOKEN_H

typedef enum {
    TOKEN_TYPE_OBJECT,
    TOKEN_TYPE_OPERATOR,
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_STRING,
    TOKEN_TYPE_L_PAREN,
    TOKEN_TYPE_R_PAREN,
    TOKEN_TYPE_END,
    TOKEN_TYPE_BLANK,
    TOKEN_TYPE_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char *value;
} Token;

typedef struct TokenNode {
    Token token;
    struct TokenNode *next;
} TokenNode;

typedef struct {
    TokenNode *head;
    TokenNode *tail;
    int size;
} TokenList;

TokenList *newTokenList();

void addToken(TokenList *list, Token token);

extern const char *OPERATORS[];

extern const char L_PARENS[];

extern const char R_PARENS[];

extern const char QUOTES[];

extern const char ENDS[];

#endif //SIMPLE_INTERPRETER_TOKEN_H