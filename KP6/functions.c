#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

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