#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *f;
    f = fopen("data.bin", "rb");

    if (f == NULL) {
        fprintf(stderr, "Can't open file. Exiting...\n");
        exit(1);
    }

    if (argc != 2) {
        fprintf(stderr, "Only one argument required.\n");
        exit(1);
    }

    int p = atoi(argv[1]);
    int indexes[ABITCOUNT];
    int marks[ABITCOUNT];

    abiturient saved[ABITCOUNT];
    for (int i = 0; i < ABITCOUNT; i++) {
        read_data(&saved[i], f);
    }
    printf("Processing...\n");
    for (int i = 0; i < ABITCOUNT; i++) {
        if (saved[i].gender == 1) {
            int k = 1;
            int notok = 0;
            int reference = saved[i].marks[0];
            int sum = reference;
            for (int j = 1; j < MARKSCOUNT; j++) {
                if (saved[i].marks[j] == reference) {
                    k += 1;
                }
                sum += saved[i].marks[j];
            }
            if (k == 3) {
                if (sum < p) {
                    indexes[i] = 1;
                }
            }
        }
    }
    //indexes filled and ready
    int found = 0;
    int count = 0;
    for (int i = 0; i < ABITCOUNT; i++) {
        if (indexes[i] == 1) {
            found = 1;
            count += 1;
        }
    }
    if (found == 1) {
        //printing
        abiturient saved2[ABITCOUNT];
        int ind = 0;
        for (int i = 0; i < ABITCOUNT; i++) {
            if (indexes[i] == 1) {
                saved2[ind] = saved[i];
                ind += 1;
            }
        }
        print_abits(saved2, count);
    } else {
        printf("No such abiturients were found.\n");
    }
    fclose(f);
}