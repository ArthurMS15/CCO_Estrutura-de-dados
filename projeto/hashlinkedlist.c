#include <stdio.h>
#include <stdlib.h>

#define M 26

typedef struct node {
    char* name;
    struct node* next;
    struct node* prev;
} node;

node* hashtable[M];

unsigned int hash(char*);
unsigned int create(char*);

int main(){
    for (int i = 0; i < M; i++){
        hashtable[i] = NULL;
    }
    //setando ponteiros

}

unsigned int create(char* name){
    int n = hash(name);
    node* node = malloc(sizeof(node));
    if(node == NULL){
        exit(1);
    } else {
        node->name = name;
        node->next = hashtable[n];
        hashtable[n] = node;
    }
    return n;
}

unsigned int hash(char* str){
    int sum=0;
    for(int i=0; str[i] != '\0'; i++){
        sum += str[i];
    }
    return sum % M;
}

