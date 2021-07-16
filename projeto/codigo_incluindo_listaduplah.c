#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listadupla.h"

#define M 29

typedef struct ht_t {
    Elemento **entries;
} ht_t;
//hash table itself, array of pointers to an entry

void createandsetFile();
ht_t *ht_create(void);
unsigned int hash(const char *);
void ht_set(ht_t *, const char *);
Elemento *ht_pair(const char *);
const char *ht_get(ht_t *, const char *);
void ht_dumpquicksort(ht_t *);
void printHt(ht_t *);
void removeElement(ht_t *, const char *);
Elemento *midFind(ht_t *, Elemento*);
void destroy(Elemento*);
void freeHashTable(ht_t *);
void swap(Elemento*, Elemento*);
void quicksort(ht_t*, Elemento*, Elemento*);

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

    hashtable->entries = malloc(sizeof(Elemento*) * M); 
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

    Elemento *entry = hashtable->entries[bucket];

    if(entry == NULL){
        hashtable->entries[bucket] = ht_pair(value);
        return;
    }

    Elemento *aux;

    while (entry != NULL){
        aux = entry;
        entry = aux->next;
    }

    aux->next = ht_pair(value);
    aux->prev = ht_pair(value);
}


Elemento *ht_pair(const char *value){
    Elemento *entry = alocaElemento(value);
    return entry;
}

const char *ht_get(ht_t *hashtable, const char *value){
    unsigned int slot = hash(value);

    Elemento *entry = hashtable->entries[slot];

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
    for(int i=0;i<M;++i){
        Lista *l=alocaLista();
        Elemento *entry = hashtable->entries[i];

        if(entry == NULL){
            continue;
        }
        
        for(;;){
            insereElemento(l, entry->value);
            if(entry->next==NULL){
                break;}

            entry = entry->next;
        }
        quicksort(hashtable, l->head, l->tail);
    }
}

void printHt(ht_t *hashtable){
    int contall=0;
    int contslot=0;
    for(int i=0;i<M;++i){
        Elemento *entry = hashtable->entries[i];

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

void removeElement(ht_t *hashtable, const char *nome){
    for(int i=0;i<M;++i){
        Elemento *entry = hashtable->entries[i];

        if(entry == NULL){
            continue;
        }

        for(;;){
            Lista *l=alocaLista();
            
            if(strcmp(entry->value, nome) == 0){
                removeElemento(entry, l);
            }

            if(entry->next==NULL){
                break;}

            entry = entry->next;
        }
    }
}

Elemento *midFind(ht_t *hashtable, Elemento *head){
    int cont=0;
    int aux=0;
    Elemento *mid;
    for(int i=0;i<M;++i){
        Elemento *entry = hashtable->entries[i];

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

void destroy(Elemento *entry){
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
        Elemento *entry = hashtable->entries[i];

        if(entry==NULL){
            continue;
        } else {
            destroy(entry);
        }
    }   
}

void swap(Elemento *a, Elemento *b){
  char *aux = a->value;
  a->value = b->value;
  b->value = aux;
}

void quicksort(ht_t *ht, Elemento *start, Elemento *end){
  if (end != NULL && start != end && start != end->next){
    Elemento* i = start->prev;
    Elemento* pivot = midFind(ht, start);

    // Percorre a lista do início ao fim
    for (Elemento *j = start; j != end; j = j->next){
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