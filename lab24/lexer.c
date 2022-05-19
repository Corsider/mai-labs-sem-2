#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "lexer.h"

void token_next(Token *t)
{
    static bool can_be_unary = true; // http://en.wikipedia.org/wiki/Static_variable
    char c;
    
    do { // Избавление от пробельных литер
        c = fgetc(stdin);
    } while (isspace(c));
    
    if (c == EOF) { // The end
        t->type = FINAL;
    }
    
    else if (isalpha(c) || c == '_') { // Переменные
        t->type = VARIABLE;
        t->data.variable_name = c;
        can_be_unary = false;
    }
    
    else if (isdigit(c)) { // Числа
        float result;
        ungetc(c, stdin);
        scanf("%f", &result);
        
        if (result == (int) result) {
            t->type = INTEGER;
            t->data.value_int = (int) result;
        } else {
            t->type = FLOATING;
            t->data.value_float = result;
        }
        can_be_unary = false;
    }
    
    else if (c == '(' || c == ')') {
        t->type = BRACKET;
        t->data.is_left_bracket = (c == '(');
        can_be_unary = t->data.is_left_bracket;
    }
    
    else if (can_be_unary && (c == '-' || c == '+')) { // Учёт минуса перед числом
        int m = (c == '+') ? +1 : -1; // Знак
        
        do {
            c = fgetc(stdin);
        } while (isspace(c));
        
        if (isdigit(c)) {
            ungetc(c, stdin);
            token_next(t); // После минуса и т.д. надо число считать
            if (t->type == INTEGER) {
                t->data.value_int = m * (t->data.value_int);
            } else {
                t->data.value_float = m * (t->data.value_float);
            }
        } else {
            ungetc(c, stdin);
            t->type = OPERATOR;
            t->data.operator_name = '-';
            can_be_unary = true;
        }
    }
    
    else {
        t->type = OPERATOR;
        t->data.operator_name = c;
        can_be_unary = true;
    }
}

void token_print(Token *t)
{
    switch (t->type) {
        case FINAL:
            break;
        case INTEGER:
            printf("%d", t->data.value_int);
            break;
        case FLOATING:
            printf("%lg", t->data.value_float);
            break;
        case VARIABLE:
            printf("%c", t->data.variable_name);
            break;
        case OPERATOR:
            printf("%c", t->data.operator_name);
            break;
        case BRACKET:
            printf("%c", (t->data.is_left_bracket) ? '(' : ')');
            break;
    }
}

/////////////////
Vector *v_create() {
    Vector *new = (Vector *) malloc(sizeof(Vector));
    new->count = 0;
    new->max = VECTOR_BASE_CAPACITY;
    new->tokens = malloc(sizeof(Token) * 256);
    //new->tokens = NULL;
    return new;
}

void v_resize(Vector *v, int capacity) {
    if (v) {
        Token **tokens = realloc(v->tokens, sizeof(Token) * capacity);
        v->tokens = tokens;
        v->max = capacity;
    }
}

void v_set(Vector *v, int ind, Token *item) {
    v->tokens[ind] = item;
}

Token v_get(Vector *v, int ind) {
    Token *tmp = v->tokens[ind];
    Token res;
    res.data.is_left_bracket = tmp->data.is_left_bracket;
    res.data.operator_name = tmp->data.operator_name;
    res.data.value_float = tmp->data.value_float;
    res.data.value_int = tmp->data.value_int;
    res.data.variable_name = tmp->data.variable_name;
    res.type = tmp->type;
    return res;
}

Token *t_create(Token *ref) {
    Token *tmp = (Token *) malloc(sizeof(Token));
    tmp->data.is_left_bracket = ref->data.is_left_bracket;
    tmp->data.operator_name = ref->data.operator_name;
    tmp->data.value_float = ref->data.value_float;
    tmp->data.value_int = ref->data.value_int;
    tmp->data.variable_name = ref->data.variable_name;
    tmp->type = ref->type;
    //printf("token created\n");
    return tmp;
}

void v_append(Vector *v, Token *item) {
    Token *tok = t_create(item);
    if (v->count == v->max) {
        v_resize(v, v->max * 2);
        v->tokens[v->count++] = tok; //item
    } else {
        v->tokens[v->count++] = tok; //item
    }
}

int v_length(Vector *v) {
    return v->count;
}

void v_delete(Vector *v, int ind) {
    free(v->tokens[ind]);
    v->tokens[ind] == NULL;
    for (int i = ind; i < v_length(v) - 1; i++) {
        v->tokens[i] = v->tokens[i + 1];
        v->tokens[i + 1] = NULL;
    }
    v->count--;

    if (v->count < v->max * 2) {
        v_resize(v, v->max / 2);
    }
}

void v_free(Vector *v) {
    free(v->tokens);
    v->tokens = NULL;
}