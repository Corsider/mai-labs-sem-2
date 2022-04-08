#include "functions.h"
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    FILE *f = fopen("data.bin", "rb");
    if (f == NULL) {
        fprintf(stderr, "Error while opening file.\n");
        exit(1);
    }
    abiturient saved[ABITCOUNT];
    for (int i = 0; i < ABITCOUNT; i++) {
        read_data(&saved[i], f);
    }
    fclose(f);
    //printing..
    print_abits(saved, ABITCOUNT);
    return 0;
}