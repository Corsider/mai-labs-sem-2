#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

Matrix *create_matrix(int size) {
    Matrix *m = (Matrix *)malloc(sizeof(Matrix));
    m->size = size;
    m->a_knots_count = 0;
    return m;
}

int fill_matrix(Matrix *m) {
    FILE *f;
    f = fopen("data.txt", "r");
    if (f == NULL) {
        //fprintf(stderr, "Can't open file.\n");
        //exit(1);
        return 0;
    }

    double num;
    int ALastIndex = 0;
    //int rowCounter = 0;
    int rowSaved = -1;
    int pasteCounter = 0;
    double numIndexes[MATRIX_SIZE];
    //int PasteIndexes[MATRIX_SIZE];
    //int pasteIndex = 0;
    for (int i = 0; i < m->size; i++) {
        int isZero = 1;
        for (int u = 0; u < MATRIX_SIZE; u++) {
            numIndexes[u] = 0;
            //PasteIndexes[u] = 0;
        }
        //pasteIndex = 0;
        for (int j = 0; j < m->size; j++) {
            if (fscanf(f, "%lf", &num)) {
                if (num != 0) {
                    //printf("I found number %2.1lf\n", num);
                    isZero = 0;
                    numIndexes[j] = num;
                    //fill A
                    m->A[ALastIndex] = j;
                    //printf("added J to A. i: %d In A: %2.1lf  INDEX %d\n", i, m->A[ALastIndex], ALastIndex);
                    ALastIndex++;
                    m->A[ALastIndex] = num;
                    if (rowSaved == -1) {
                        rowSaved = m->a_knots_count + 1;
                    }
                    //m->rows[rowCounter] = i;
                    //rowCounter++;
                    m->a_knots_count++;
                    ALastIndex++;
                    //search for next 
                    m->A[ALastIndex] = 0; //pre
                    //printf("added 0 at pos %d\n", ALastIndex);
                    //PasteIndexes[pasteIndex] = (m->a_knots_count) * 3 - 1; //j
                    //pasteIndex++;
                    ALastIndex++;
                }
            }
        }
        //int pasteCounter = 0;
        double toPaste = 0;
        
        for (int k = 0; k < m->size; k++) {
            toPaste = 0;
            //printf("processing line %d\n", k);
            if (numIndexes[k] != 0) {
                for (int l = k+1; l < m->size; l++) {
                    if (numIndexes[l] != 0) {
                        toPaste = numIndexes[l];
                        //printf("for %2.2lf found next num %2.2lf\n", numIndexes[k], numIndexes[l]);
                        break;
                    }
                }
                //m->A[PasteIndexes[pasteCounter]] = toPaste;
                m->A[pasteCounter * 3 + 2] = toPaste;
                //printf("pasting next num %2.2lf at pos %d\n", toPaste, pasteCounter*3+2);
                pasteCounter++;
                //paste into index
            }
        }
        
        //fill M
        /*
        if (isZero == 1) {
            m->M[i] = 0;
        } else {
            m->M[i] = m->size * i;
        }
        */
        if (rowSaved == -1) {
            m->M[i] = 0;
        } else {
            m->M[i] = rowSaved;
        }
        rowSaved = -1;
    }

    fclose(f);
    return 1;
}

void print_matrix(Matrix *m, int option) {
    if (option == 0) {
        //strange method
        int raz = 0;
        printf("M:\n");
        printf("%d", m->M[0]);
        for (int i = 1; i < m->size; i++) {
            printf(" %d", m->M[i]);
        }
        printf("\nA:\n");
        printf("%2.1lf", m->A[0]);
        raz++;
        //printf("aknots %d\n", m->a_knots_count);
        for (int i = 1; i < (m->a_knots_count) * 3; i++) {
            printf(" %2.1lf", m->A[i]);
            raz++;
            if (raz == 3) {
                printf(" |");
                raz = 0;
            }
        }
        printf("\n");
    } else {
        //normal method
        for (int i = 0; i < m->size; i++) {
            if (m->M[i] == 0) {
                printf("0");
                for (int r = 1; r < m->size; r++) {
                    printf(" 0");
                }
                printf("\n");
            } else {
                for (int j = 0; j < m->size; j++) {
                    
                }
            }
        }
        /*
        for (int i = 0; i < m->size; i++) {
            printf("%lf \n", m->)
            for (int j = 1; j < m->size; j++) {
                printf
            }
        }
        */
    }
}

void delete_matrix(Matrix *m) {
    free(m);
    m = NULL;
}

void func(Matrix *m) {
    double max = 0;
    int rowIndex;
    for (int i = 0; i < m->a_knots_count; i++) {
        if (m->A[i * 3 + 1] > max) {
            max = m->A[i * 3 + 1];
            //rowIndex = m->rows[i];
            for (int t = 0; t < m->size; t++) {
                //printf("comparing M = %d with %d\n", m->M[t], i);
                if (m->M[t] == i) {
                    rowIndex = t;
                    break;
                }
            }
        }
    }
    printf("max elem %2.2lf at row %d\n", max, rowIndex);
    for (int i = 0; i < m->a_knots_count; i++) {
        if (m->rows[i] == rowIndex) {
            m->A[i * 3 + 1] = m->A[i * 3 + 1] / max;
        }
    }
}