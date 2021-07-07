#include <stdio.h>
#include <stdlib.h>

#define M 26

typedef struct node {
    char* name;
    struct node* next;
    struct node* prev;
} node;

node* hashtable[M];

//create, delete, find

int main(){
    for (int i = 0; i < M; i++){
        hashtable[i] = NULL;
    }
    //setando ponteiros

}

unsigned int create(char* n){
    int n = hash(n);
}

unsigned int hash(char* str){
    int sum=0;
    for(int i=0; str[i] != '\0'; i++){
        sum += str[i];
    }
    return sum % M;
}

