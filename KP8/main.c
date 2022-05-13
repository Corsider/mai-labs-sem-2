#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    /*
    List *test = list_create("hello");
    list_print(test);
    list_add(test, "world");
    list_add(test->next, "team");
    list_add(test, "rt");
    list_print(test);
    //list_print(test->next->next->next->next);
    printf("%d\n", list_length(test));
    list_remove(test, test->next);
    list_print(test);
    printf("lengh/..\n");
    printf("%d\n", list_length(test));
    printf("----\n");
    list_function(test, "f");
    list_destroy(test);
    */
    List *list = list_create("empty");
    int list_created = 0;

    /////////////////////////////////////////////////
    //
    //
    //    TODO: MAKE LIST CIRCLE! NOT SETTING NULLS TO ->next;
    //
    //
    /////////////////////////////////////////

    while (1) {
        printf("%s\n", "What do you want to do?");
        printf("%s\n", "1) Print list");
        printf("%s\n", "2) Add new elem to list");
        printf("%s\n", "3) Remove elem from list");
        printf("%s\n", "4) Function");
        printf("%s\n", "5) Exit");
        printf("%s", "? - ");
        char c[100] = "";
        char c1[100];
        scanf("%s", c);
        //fgets(c, 100, stdin);
        //printf("atoied %d\n", atoi(c));
        //if (!check(c)) {
        //    throw_error();
        //    continue;
        //}
        
        if (atoi(c) == 1) {
            list_print(list);
            printf("\n");
            /*
            if (list_created) {
                printf("\nPrinting list...\n\n");
                list_print(list);
            } else {
                printf("\nList is empty\n\n");
            }
            */
        } else if (atoi(c) == 2) {
            if (list_created) {
                printf("\nWhich one: ");
                scanf("%s", c1);
                list_add(list, c1);
                printf("\nAdded.\n");
                list_print(list);
                printf("\n");
            } else {
                printf("\nCreate root elem: ");
                scanf("%s", c1);
                //fgets(c1, 100, stdin);
                //list_destroy(list);
                //printf("Qurrent data was %s\n", list->data);
                //list->data = c1;
                //list->next = list;
                list_add(list, c1);
                list_remove(list, "empty");
                //printf("and now %s\n", list->data);
                printf("Created.\n\n");
                list_created = 1;
                list_print(list);
                printf("\n");
            }
        } else if (atoi(c) == 3) {
            if (list_created) {
                printf("Which one: ");
                scanf("%s", c);
                //check if exists
                if (list_find(list, c)) {
                    if (list_length(list) == 1) {
                        //list_destroy(list);
                        list_created = 0;
                        list->data = "empty";
                        printf("List was destroyed.\n\n");
                    } else {
                        list_remove(list, c);
                        printf("Removed.\n");
                        list_print(list);
                        printf("\n");
                    }
                } else {
                    printf("No such element.\n\n");
                }
                
            } else {
                printf("\nList wasn't created.\n\n");
            }
        } else if (atoi(c) == 4) {
            if (list_created) {
                printf("Which one: ");
                scanf("%s", c);
                printf("\nExecuting function...\n\n");
                list_function(list, c);
            } else {
                printf("\nList is empty.\n\n");
            }
            
        } else if (atoi(c) == 5) {
            printf("\nBye-bye!\n\n");
            break;
        } else {
            printf("%s", "No such option\n");
            printf("\n");
        }
    }
    list_destroy(list);
    return 0;
}