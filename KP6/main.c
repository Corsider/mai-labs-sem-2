#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *f;
    f = fopen("data.bin", "wb");

    if (f == NULL) {
        fprintf(stderr, "Can't open file");
        exit(1);
    }

    int num = 123;
    int *p = &num;
    /*
    if (fwrite(p, sizeof(num), 1, f) != 1) {
        fprintf(stderr, "CANT WRITE");
    }
    */
    fclose(f);
}