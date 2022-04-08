#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

abiturient abits[ABITCOUNT] = {
    {"Ivanov", "I. I.", 0, 10, 1, {90, 90, 90}, 1},
    {"Ivanova", "E. I.", 1, 10, 0, {45, 89, 76}, 1},
    {"Sidorov", "S. E.", 0, 345, 0, {78, 66, 99}, 1},
    {"Petrova", "A. S", 1, 56, 1, {67, 55, 81}, 1},
    {"Mashina", "D. D.", 1, 56, 1, {78, 75, 49}, 1},
    {"Durov", "E. F.", 0, 789, 1, {100, 89, 93}, 1},
    {"Sashina", "A. R.", 1, 123, 0, {56, 45, 66}, 1}
};

int main(int argc, char const *argv[]) {
    //GENERATE IF FILE CREATED, CREATE FILE AND GENERATE IF NOT
    printf("Generating data...\n");

    FILE *f = fopen("data.bin", "wb+");
    if (f == NULL) {
        fprintf(stderr, "Something went wrong while opening file.\n");
        exit(1);
    }
    for (int i = 0; i < ABITCOUNT; i++) {
        write_to_data(&abits[i], f);
    }
    fclose(f);
    printf("DB generated: data.bin\n");
    return 0;
}