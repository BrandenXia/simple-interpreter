#ifndef SIMPLE_INTERPRETER_TOKEN_H
#define SIMPLE_INTERPRETER_TOKEN_H

/*
 * Token types:
 * - TOKEN_TYPE_OBJECT: object
 * - TOKEN_TYPE_UNARY_OPERATOR: unary operator
 * - TOKEN_TYPE_BINARY_OPERATOR: binary operator
 * - TOKEN_TYPE_NUMBER: number
 * - TOKEN_TYPE_STRING: string
 * - TOKEN_TYPE_L_PAREN: left parenthesis
 * - TOKEN_TYPE_R_PAREN: right parenthesis
 * - TOKEN_TYPE_END: end of input
 * - TOKEN_TYPE_BLANK: blank
 * - TOKEN_TYPE_UNKNOWN: unknown
 */
typedef enum {
    TOKEN_TYPE_OBJECT,
    TOKEN_TYPE_UNARY_OPERATOR,
    TOKEN_TYPE_BINARY_OPERATOR,
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_STRING,
    TOKEN_TYPE_L_PAREN,
    TOKEN_TYPE_R_PAREN,
    TOKEN_TYPE_END,
    TOKEN_TYPE_BLANK,
    TOKEN_TYPE_UNKNOWN
} TokenType;

/*
 * Token:
 * - type: token type
 * - value: token value
 */
typedef struct {
    TokenType type;
    char *value;
} Token;

/*
 * Token node:
 * A linked list node for tokens.
 * - token: token
 * - next: next token node
 */
typedef struct TokenNode {
    Token token;
    struct TokenNode *next;
} TokenNode;

/*
 * Token list:
 * A linked list for tokens.
 * - head: head of the token list
 * - tail: tail of the token list
 * - size: size of the token list
 */
typedef struct {
    TokenNode *head;
    TokenNode *tail;
    int size;
} TokenList;

/*
 * Initialize a token list.
 */
void initializeTokenList(TokenList **dst);

/*
 * Free a token list.
 */
void freeTokenList(TokenList *list);

/*
 * Add a token to the token list.
 */
void addToken(TokenList *list, Token token);

extern const char *UNARY_OPERATORS[];

extern const char *BINARY_OPERATORS[];

extern const char L_PARENS[];

extern const char R_PARENS[];

extern const char QUOTES[];

extern const char ENDS[];

#endif //SIMPLE_INTERPRETER_TOKEN_H
