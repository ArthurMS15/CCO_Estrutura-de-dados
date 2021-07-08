#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 26

typedef struct node {
    char* key;
    char* value;
    struct node* next; // colisão
    struct node* prev; 
} node;
// 1 entry in the hash table, a key of value at a pointer to another entry

typedef struct {
    node **entries;
} ht;
//hash tabel itself, array of pointers to an entry

ht *ht_create(void);
unsigned int hash(char* str);
node *ht_pair(const char *key, const char *value);
node *ht_get(ht *hashtable, const char *key);
void ht_dump(ht *hashtable);
void createNode(ht *hashtable, const char *key, const char *value);
void destroy(node* node);
void freeHashTable(ht *hashtable);

int main(){
    ht *ht = ht_create();
    //setando ponteiros
    FILE *file = fopen("teste.txt", "r");

    if(file == NULL){
        printf("Não foi possivel ler os nomes\n");
        exit(0);
    }
    //iniciando file

    /*char nome[100];
    while(fgets(nome, 100, file) != NULL){
        printf("%s\n", nome);
        createNode(ht, "1", nome);
    }*/

    ht_dump(ht);

    fclose(file);
    freeHashTable(ht);

    return 0;
}

ht *ht_create(void){
    ht *hashtable = malloc(sizeof(ht)*1); //ponteiro para a hashtable

    hashtable->entries = malloc(sizeof(node*)*M); //x numbers of pointers to an entry/node (26 ponteiros, baseado no M)

    for(int i=0;i<M;++i){
        hashtable->entries[i] = NULL;
    } //inicializando os ponteiros
    return hashtable;
}

unsigned int hash(char* str){
    int acumulador=0;
    for(int i=0; i < strlen(str); i++){
        acumulador = (31 * acumulador + str[i]);
    }
    acumulador = acumulador % M;
    //valor é maior que 0 e menor que M;
    return acumulador;
}

node *ht_pair(const char *key, const char *value){
    node *node = malloc(sizeof(node) * 1);
    node->key = malloc(sizeof(key) + 1);
    node->value = malloc(sizeof(value) + 1);

    strcpy(node->key, key);
    strcpy(node->value, value);

    node->next=NULL;

    return node;
}

node *ht_get(ht *hashtable, const char *key){
    unsigned int slot = hash(key);
    node *node = hashtable->entries[slot];

    if(node==NULL){
        return NULL;
    }

    while(node != NULL){
        if(strcmp(node->key, key) == 0){
            return node->value;
        } 
        node = node->next;
    }

    return NULL;
}

void ht_dump(ht *hashtable){
    for(int i=0;i<M;++i){
        node *node = hashtable->entries[i];

        if(node==NULL){
            continue;
        }
        printf("slot[%4d]: ", i);
        for(;;){
            printf("%s=%s ", node->key, node->value);

            if(node->next==NULL){
                break;
            }
            node = node->next;
        }
        printf("\n");
    }
}

void createNode(ht *hashtable, const char *key, const char *value){
    unsigned int slot = hash(key);
    node *node = hashtable->entries[slot];
    if(node == NULL){
        hashtable->entries[slot] = ht_pair(key, value);
        return;
    }

    while (node != NULL){
        if(strcmp(node->key, key) == 0){
            free(node->value);
            node->value = malloc(strlen(value) + 1);
            strcpy(node->value, value);
            return;
        }

        node->prev = node;
        node = node->prev->next;
    }

    node->prev->next = ht_pair(key, value);
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

void freeHashTable(ht *hashtable){
    for(int i=0;i<M;++i){
        node *node = hashtable->entries[i];

        if(node==NULL){
            continue;
        } else {
            destroy(node);
        }
    }   
}