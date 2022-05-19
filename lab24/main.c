#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "tree.h"
#include "transform.h"

/*
 * Необходимые улучшения:
 *   сделать tokens вектором, а не массивом - ready
 *   убрать вывод деревьев и вспомогательных сообщений - will be done soon
 *   перейти от однобуквенных имён переменных к многобуквенным - under investigation lol
 *   обработать экзотические требования к обработке унарного минуса - what...
*/

int main(void)
{
    //Token tokens[256];
    Vector *TokensV = v_create();
    size_t tokens_qty = 0;

    Token token;
    token_next(&token);

    while (token.type != FINAL) {
        //tokens[tokens_qty++] = token;
        v_append(TokensV, &token);
        tokens_qty++;
        token_next(&token);
    }

    //printf("%s\n", v_get(TokensV, 2).data.operator_name);

    Tree tree = tree_create(TokensV, 0, tokens_qty - 1); //tokens

    printf("\nExpression tree:\n");
    tree_print(tree, 0);

    tree_transform(&tree);

    printf("\nSemitransformed expression tree:\n");
    tree_print(tree, 0);

    printf("\nTree's infix linearization:\n");
    tree_infix(tree);
    printf("\n");

    return 0;
}

