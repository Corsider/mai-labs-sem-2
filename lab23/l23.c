#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct node {
    struct node ** children;
    int count;
    int key;
} node;

//functions
node *make_node(int x) {
    node *n = (node *)malloc(sizeof(node));
    n->key = x;
    n->count = 0;
    n->children = NULL;
    return n;
}

void free_node(node *n) {
    for (int i = 0; i < n->count; i++) {
        if (n->children[i] != NULL) {
            free_node(n->children[i]);
        }
    }
    //deleted
    free(n->children);
    n->children = NULL; //deleting field
    free(n);
    n = NULL; //deleting node
}

node *find_node(node *n, int key) {
    if (n->key == key) {
        return n;
    }
    if (n->count > 0) {
        for (int i = 0; i < n->count; i++) {
            node * nn = find_node(n->children[i], key);
            if (nn) {
                return nn;
            }
        }
        return NULL; //no more children
    } else {
        return NULL; //no more children
    }
}

void add_node(node *n, int parent, int x) {
    node *pnt = find_node(n, parent);
    if (pnt) {
        if (pnt->count > 0) {
            //adding memory for new child
            pnt->children = (node **)realloc(pnt->children, sizeof(node *) * (pnt->count + 1));
            //adding child
            int c = pnt->count;
            pnt->children[c] = make_node(x);
            //incrementing count
            pnt->count++;
        } else {
            //adding child, malloc
            pnt->children = (node **)malloc(sizeof(node *));
            pnt->children[0] = make_node(x);
            pnt->count = 1;
        }
    } else {
        printf("%s", "[ERROR] NO PARENTS FOR THIS KEY WERE FOUND\n");
    }
}

void print_node_tabs(node *n, int depth) {
    for (int i = 0; i < depth; i++) {
        printf("\t");
    }
    printf("%d", n->key);
    printf("\n");
    depth++;
    for (int i = 0; i < n->count; i++) {
        int depthN = depth;
        print_node_tabs(n->children[i], depthN);
    }
}

void print_node(node *n, int depth) {
    for (int i = 0; i < depth; i++) {
        if (i < depth - 1) {
            printf("| ");
        } else {
            printf("|=");
        }
    }
    printf("%d", n->key);
    printf("\n");
    depth++;
    for (int i = 0; i < n->count; i++) {
        int depthN = depth;
        print_node(n->children[i], depthN);
    }
}

void print_tree(node *n) {
    print_node(n, 0);
}

node *find_parent(node *n, int key) {
    if (n->count > 0) {
        for (int i = 0; i < n->count; i++) {
            if (n->children[i]->key == key) {
                return n;
            } else {
                node *p = find_parent(n->children[i], key);
                if (p != NULL) {
                    return p;
                }
            }
        }
        return NULL;
        /*
        for (int i = 0; i < n->count; i++) {
            node *p = find_parent(n->children[i], key);
            if (p) {
                return p;
            }
        }
        */
    } else {
        return NULL;
    }
}

void remove_node(node *n, int key) {
    node *nn = find_node(n, key);
    node *pnt = find_parent(n, key);
    //printf("%s %d\n", "Parent is ", pnt->key);
    int index;
    for (int i = 0; i < pnt->count; i++) {
        if (pnt->children[i]->key == key) {
            index = i;
            break;
        }
    }
    free_node(nn);
    for (int i = index; i < pnt->count-1; i++) {
        pnt->children[i] = pnt->children[i+1];
    }
    pnt->count--;
}

int tree_power(node *n, int max) {
    //printf("%s %d %s %d\n", "recieved MAX", max, "node", n->key);
    int k = n->count;
    
    if (k > max) {
        max = k;
        //printf("%s %d %s %d\n", "New MAX", max, "was at node", n->key);
    }
    
    for (int i = 0; i < n->count; i++) {
        
        k = tree_power(n->children[i], max);
        if (k > max) {
            max = k;
        }
    }
    return max;
}

int nodes_with_max_power(node *n, int max, int k) {
    if (n->count == max) {
        k++;
        //printf("%s %d %s %d\n", "Node", n->key, "power", n->count);
    }
    for (int i = 0; i < n->count; i++) {
        int s = nodes_with_max_power(n->children[i], max, k);
        k = s;
    }
    return k;
}

