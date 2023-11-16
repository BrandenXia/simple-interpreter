#include "lexer/lexer.h"
#include "lexer/token_utils.h"
#include "parser/parser.h"
#include "parser/ast_utils.h"

int main(void) {
    TokenList *tokens;
    ASTNode *root;
    FILE *input;

    input = fopen("../test.txt", "r");

    tokenize(&tokens, input);

    printTokens(tokens);

    parse(&root, tokens);

    freeTokenList(tokens);

    printAST(root, 0);

    freeASTNode(root);
}
