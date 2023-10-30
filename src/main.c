#include "lexer/lexer.h"
#include "lexer/token_utils.h"

int main() {
    char *str = "ab = '1 + 28)* 3;'";

    TokenList *list = tokenize(str);

    printTokens(list);
}