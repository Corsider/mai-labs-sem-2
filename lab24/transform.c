#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "printer.h"
#include "transform.h"

int sum_create(Expression *expr, Token *t, int n, bool first)
{
    Expression tmp;

    Token plus  = { .type = OPERATOR, .data = { .operator_name = '+' } };
    Token minus = { .type = OPERATOR, .data = { .operator_name = '-' } };
    Token zero  = { .type = INTEGER,  .data = { .value_int = 0 } };

    int err = TRANSORMATION_SUCCESS;

    if (n == 0) {
        err = expression_create_terminal(expr, &zero);
        if (err) {
            return TRANSORMATION_ERROR;
        }
        return TRANSORMATION_SUCCESS;
    }

    err = expression_create_terminal(expr, t);
    if (err) {
        return TRANSORMATION_ERROR;
    }

    if (n < 0 && first) {
        err = expression_create_unary(expr, &minus, *expr);
        if (err) {
            return TRANSORMATION_ERROR;
        }
    }

    if (n > 1) {
        err = sum_create(&tmp, t, n - 1, false);
        if (err) {
            expression_destroy(&tmp);
            return TRANSORMATION_ERROR;
        }
        err = expression_create_binary(expr, &plus, *expr, tmp);
        if (err) {
            expression_destroy(&tmp);
            return TRANSORMATION_ERROR;
        }
    } else if (n < -1) {
        err = sum_create(&tmp, t, n + 1, false);
        if (err) {
            expression_destroy(&tmp);
            return TRANSORMATION_ERROR;
        }
        err = expression_create_binary(expr, &minus, *expr, tmp);
        if (err) {
            expression_destroy(&tmp);
            return TRANSORMATION_ERROR;
        }
    }

    return TRANSORMATION_SUCCESS;
}

int transform1(Expression *expr)
{
    Token bracket = { .type = BRACKET, .data = { .is_left_bracket = 0 } };
    Expression tmp;
    int err = sum_create(&tmp, &((*expr)->left->data), (*expr)->right->data.data.value_int, true);
    if (err) {
        expression_destroy(&tmp);
        return TRANSORMATION_ERROR;
    }
    err = expression_create_unary(&tmp, &bracket, tmp);
    if (err) {
        expression_destroy(&tmp);
        return TRANSORMATION_ERROR;
    }
    expression_destroy(expr);
    *expr = tmp;
    return TRANSORMATION_SUCCESS;
}

int transform2(Expression *expr)
{
    Expression tmp;
    Token bracket = { .type = BRACKET, .data = { .is_left_bracket = 0 } };
    int err = sum_create(&tmp, &((*expr)->left->right->data), (*expr)->right->data.data.value_int, true);
    if (err) {
        expression_destroy(&tmp);
        return TRANSORMATION_ERROR;
    }
    err = expression_create_unary(&tmp, &bracket, tmp);
    if (err) {
        expression_destroy(&tmp);
        return TRANSORMATION_ERROR;
    }
    Expression left = (*expr)->left->left;
    (*expr)->left->left = NULL;
    expression_destroy(&((*expr)->left));
    (*expr)->left = left;
    expression_destroy(&((*expr)->right));
    (*expr)->right = tmp;
    return TRANSORMATION_SUCCESS;
}

int transform3(Expression *expr)
{
    Expression tmp;
    Token bracket = { .type = BRACKET, .data = { .is_left_bracket = 0 } };
    int err = expression_create_unary(&tmp, &bracket, (*expr)->left);
    if (err) {
        expression_destroy(&tmp);
        return TRANSORMATION_ERROR;
    }
    (*expr)->left = tmp;
    return TRANSORMATION_SUCCESS;
}

