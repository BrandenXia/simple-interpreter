#include "lexer/lexer.h"
#include "lexer/token_utils.h"

int main(void) {
    char *str = "ab = a * 2 + 3\n";

    TokenList *tokens = tokenize(str);

    printTokens(tokens);
}
