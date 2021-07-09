#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 29

typedef struct entry_t {
    int key;
    char *value;
    struct entry_t* next; // colisão
} entry_t;
// 1 entry in the hash table, a key of value at a pointer to another entry

typedef struct {
    entry_t **entries;
} ht_t;
//hash tabel itself, array of pointers to an entry

ht_t *ht_create(void);
unsigned int hash(int, char*);
void ht_set(ht_t *, int, const char *);
entry_t *ht_pair(int, const char *);
char *ht_get(ht_t *, int, const char *);
void ht_dump(ht_t *);
void ht_dumpslot(ht_t *, int);
void destroy(entry_t*);
void freeHashTable(ht_t *);

int main(){
    ht_t *ht = ht_create();
    //setando ponteiros
    FILE *file = fopen("nomes.txt", "r");

    if(file == NULL){
        printf("Não foi possivel ler os nomes\n");
        exit(0);
    }
    //iniciando file

    char *nome[100];
    int aux=0;
    while(fgets(nome, 100, file) != NULL){
        aux++;
        ht_set(ht, aux, nome);
    }

    //char *teste="1"; 
    //ht_set(ht, "1", teste);
    //ht_set(ht, "1", "2");
    //ht_set(ht, "3", "3");
    //ht_set(ht, "4", "4");
    //ht_set(ht, "5", "5");
    //ht_set(ht, "6", "6");
    //ht_set(ht, "7", "7");
    //se tiver chave igual um é substituído por outro

    ht_dumpslot(ht, 24);

    fclose(file);
    freeHashTable(ht);

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

unsigned int quantAlgarismos(int key){
    int count = 0;
    while(key != 0) {
       key = key / 10;
       count++;
    }
    return count;
}

unsigned int hash(int key, char *valuechar){
    unsigned long int value = 0;
    unsigned int i=0;
    unsigned int key_len = quantAlgarismos(key);

    for(; i < strlen(valuechar); ++i){
        value = 31 * value + valuechar[i];
    }

    value = value % M;
    //valor é maior que 0 e menor que M;
    return value;
}

void ht_set(ht_t *hashtable, int key, const char *value){
    unsigned int bucket = hash(key, value);

    entry_t *entry = hashtable->entries[bucket];

    if(entry == NULL){
        hashtable->entries[bucket] = ht_pair(key, value);
        return;
    }

    entry_t *prev;

    while (entry != NULL){

        if(entry->key==key){
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


entry_t *ht_pair(int key, const char *value){
    entry_t *entry = malloc(sizeof(entry) * 1);

    entry->value = malloc(strlen(value) + 1);

    entry->key=key;
    strcpy(entry->value, value);

    entry->next=NULL;

    return entry;
}

char *ht_get(ht_t *hashtable, int key, const char *value){
    unsigned int slot = hash(key, value);

    entry_t *entry = hashtable->entries[slot];

    if(entry == NULL){
        return NULL;
    }

    while(entry != NULL){
        if(entry->key == key){
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

        for(;;){
            printf("slot[%d]: %d=%s ", i, entry->key, entry->value);

            if(entry->next==NULL){
                break;
            }

            entry = entry->next;

        }

        printf("\n");

    }
}

void ht_dumpslot(ht_t *hashtable, int slot){
    int cont=0;
    for(int i=0;i<M;++i){
        entry_t *entry = hashtable->entries[i];

        if(entry == NULL){
            continue;
        }

        if(i==slot){
            for(;;){
                cont++;
                printf("slot[%d]: %d=%s ", i, entry->key, entry->value);

                if(entry->next==NULL){
                    break;
                }

                entry = entry->next;
            }

        printf("\n");
        }

    }
    printf("TEM: %d nomes", cont);
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