#ifndef MATRIX_H
#define MATRIX_H

#define MATRIX_SIZE 100

typedef struct _Matrix_ {
    int size;
    int a_knots_count;
    int M[MATRIX_SIZE];
    double A[MATRIX_SIZE];
    //int rows[MATRIX_SIZE];
} Matrix;

Matrix *create_matrix(int size);
int fill_matrix(Matrix *m);
void print_matrix(Matrix *m, int option);
void delete_matrix(Matrix *m);
void func(Matrix *m);

#endif