void transform4(Expression *expr)
{
    Expression ex1;
    Expression ex2;
    Expression ab;
    Expression b2;
    Token mult = { .type = OPERATOR, .data = {.operator_name = '*'}};
    Token power = { .type = OPERATOR, .data = {.operator_name = '^'}};
    Token plus = { .type = OPERATOR, .data = {.operator_name = '+'}};
    Token minus = { .type = OPERATOR, .data = {.operator_name = '-'}};
    Token bracketr = { .type = BRACKET, .data = {.is_left_bracket = 0}};
    String str1;
    string_initialize(&str1);
    string_append(&str1, 'c');
    String str2;
    string_initialize(&str2);
    string_append(&str2, 'v');
    Token aaaa = { .type = VARIABLE, .data = { .variable_name = str1}};
    Token b = { .type = VARIABLE, .data = { .variable_name = str2}};
    string_copy(&aaaa.data.variable_name, &(*expr)->left->left->data.data.variable_name);
    string_copy(&b.data.variable_name, &(*expr)->right->left->data.data.variable_name);
    Token num2t = { .type = INTEGER, .data = { .value_int = 2}};
    Expression num2;
    Expression varA;
    Expression varB;
    expression_create_terminal(&num2, &num2t);
    expression_create_terminal(&varA, &aaaa);
    expression_create_terminal(&varB, &b);
    //creating a + b:
    expression_create_binary(&ex1, &plus, varA, varB);
    //creating (a + b):
    expression_create_unary(&ex1, &bracketr, ex1);
    //creating a^2:
    expression_create_binary(&ex2, &power, varA, num2);
    //creating a*b:
    expression_create_binary(&ab, &mult, varA, varB);
    //creating a^2 - a*b:
    expression_create_binary(&ex2, &minus, ex2, ab);
    //creating b^2:
    expression_create_binary(&b2, &power, varB, num2);
    //creating a^2 - a*b + b^2:
    expression_create_binary(&ex2, &plus, ex2, b2);
    //creating brackets for ex2:
    expression_create_unary(&ex2, &bracketr, ex2);
    (*expr)->data.data.operator_name = '*';
    (*expr)->left = NULL;
    (*expr)->right = NULL;
    expression_destroy(&((*expr)->left));
    expression_destroy(&((*expr)->right));
    
    (*expr)->left = ex1; //(a +b)
    (*expr)->right = ex2; //(a^2 -ab + b^2)
}

int match1(Expression *expr)
{
    return (*expr != NULL) && ((*expr)->data.type == OPERATOR)
           && ((*expr)->data.data.operator_name == '*')
           && ((*expr)->left->data.type == VARIABLE)
           && ((*expr)->right->data.type == INTEGER);
    //        && ((*expr)->right->data.data.value_int >= 0);
}

int match2(Expression *expr)
{
    return (*expr != NULL) && ((*expr)->data.type == OPERATOR)
           && ((*expr)->data.data.operator_name == '*')
           && ((*expr)->left->data.type == OPERATOR)
           && ((*expr)->left->data.data.operator_name == '*')
           && ((*expr)->left->right->data.type == VARIABLE)
           && ((*expr)->right->data.type == INTEGER);
    //        && ((*expr)->right->data.data.value_int >= 0);
}

int match3(Expression *expr)
{
    return (*expr != NULL) && ((*expr)->data.type == OPERATOR)
           && ((*expr)->left->data.type == OPERATOR)
           && ((*expr)->left->data.data.operator_name == '+');
}

int match_61(Expression *expr) //a^3 + b^3 = (a+b)*(a^2 -a*b + b^2)
{
    return (*expr != NULL) && ((*expr)->data.type == OPERATOR)
            && ((*expr)->data.data.operator_name = '^')
            && ((*expr)->left->data.type == VARIABLE)
            && ((*expr)->right->data.type == INTEGER)
            && ((*expr)->right->data.data.value_int == 3)
            && ((*expr)->right->right->data.type == OPERATOR)
            && ((*expr)->right->right->data.data.operator_name == '+')
            && ((*expr)->right->right->right->data.type == VARIABLE)
            && ((*expr)->right->right->right->right->data.type == OPERATOR)
            && ((*expr)->right->right->right->right->data.data.operator_name == '^')
            && ((*expr)->right->right->right->right->right->data.type == INTEGER)
            && ((*expr)->right->right->right->right->right->data.data.value_int == 3);
}

int match4(Expression *expr)
{
    return (*expr != NULL) && ((*expr)->data.type == OPERATOR)
            && ((*expr)->data.data.operator_name == '+')
            && ((*expr)->left->data.type == OPERATOR)
            && ((*expr)->left->data.data.operator_name == '^')
            && ((*expr)->right->data.type == OPERATOR)
            && ((*expr)->right->data.data.operator_name == '^')
            && ((*expr)->left->left->data.type == VARIABLE)
            && ((*expr)->left->right->data.type == INTEGER)
            && ((*expr)->left->right->data.data.value_int == 3)
            && ((*expr)->right->left->data.type == VARIABLE)
            && ((*expr)->right->right->data.type == INTEGER)
            && ((*expr)->right->right->data.data.value_int == 3);
}

int expression_transform(Expression *expr)
{
    if ((*expr) != NULL) {
        int err = expression_transform(&((*expr)->left));
        if (err) {
            return TRANSORMATION_ERROR;
        }
        err = expression_transform(&((*expr)->right));
        if (err) {
            return TRANSORMATION_ERROR;
        }

        if (match4(expr)) {
            transform4(expr);
        }
        //        if(match3(expr))
        //            return transform3(expr);
    }
    return TRANSORMATION_SUCCESS;
}
