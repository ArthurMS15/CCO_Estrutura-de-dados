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
void destroy(node*);

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

void destroy(node* node){
    if(node->next==NULL){
        free(node);
    } else {
        destroy(node->next);
        free(node);
    }
    return;
}

int find(char* name){
    int n = hash(name);
    if(hashtable[n] == NULL){
        for(node* aux=hashtable[n]; aux != NULL; aux=aux->next){
            if(aux->name == name){
                return 1;
            }
        }
    }
    return 0;
}
