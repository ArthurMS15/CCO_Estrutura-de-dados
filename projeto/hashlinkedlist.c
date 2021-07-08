#include <stdio.h>
#include <stdlib.h>

#define M 26

typedef struct node {
    char* name;
    node* next;
    node* prev;
} node;

int hashFunction(char*);
unsigned int create(char*);
void destroy(node*);
void removeSpec(char*);
int find(char*);

int main(){
    node* hashtable[M];
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
        //printf("%d", aux);
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
    int n = hashFunction(name);
    node* hashtable[M];
    node* entry = hashtable[M];
    node* top[M];
    for (int i = 0; i < M; i++) {
        hashtable[i] = NULL;
        top[i] = NULL;
    }

    if(entry == NULL){
        entry = malloc(sizeof(node));
        if(entry == NULL){
            exit(1);
        } else {
            entry->name = name;
            entry->next = NULL;
            entry->prev = NULL;
            hashtable[n] = entry;
            top[n] = entry;
        }
    } else {
        while (entry != NULL){
            entry = entry->next;
        }
        entry = malloc(sizeof(node));
        if(entry == NULL){
            exit(1);
        } else {
            entry->name = name;
            entry->next = NULL;
            entry->prev = top[n];
            top[n]->next = entry;
            top[n] = entry;
        }
    }
    return n;
}

int hashFunction(char* str){
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

void removeSpec(char* name){
    node* hashtable[M];
    node* top[M];
    int n = hashFunction(name);
    node* entry = hashtable[n];
    if (entry->name != name || entry == NULL) {
        printf("Não foi encontrado o nome: %s na chave: %d OU a chave está vazia\n", name, n);
        return;
    }
    // if some values are present at that key &
    // traversing the list and removing all values
    while (entry != NULL) {
        if (entry->next == NULL) {
            if (entry->prev == NULL) {
                hashtable[n] = NULL;
                top[n] = NULL;
                destroy(entry);
                break;
            }
            else {
                top[n] = entry->prev;
                top[n]->next = NULL;
                destroy(entry);
                entry = top[n];
            }
        }
        entry = entry->next;
    }
    printf("Elemento excluído com sucesso da chave: %d\n", n);
}

int find(char* name){
    //aplying hash to find
    //index for given name
    int n = hashFunction(name);
    node* hashtable[M];
    if(hashtable[n] == NULL){
        for(node* aux=hashtable[n]; aux != NULL; aux=aux->next){
            if(aux->name == name){
                printf("Elemento encontrado com sucesso na chave: %d\n", n);
                return 1;
            }
        }
    }        
    return 0;
}
