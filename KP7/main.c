#include "matrix.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void throw_error() {
    printf("\n");
    printf("%s\n", "ERROR - Invalid input");
    printf("\n");
}

int check(char *c) {
    while (*c) {
        if ((*c < '0' || *c > '9') && (*c != '-') && (*c != '.')) {
            return 0;
        }
        *c++;
    }
    return 1;
}

int main(void)
{
    int matrixFilled = 0;
    Matrix *mat = create_matrix(10);
    //fill_matrix(mat);
    //print_matrix(mat, 0);
    int matrixSize;
    printf("Specify matrix size: ");
    scanf("%d", &matrixSize);

    while (1) {
        printf("%s\n", "What do you want to do?");
        printf("%s\n", "1) Fill matrix");
        printf("%s\n", "2) Print matrix");
        printf("%s\n", "3) Function");
        printf("%s\n", "4) Exit");
        printf("%s", "? - ");
        char c[100] = "";
        scanf("%s", c);
        if (!check(c)) {
            throw_error();
            continue;
        }
        
        if (!strcmp(c, "1")) {
            int value;
            printf("\nReading data.txt ...\n\n");
            if (fill_matrix(mat) == 1) {
                matrixFilled = 1;
            } else {
                printf("No such file. Please create data.txt file with your matrix.\n");
                //break;
            }
        } else if (!strcmp(c, "2")) {
            if (matrixFilled == 0) {
                printf("\nMatrix wasn't filled with data.\n\n");
                continue;
            }
            printf("\nSelect option 1/2:\n");
            scanf("%s", c);
            if (!check(c)) {
                throw_error();
                continue;
            }
            printf("\n");
            if (!strcmp(c, "1")) {
                print_matrix(mat, 0);
                printf("\n");
            } else if (!strcmp(c, "2")) {
                print_matrix(mat, 1);
                printf("\n");
            } else {
                printf("No such option.\n");
                continue;
            }
        } else if (!strcmp(c, "3")) {
            if (matrixFilled == 0) {
                printf("\nMatrix wasn't filled with data.\n\n");
                continue;
            }
            func(mat);
            printf("\nFunction called.\n\n");
            print_matrix(mat, 1);
            printf("\n");
        } else if (!strcmp(c, "4")) {
            printf("\nGoodbye!\n\n");
            break;
        } else {
            printf("%s", "No such option\n");
            printf("\n");
        }
    }

    delete_matrix(mat);
    return 0;
}