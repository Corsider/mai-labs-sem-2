#ifndef __LEXER_H__
#define __LEXER_H__

#define VECTOR_BASE_CAPACITY 256

#include <stdbool.h>

typedef enum {
    FINAL, // Идентификатор конца входной строки
    INTEGER,
    FLOATING,
    OPERATOR,
    VARIABLE,
    BRACKET
} TokenType;

typedef struct {
    TokenType type;
    union {
        int   value_int;
        float value_float;
        char  operator_name;
        bool  is_left_bracket; // Левая скобка - истина, правая - ложь
        char  variable_name;
    } data;
} Token; // Именно они будут в узлах дерева выражений

typedef struct {
    Token **tokens; //**tokens
    int count;
    int max;
} Vector;

Token *t_create(Token *ref);
Vector *v_create();
void v_append(Vector *v, Token *item);
Token v_get(Vector *v, int ind);
void v_set(Vector *v, int ind, Token *item);
int v_length(Vector *v);
void v_delete(Vector *v, int ind);
void v_free(Vector *v);

void token_print(Token *t);
void token_next(Token *t); // Считать в *t следующий "кусок" входной строки

#endif
