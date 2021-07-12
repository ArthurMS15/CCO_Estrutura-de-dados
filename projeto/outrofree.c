#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 3

typedef struct entry_t {
    int key;
    char *value;
    struct entry_t* next; // colisão
    struct entry_t* prev;
} entry_t;
// 1 entry in the hash table, a key of value at a pointer to another entry

typedef struct {
    entry_t **entries;
} ht_t;
//hash table itself, array of pointers to an entry

ht_t *ht_create(void);
unsigned int hash(int, const char *);
void ht_set(ht_t *, int, const char *);
entry_t *ht_pair(int, const char *);
char *ht_get(ht_t *, int, const char *);
void ht_dumpquicksort(ht_t *);
void ht_dumpslotquicksort(ht_t *, int);
void destroy(entry_t*);
void freeHashTable(ht_t *);
void swap(entry_t*, entry_t*);
void quicksort(entry_t*, entry_t*);

int main(){
    ht_t *ht = ht_create();
    //setando ponteiros
    FILE *file = fopen("testemenor.txt", "r");

    if(file == NULL){
        printf("Não foi possivel ler os nomes\n");
        exit(0);
    }
    //iniciando file

    char nome[100];
    int aux=0;
    while(fgets(nome, 100, file) != NULL){
        aux++;
        ht_set(ht, aux, nome);
    }

    ht_dumpquicksort(ht);
    printf("quicksort feito\n\n");
    ht_dumpquicksort(ht);

    //fclose(file);
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

unsigned int hash(int key, const char *valuechar){
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

    entry_t *aux;

    while (entry != NULL){

        if(entry->key==key){
            free(entry->value);
            entry->value = malloc(strlen(value) + 1);
            strcpy(entry->value, value);
            return;
        }

        aux = entry;
        entry = aux->next;
    }

    aux->next = ht_pair(key, value);
}


entry_t *ht_pair(int key, const char *value){
    entry_t *entry = malloc(sizeof(entry) * 1);

    entry->value = malloc(strlen(value) + 1);

    entry->key=key;
    strcpy(entry->value, value);

    entry->next=NULL;
    entry->prev=NULL;

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
            cont++;
            printf("slot[%d]: %d=%s ", i, entry->key, entry->value);

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
        printf("\nHEAD quick: %s\n", head->value);
        if(cont<=1){
          tail=head;
        }
        printf("TAIL quick: %s\n", tail->value);
        printf("TEM: %d nomes\n", cont);
        cont=0;
        printf("\n");
        quicksort(head, tail);
    }
}

void ht_dumpslotquicksort(ht_t *hashtable, int slot){
    int cont=0;
    entry_t *head;
    entry_t *tail;
    for(int i=0;i<M;++i){
        entry_t *entry = hashtable->entries[i];

        if(entry == NULL){
            continue;
        }

        if(i==slot){
            for(;;){
                cont++;
                printf("slot[%d]: %d=%s ", i, entry->key, entry->value);
                
                if(cont==1){
                    head=entry;
                }

                if(entry->next==NULL){
                    break;
                }
                
                entry = entry->next;
                if(cont>1){
                  tail=entry;
                } else {
                  tail=head;
                }
            }
        
        printf("\n");
      }
    }
    quicksort(head, tail);
    printf("HEAD quick: %s\n", head->value);
    printf("TAIL quick: %s\n", tail->value);
    printf("TEM: %d nomes\n", cont);
}

void destroy(entry_t* node){
    free(node->value);
    free(node);
}

void freeHashTable(ht_t *hashtable){
    // Frees the table
    for (int i=0; i<M; i++) {
        entry_t *entry = hashtable->entries[i];
        if (entry != NULL)
            destroy(entry);
    }
 
    free(hashtable->entries);
    free(hashtable);
}

void swap(entry_t* a, entry_t* b){
  char *aux = a->value;
  a->value = b->value;
  b->value = aux;
}

void quicksort(entry_t* start, entry_t* end){
  if (end != NULL && start != end && start != end->next){
    entry_t* i = start->prev;
    entry_t* pivo = end;
    char temp[20];

    // Percorre a lista do início ao fim
    for (entry_t *j = start; j != end; j = j->next){
      // Se o valor for menor que o pivô, trocar com o i
      
      if (strcmp(j->value, pivo->value) <= 0){
        i = (i == NULL ? start : i->next);
        swap(i, j);
      }
    }
    // Coloca o pivô no lugar certo
    i = (i == NULL ? start : i->next);
    swap(i, pivo);

    // Ordena as duas partes da lista
    quicksort(start, i->prev);
    quicksort(i->next, end);
  }
}
// quicksort head, tail da lista; PROBLEMA NO I 