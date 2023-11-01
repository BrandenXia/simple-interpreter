#include "lexer/lexer.h"
#include "lexer/token_utils.h"

int main() {
    char *str = "ab = (1 + 28)* 3 * '_aw38932u  *U@#*&#ecfkw';";

    TokenList *list = tokenize(str);

    printTokens(list);
}