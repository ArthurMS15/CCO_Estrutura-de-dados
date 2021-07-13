#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 29

typedef struct entry_t {
    int key;
    char *value;
    struct entry_t* next;
    struct entry_t* prev;
} entry_t;
// 1 entry in the hash table, a key of value at a pointer to another entry

typedef struct lista{
    struct entry *head;
    struct entry *tail;
    int size;
} lista;

typedef struct ht_t {
    entry_t **entries;
} ht_t;
//hash table itself, array of pointers to an entry

void createandsetFile();
ht_t *ht_create(void);
unsigned int hash(const char *);
void ht_set(ht_t *, int, const char *);
entry_t *ht_pair(int, const char *);
char *ht_get(ht_t *, int, const char *);
void ht_dumpquicksort(ht_t *);
void printHt(ht_t *);
void destroy(entry_t*);
void freeHashTable(ht_t *);
void swap(entry_t*, entry_t*);
void quicksort(entry_t*, entry_t*);

int main(){
    ht_t *ht = ht_create();
    //seting pointers
    createandsetFile(ht);
    //initializing file
    ht_dumpquicksort(ht);
    printHt(ht);

    freeHashTable(ht);

    return 0;
}

void createandsetFile(ht_t *hashtable){

    FILE *file = fopen("nomes.txt", "r");

    if(file == NULL){
        printf("Não foi possivel ler os nomes\n");
        return;
    }

    char nome[100];
    int aux=0;
    while(fgets(nome, 100, file) != NULL){
        aux++;
        ht_set(hashtable, aux, nome);
    }
    fclose(file);
}

ht_t *ht_create(void){
    ht_t *hashtable = malloc(sizeof(ht_t) * 1); //ponteiro para a hashtable

    hashtable->entries = malloc(sizeof(entry_t*) * M); 
    //x numbers of pointers to an entry/node (29 ponteiros, baseado no M)

    int i = 0;
    for(; i < M; ++i){
        hashtable->entries[i] = NULL;
    } //inicializando os ponteiros

    return hashtable;
}

unsigned int hash(const char *valuechar){
    unsigned long int value = 0;
    unsigned int i=0;

    for(; i < strlen(valuechar); ++i){
        value = 31 * value + valuechar[i];
    }

    value = value % M;
    //valor é maior que 0 e menor que M;
    return value;
}

void ht_set(ht_t *hashtable, int key, const char *value){
    unsigned int bucket = hash(value);

    entry_t *entry = hashtable->entries[bucket];

    if(entry == NULL){
        hashtable->entries[bucket] = ht_pair(key, value);
        return;
    }

    entry_t *aux;

    while (entry != NULL){
        aux = entry;
        entry = aux->next;
    }

    aux->next = ht_pair(key, value);
    aux->prev = ht_pair(key, value);
}


entry_t *ht_pair(int key, const char *value){
    entry_t *entry = malloc(sizeof(entry) * 1);
    entry->key = (int)malloc(sizeof(key) * 1);
    entry->value = malloc(strlen(value) + 1);

    entry->key=key;
    strcpy(entry->value, value);

    entry->next=NULL;
    entry->prev=NULL;

    return entry;
}

char *ht_get(ht_t *hashtable, int key, const char *value){
    unsigned int slot = hash(value);

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

void ht_dumpquicksort(ht_t *hashtable){
    int cont=0;
    entry_t *head;
    entry_t *tail;
    for(int i=0;i<M;++i){
        entry_t *entry = hashtable->entries[i];

        if(entry == NULL){
            continue;
        }
        
        for(;;){
            if(cont==1){
              head=entry;
            }

            if(entry->next==NULL){
                break;
            }

            entry = entry->next;
            if(cont>1){
              tail=entry;
            }
        }
        if(cont<=1){
          tail=head;
        }
        quicksort(head, tail);
    }
}

void printHt(ht_t *hashtable){
    int contall=0;
    int contslot=0;
    for(int i=0;i<M;++i){
        entry_t *entry = hashtable->entries[i];

        if(entry == NULL){
            continue;
        }
        
        for(;;){
            contall++;
            contslot++;
            printf("slot[%d]: %d=%s ", i, entry->key, entry->value);

            if(entry->next==NULL){
                break;
            }

            entry = entry->next;
        }
        printf("\nNumber of entries in slot[%d]: %d\n", i, contslot);
        contslot=0;
    } 
    printf("Number of entries in all hashtable: %d\n", contall);
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

void swap(entry_t* a, entry_t* b){
  char *aux = a->value;
  a->value = b->value;
  b->value = aux;
}

void quicksort(entry_t* start, entry_t* end){
  if (end != NULL && start != end && start != end->next){
    entry_t* i = start->prev;
    entry_t* pivot = end;

    // Percorre a lista do início ao fim
    for (entry_t *j = start; j != end; j = j->next){
      // Se o valor for menor que o pivô, trocar com o i
      
      if (strcmp(j->value, pivot->value) <= 0){
        i = (i == NULL ? start : i->next);
        swap(i, j);
      }
    }
    // Coloca o pivô no lugar certo
    i = (i == NULL ? start : i->next);
    swap(i, pivot);

    // Ordena as duas partes da lista
    quicksort(start, i->prev);
    quicksort(i->next, end);
  }
}