#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
    List *list = list_create();
    int list_created = 0;

    while (1) {
        printf("%s\n", "What do you want to do?");
        printf("%s\n", "1) Print list");
        printf("%s\n", "2) Add new elem to list");
        printf("%s\n", "3) Remove elem from list");
        printf("%s\n", "4) Function");
        printf("%s\n", "5) Exit");
        printf("%s", "? - ");
        
        Iterator it;
        char c[STRING_SIZE];
        scanf("%s", c);
        
        if (atoi(c) == 1) { //////PRINT
            
            if (list_created) {
                printf("\nPrinting list...\n\n");
                list_print(list);
                printf("\n");
            } else {
                printf("\nList is empty\n\n");
            }
            
        } else if (atoi(c) == 2) { /////ADD
            if (list_created) {
                printf("\nAfter which one: ");
                scanf("%s", c);
                Iterator parent = find(list, c);
                if (parent.part != NULL) {
                    printf("String: ");
                    scanf("%s", c);
                    insert(list, &parent, c);
                    printf("Inserted. Printing list...\n\n");
                    list_print(list);
                    printf("\n");
                } else {
                    printf("No such element.\n\n");
                }
            } else {
                printf("\nCreate root elem: ");
                scanf("%s", c);
                it = push_back(list, c);
                list_forceFirstElem(list, c);
                printf("Created.\n\n");
                list_created = 1;
                list_print(list);
                printf("\n");
            }
        } else if (atoi(c) == 3) { //////REMOVE
            if (list_created) {
                printf("Which one: ");
                scanf("%s", c);
                //check if exists
                Iterator dl = find(list, c);
                if (dl.part != NULL) {
                    if (list_length(list) == 1) {
                        //list_destroy(list);
                        printf("List was deleted.\n\n");
                        list_created = 0;
                    } else {
                        delete(list, &dl);
                        printf("Deleted.\n\n");
                        list_print(list);
                        printf("\n");
                    }
                } else {
                    printf("No such element.\n\n");
                }
            } else {
                printf("\nList wasn't created.\n\n");
            }
        } else if (atoi(c) == 4) { /////FUNCTION
            if (list_created) {
                printf("Which one: ");
                scanf("%s", c);
                printf("\nExecuting function...\n\n");
                //if (list_length(l))
                if (list_function(list, c)) {
                    list_created = 0;
                }
                //if (list_length)
            } else {
                printf("\nList is empty.\n\n");
            }
            
        } else if (atoi(c) == 5) {
            printf("\nBye-bye!\n\n");
            break;
        } else if (atoi(c) == 0) {
            //printf("Start is %s\n", list->start->str);
            //printf("List end is %s\n", last(list).part->str);
            //print_connection(list);
            printf("%s", "No such option\n\n");
        } else {
            printf("%s", "No such option\n");
            printf("\n");
        }
    }
    list_destroy(list);
    return 0;
}