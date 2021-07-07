#include <stdio.h>
#include <stdlib.h>

#define M 26

typedef struct node {
    char* name;
    struct node* next;
    struct node* prev;
} node;

node* hashtable[M];

