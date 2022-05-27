#include "map_n.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    Map *m = map_create();
    FILE *f = fopen("input_reversed", "r");
    map_read(m, f);
    fclose(f);

    while (1) {
        printf("%s\n", "What do you want to do?");
        printf("%s\n", "1) Print map");
        printf("%s\n", "2) Binary search");
        printf("%s\n", "3) Sort");
        printf("%s\n", "4) Exit");
        printf("%s", "? - ");
        
        char c[128];
        scanf("%s", c);
        
        if (atoi(c) == 1) { //////PRINT
            printf("\nPrinting map...\n\n");
            map_print(m);
            printf("\n");
        } else if (atoi(c) == 2) { /////BIN SEARCH
            if (m->sorted == 1) {
                printf("\nWhich element: ");
                scanf("%s", c);
                map_bin_search(m, c);
            } else {
                printf("\nMap is not sorted.\n\n");
            }
        } else if (atoi(c) == 3) { /////SORT
            map_sort(m);
            printf("\n");
        } else if (atoi(c) == 4) { /////EXIT
            printf("\nBye-bye!\n\n");
            break;
        } else {
            printf("%s", "\nNo such option\n");
            printf("\n");
        }
    }
    map_delete(m);
    return 0;
}