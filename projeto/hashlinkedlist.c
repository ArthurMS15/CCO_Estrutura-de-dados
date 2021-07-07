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
int find(char*);

int main(){
    for (int i = 0; i < M; i++){
        hashtable[i] = NULL;
    }
    //setando ponteiros
    FILE *file = fopen("teste.txt", "r");

    if(file == NULL){
        printf("Não foi possivel ler os nomes\n");
        exit(0);
    }
    //iniciando file

    char nome[100];
    while(fgets(nome, 100, file) != NULL){
        printf("%s", nome);
        int aux = create(nome);
    }
    

    fclose(file);

    for (int i = 0; i < M; i++){
        if (hashtable[i] != NULL){
            destroy(hashtable[i]);
        }
    }
    //free no hashtable
    return 0;
}

unsigned int create(char* name){
    int n = hash(name);
    node* nnode = malloc(sizeof(node));
    if(nnode == NULL){
        exit(1);
    } else {
        nnode->name = name;
        nnode->next = hashtable[n];
        hashtable[n] = nnode;
        //printf("%s", hashtable[23]->name);
    }
    return n;
}

unsigned int hash(char* str){
    //int sum=0;
    //for(int i=0; str[i] != '\0'; i++){
    //    sum += str[i];
    //}
    //return sum % M;
    int acumulador=0;
    for(int i=0; i < strlen(str); i++){
        int aux = str[i];
        acumulador = (31 * acumulador + str[i]) % M;
    }
    return acumulador;
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
