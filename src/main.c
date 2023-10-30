#include "lexer/lexer.h"
#include "lexer/token_utils.h"
#include "parser/ast.h"
#include "parser/parser.h"
#include "parser/ast_utils.h"

int main() {
    char *str = "ab = (1 + 28)* 3 * '_aw38932u  *U@#*&#ecfkw';ac=ab+ac;";

    TokenList *list = tokenize(str);

    printTokens(list);

    ASTNode *node = parse(list);

    printASTNode(node, 0);
}