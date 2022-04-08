#include "functions.h"
#include <stdio.h>

void read_data(abiturient *rec, FILE *f) {
    fread(rec->lastname, sizeof(rec->lastname[0]), STR_SIZE, f);
    fread(rec->initials, sizeof(rec->initials[0]), STR_SIZE, f);
    fread(&(rec->gender), sizeof(rec->gender), 1, f);
    fread(&(rec->school_number), sizeof(rec->school_number), 1, f);
    fread(&(rec->has_medal), sizeof(rec->has_medal), 1, f);
    fread(&(rec->composition), sizeof(rec->composition), 1, f);
    fread(&(rec->marks), sizeof(rec->marks[0]), 3, f);
}

void write_to_data(abiturient *rec, FILE *f) {
    fwrite(rec->lastname, sizeof(rec->lastname[0]), STR_SIZE, f);
    fwrite(rec->initials, sizeof(rec->initials[0]), STR_SIZE, f);
    fwrite(&(rec->gender), sizeof(rec->gender), 1, f);
    fwrite(&(rec->school_number), sizeof(rec->school_number), 1, f);
    fwrite(&(rec->has_medal), sizeof(rec->has_medal), 1, f);
    fwrite(&(rec->composition), sizeof(rec->composition), 1, f);
    fwrite(&(rec->marks), sizeof(rec->marks[0]), 3, f);
}

void print_abits(abiturient saved[ABITCOUNT], int count) {
    printf("+----------+-------+---+----------+-------+-------------+-------+\n");
    printf("| Lastname | Init  | G | SchoolNo | Medal |    Marks    | Comp. |\n");
    printf("+----------+-------+---+----------+-------+-------------+-------+\n");
    for (int i = 0; i < count; i++) {
        printf("| %-8s | %-5s | %d | %-8d |   %d   | ", saved[i].lastname, saved[i].initials, saved[i].gender, saved[i].school_number, saved[i].has_medal);
        int k = 0;
        for (int j = 0; j < MARKSCOUNT; j++) {
            printf("%d ", saved[i].marks[j]);
            if (saved[i].marks[j] < 10) {
                k += 2;
            } else if (saved[i].marks[j] < 100) {
                k += 1;
            }
        }
        for (int r = 0; r < k; r++) {
            printf(" ");
        }
        printf("|   %d   |\n", saved[i].composition);
        printf("+----------+-------+---+----------+-------+-------------+-------+\n");
    }
}