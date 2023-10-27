#ifndef SIMPLE_INTERPRETER_TOKEN_H
#define SIMPLE_INTERPRETER_TOKEN_H

typedef enum {
    OBJECT,
    OPERATOR,
    NUMBER,
    STRING,
    L_PAREN,
    R_PAREN,
    END,
    BLANK,
    UNKNOWN
} TokenType;

const char *tokenTypeToString(TokenType type);

typedef struct {
    TokenType type;
    char *value;
} Token;

typedef struct TokenNode {
    Token data;
    struct TokenNode *next;
} TokenNode;

typedef struct {
    TokenNode *head;
    TokenNode *tail;
    int size;
} TokenList;

void addToken(TokenList *list, Token token);

extern const char *OPERATORS[];

extern const char L_PARENS[];

extern const char R_PARENS[];

extern const char QUOTES[];

extern const char ENDS[];

#endif //SIMPLE_INTERPRETER_TOKEN_H