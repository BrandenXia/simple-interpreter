#ifndef SIMPLE_INTERPRETER_TOKEN_H
#define SIMPLE_INTERPRETER_TOKEN_H

#define UNARY_OPERATORS (const char *[]){"!", ""}

#define BINARY_OPERATORS (const char *[]){"+", "-", "*", "/", "^", "%", "=", "==", "!=", ">", "<", ">=", "<=", "&&", "||", ""}

#define L_PARENS "({["

#define R_PARENS ")}]"

#define QUOTES "\"'"

#define ENDS ";\n"

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
 * Token stack:
 * - tokens: tokens
 * - size: size of the stack
 * - capacity: capacity of the stack
 */
typedef struct {
    Token *tokens;
    int size;
    int capacity;
} TokenStack;

/*
 * Initialize a token stack.
 */
void initializeTokenStack(TokenStack **dst);

/*
 * Free a token stack.
 */
void freeTokenStack(TokenStack *stack);

/*
 * Push a token to the token stack.
 */
void pushToken(TokenStack *stack, Token token);

/*
 * Pop a token from the token stack.
 */
Token popToken(TokenStack *stack);

/*
 * Peek a token from the token stack.
 */
Token peekToken(TokenStack *stack);

#endif //SIMPLE_INTERPRETER_TOKEN_H