int get_start(node *n) {
    return n->key;
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

void throw_error() {
    printf("\n");
    printf("%s\n", "ERROR - invalid input");
    printf("\n");
    //scanf("%*[^\n]");
}

int main(void)
{
    //making tree
    node *n = NULL;
    
    //MENU
    //int cont = 0;
    int tp;
    int treeExists = 0;
    while (1) {
        //loop
        int start;
        int tp;
        int cont = 0;
        if (treeExists == 1) {
            tp = tree_power(n, 0);
            start = get_start(n);
        }
        
        printf("%s\n", "What do you want to do?");
        printf("%s\n", "1) Add new node");
        printf("%s\n", "2) Print tree");
        printf("%s\n", "3) Print node");
        printf("%s\n", "4) Remove node");
        printf("%s\n", "5) Number of nodes, power of which is equal to tree's power");
        printf("%s\n", "6) Exit");
        printf("%s", "Decide. ");
        char c[100] = "";
        //scanf("%c", &c);
        /*
        if ((c != '\n') && (c >= '0' && c <= '9')) {
            cont = c - 48;
        } else {
            printf("Your input is incorrect\n\n");
            continue;
        }
        */
       /*
        int ok = scanf("%d", &cont);
        if (!ok) {
            printf("\n");
            printf("Invalid input!\n");
            continue;
        }
       */
        //fgets(c, 100, stdin);
        //sscanf(c, "%d", &cont);
        //if (check_str(c) == 0) {
        //    printf("%s\n", "BAAD");
        //    continue;
        //}
        //int error;
        scanf("%s", c);
        if (!check(c)) {
            throw_error();
            continue;
        }
        //cont = atoi(c);

        /*
        int error = scanf("%d", &cont);
        if (error != 1) {
            throw_error();
            continue;
        }
        */

        printf("\n");
        
        if (!strcmp(c, "1")) {
            int parent = 0;
            int val = 0;
            printf("%s\n", "Adding new node. Which one?");
            if (treeExists == 1) {
                printf("%s\n", "Enter parent node and new node's key value");
                printf("%s", "PARENT ");
                scanf("%s", c);
                if (!check(c)) {
                    throw_error();
                    continue;
                }
                parent = atoi(c);
                printf("%s", "VALUE ");
                scanf("%s", c);
                if (!check(c)) {
                    throw_error();
                    continue;
                }
                val = atoi(c);
            } else {
                printf("%s\n", "Enter parent node:");
                scanf("%s", c);
                if (!check(c)) {
                    throw_error();
                    continue;
                }
                val = atoi(c);
            }
            printf("\n");
            if (treeExists == 0) {
                n = make_node(val);
                treeExists = 1;
                printf("%s\n", "Added. Now tree looks like this:");
                printf("\n");
                print_tree(n);
                printf("\n");
                continue;
            }
            if (find_node(n, parent)) {
                if (find_node(n, val)) {
                    printf("%s\n", "This key already exists");
                } else {
                    add_node(n, parent, val);
                    printf("%s\n", "Added. Now tree looks like this:");
                    printf("\n");
                    print_tree(n);
                    treeExists = 1;
                }
            } else {
                printf("%s\n", "No such parent was found");
            }
            printf("\n");
        } else if (!strcmp(c, "2")) {
            printf("%s\n", "Printing tree...");
            printf("\n");
            if (treeExists == 1) {
                print_tree(n);
            } else {
                printf("Tree is empty\n");
            }
            printf("\n");
        } else if (!strcmp(c, "3")) {
            if (treeExists == 0) {
                printf("Tree is empty\n");
                printf("\n");
                continue;
            }
            int kkey;
            printf("%s\n", "Which node and it's children to print?");
            scanf("%s", c);
            if (!check(c)) {
                throw_error();
                continue;
            }
            kkey = atoi(c);
            printf("\n");
            if (find_node(n, kkey)) {
                print_node(find_node(n, kkey), 0);
            } else {
                printf("%s\n", "No such node was found");
            }
            printf("\n");
        } else if (!strcmp(c, "4")) {
            int dkey;
            if (treeExists == 0) {
                printf("Tree is empty\n");
                printf("\n");
                continue;
            }
            printf("%s\n", "Select node's key to delete");
            scanf("%s", c);
            if (!check(c)) {
                throw_error();
                continue;
            }
            dkey = atoi(c);
            printf("\n");
            if (find_node(n, dkey) && dkey != start) {
                remove_node(n, dkey);
                printf("%s\n", "Now tree looks like this:");
                printf("\n");
                print_tree(n);
            } else if (dkey == start) {
                free_node(n);
                treeExists = 0;
                printf("%s\n", "Tree was deleted");
            } else {
                printf("%s\n", "No node with such key was found");
            }
            printf("\n");
        } else if (!strcmp(c, "5")) {
            if (treeExists == 0) {
                printf("Tree is empty\n");
                printf("\n");
                continue;
            }
            int k = 0;
            int np = nodes_with_max_power(n, tp, 0);
            printf("%s %d\n", "Nodes with tree's power:", np);
            printf("\n");
        } else if (!strcmp(c, "6")) {
            break;
        } else {
            printf("%s", "No such option\n");
            printf("\n");
        }
    }
    if (treeExists == 1) {
        free_node(n);
    }
    
    return 0;
}