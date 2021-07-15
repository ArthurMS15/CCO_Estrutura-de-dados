#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 29

typedef struct entry_t {
    char *value;
    struct entry_t* next;
    struct entry_t* prev;
} entry_t;

typedef struct ht_t {
    entry_t **entries;
} ht_t;

void createandsetFile();
ht_t *ht_create(void);
unsigned int hash(const char *);
void ht_set(ht_t *, const char *);
entry_t *ht_pair(const char *);
char *ht_get(ht_t *, const char *);
void ht_dumpquicksort(ht_t *);
void printHt(ht_t *);
entry_t *midFind(ht_t *, entry_t*);
void destroy(entry_t*);
void freeHashTable(ht_t *);
void swap(entry_t*, entry_t*);
void quicksort(ht_t*, entry_t*, entry_t*);

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
    while(fgets(nome, 100, file) != NULL){
        ht_set(hashtable, nome);
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

void ht_set(ht_t *hashtable, const char *value){
    unsigned int bucket = hash(value);

    entry_t *entry = hashtable->entries[bucket];

    if(entry == NULL){
        hashtable->entries[bucket] = ht_pair(value);
        return;
    }

    entry_t *aux;

    while (entry != NULL){
        aux = entry;
        entry = aux->next;
    }

    aux->next = ht_pair(value);
    aux->prev = ht_pair(value);
}


entry_t *ht_pair(const char *value){
    entry_t *entry = malloc(sizeof(entry) * 1);
    entry->value = malloc(strlen(value) + 1);

    strcpy(entry->value, value);

    entry->next=NULL;
    entry->prev=NULL;

    return entry;
}

char *ht_get(ht_t *hashtable, const char *value){
    unsigned int slot = hash(value);

    entry_t *entry = hashtable->entries[slot];

    if(entry == NULL){
        return NULL;
    }

    while(entry != NULL){
        if(strcmp(entry->value, value) == 0){
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
        quicksort(hashtable, head, tail);
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
            printf("slot[%d]: %s", i, entry->value);

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

entry_t *midFind(ht_t *hashtable, entry_t* head){
    int cont=0;
    int aux=0;
    entry_t *mid;
    for(int i=0;i<M;++i){
        entry_t *entry = hashtable->entries[i];

        if(entry == NULL){
            continue;
        }

        for(;;){
            if(head==entry){
                aux++;
            }
            if(aux>=1){
                cont++;
            }

            if(entry->next==NULL){
                break;
            }

            entry = entry->next;
        }
        aux=0;
        cont=cont/2;
        for(;;){
            aux++;

            if(aux==cont){
                mid=entry;
                return mid;
            }

            if(entry->next==NULL){
                break;
            }

            entry = entry->next;
        }
    }
    return head;
}

void destroy(entry_t* entry){
    if(entry->next==NULL){
        free(entry);
    } else {
        destroy(entry->next);
        free(entry);
    }
    return;
}

void freeHashTable(ht_t *hashtable){
    for(int i=0;i<M;++i){
        entry_t *entry = hashtable->entries[i];

        if(entry==NULL){
            continue;
        } else {
            destroy(entry);
        }
    }   
}

void swap(entry_t *a, entry_t *b){
  char *aux = a->value;
  a->value = b->value;
  b->value = aux;
}

void quicksort(ht_t *ht, entry_t *start, entry_t *end){
  if (end != NULL && start != end && start != end->next){
    entry_t* i = start->prev;
    entry_t* pivot = midFind(ht, start);

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
    quicksort(ht, start, i->prev);
    quicksort(ht, i->next, end);
  }
}