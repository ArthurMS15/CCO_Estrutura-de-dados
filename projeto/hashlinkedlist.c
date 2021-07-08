#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 3

typedef struct entry_t {
    char *key;
    char *value;
    struct entry_t* next; // colisão
} entry_t;
// 1 entry in the hash table, a key of value at a pointer to another entry

typedef struct {
    entry_t **entries;
} ht_t;
//hash tabel itself, array of pointers to an entry

ht_t *ht_create(void);
unsigned int hash(const char *);
void ht_set(ht_t *, const char *, const char *);
entry_t *ht_pair(const char *, const char *);
char *ht_get(ht_t *, const char *);
void ht_dump(ht_t *);
void createNode(ht_t *, const char *, const char *);
void destroy(entry_t*);
void freeHashTable(ht_t *);

int main(){
    ht_t *ht = ht_create();
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

    createNode(ht, "1", "em");
    createNode(ht, "2", "russian");
    createNode(ht, "3", "pizza");
    createNode(ht, "4", "doge");
    createNode(ht, "5", "pyro");
    createNode(ht, "6", "joost");
    createNode(ht, "7", "kalix");

    ht_dump(ht);

    fclose(file);
    //freeHashTable(ht);

    return 0;
}

ht_t *ht_create(void){
    ht_t *hashtable = malloc(sizeof(ht_t) * 1); //ponteiro para a hashtable

    hashtable->entries = malloc(sizeof(entry_t*) * M); 
    //x numbers of pointers to an entry/node (26 ponteiros, baseado no M)

    int i = 0;
    for(; i < M; ++i){
        hashtable->entries[i] = NULL;
    } //inicializando os ponteiros

    return hashtable;
}

unsigned int hash(const char* key){
    unsigned long int value =0 ;
    unsigned int i=0;
    unsigned int key_len = strlen(key);

    for(; i < key_len; ++i){
        value = 31 * value + key[i];
    }

    value = value % M;
    //valor é maior que 0 e menor que M;
    return value;
}

void ht_set(ht_t *hashtable, const char *key, const char *value){
    unsigned int bucket = hash(key);

    entry_t *entry = hashtable->entries[bucket];

    if(entry == NULL){
        hashtable->entries[bucket] = ht_pair(key, value);
        return;
    }

    entry_t *prev;

    while (entry != NULL){

        if(strcmp(entry->key, key) == 0){
            free(entry->value);
            entry->value = malloc(strlen(value) + 1);
            strcpy(entry->value, value);
            return;
        }

        prev = entry;
        entry = prev->next;
    }

    prev->next = ht_pair(key, value);
}


entry_t *ht_pair(const char *key, const char *value){
    entry_t *entry = malloc(sizeof(entry) * 1);
    entry->key = malloc(strlen(key) + 1);
    entry->value = malloc(strlen(value) + 1);

    strcpy(entry->key, key);
    strcpy(entry->value, value);

    entry->next=NULL;

    return entry;
}

char *ht_get(ht_t *hashtable, const char *key){
    unsigned int slot = hash(key);

    entry_t *entry = hashtable->entries[slot];

    if(entry == NULL){
        return NULL;
    }

    while(entry != NULL){
        if(strcmp(entry->key, key) == 0){
            return entry->value;
        } 
        entry = entry->next;
    }

    return NULL;
}

void ht_dump(ht_t *hashtable){
    for(int i=0;i<M;++i){
        entry_t *entry = hashtable->entries[i];

        if(entry == NULL){
            continue;
        }
        printf("slot[%4d]: ", i);

        for(;;){
            printf("%s=%s ", entry->key, entry->value);

            if(entry->next==NULL){
                break;
            }

            entry = entry->next;

        }

        printf("\n");

    }
}

void destroy(entry_t* node){
    if(node->next==NULL){
        free(node);
    } else {
        destroy(node->next);
        free(node);
    }
    return;
}

void freeHashTable(ht_t *hashtable){
    for(int i=0;i<M;++i){
        entry_t *node = hashtable->entries[i];

        if(node==NULL){
            continue;
        } else {
            destroy(node);
        }
    }   
}