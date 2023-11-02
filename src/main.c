#include "lexer/lexer.h"
#include "lexer/token_utils.h"

int main() {
    char *str = "'_aw38932u  *Ue#*&#ecfkw';";

    TokenList *tokens = tokenize(str);

    printTokens(tokens);
}