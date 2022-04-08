#ifndef _FUNCTIONS_
#define _FUNCTIONS_

#include <stdio.h>

#define STR_SIZE 50
#define ABITCOUNT 7
#define MARKSCOUNT 3

typedef struct _abiturient {
    char lastname[STR_SIZE];
    char initials[STR_SIZE];
    int gender; //0 - male, 1 - female
    int school_number;
    int has_medal;
    int marks[MARKSCOUNT];
    int composition;
} abiturient;

void write_to_data(abiturient *abit, FILE *f);
void read_data(abiturient *abit, FILE *f);

#endif