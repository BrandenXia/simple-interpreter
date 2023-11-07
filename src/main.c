#include "lexer/lexer.h"
#include "lexer/token_utils.h"

int main(void) {
    TokenList *tokens;

    char *str = "ab = a * 2 + 3\n";

    tokenize(&tokens, str);

    printTokens(tokens);

    freeTokenList(tokens);
}
