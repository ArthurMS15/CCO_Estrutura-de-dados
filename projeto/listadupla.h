#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sElemento{
    struct sElemento *next;
    struct sElemento *prev;
    char *value;
} Elemento;

typedef struct sLista{
    struct sElemento *head;
    struct sElemento *tail;
    int size;
} Lista;

Lista* alocaLista();
Elemento* alocaElemento(const char *);
void insereElemento(Lista *, Elemento*, char *);
int removeElemento(Elemento *, Lista *);
void imprimeListaNext(Lista *);
Elemento* pesquisarElementoNext(Lista*, char *);
void freeLista(Lista*);

Elemento *alocaElemento(const char *d){
    Elemento *entry = malloc(sizeof(entry) * 1);
    entry->value = malloc(strlen(d) + 1);

    strcpy(entry->value, d);

    entry->next=NULL;
    entry->prev=NULL;
    return entry;
}

Lista *alocaLista(){
    Lista *l;
    l=(Lista*)malloc(sizeof(Lista));
    l->head=NULL;
    l->tail=NULL;
    l->size=0;
    return l;
}

void insereElemento(Lista* l, Elemento* pivo, char * dado){
    Elemento *ea=alocaElemento(dado);
    ea->value=dado;
    if((pivo==NULL) && (l->size>0)){
        printf("Erro: pivo NULL apenas na insercao do primeiro elemento\n");
        return;
    }
    if(l->size==0){
        l->head=ea;
        l->tail=ea;
    } else {
        ea->next=pivo->next;
        ea->prev=pivo;
        if(pivo->next==NULL){
            l->tail=ea;
        } else {
            pivo->next->prev=ea;
        }
        pivo->next=ea;
    }
    l->size++;
}

int removeElemento(Elemento* e, Lista* l){
    const char *dado;

    if((e!=NULL) && (l->size>0)){
        if(e==l->head){
            l->head=e->next;
            if(l->head==NULL){
                l->tail=NULL;
            } else {
                e->next->prev=NULL;
            }
        } else {
            e->prev->next=e->next;
            if(e->next==NULL){
                l->tail=e->prev;
            } else {
                e->next->prev=e->prev;
            }
        }
        dado=e->value;
        free(e);
        l->size--;
        return 1;
    }
    printf("Erro: elemento NULL ou lista vazia\n");
    return 0;
}

void imprimeListaNext(Lista* l){
    Elemento *ea=l->head; //elemento auxiliar
    printf("NULL\t");
    while(ea!=NULL){
        printf("%d\t", ea->value);
        ea=ea->next;
    }
    printf("NULL\n");
}

Elemento *pesquisarElementoNext(Lista* l, char *dado){
    Elemento* aux=l->head;
    while(aux!=NULL){
        if(strcmp(aux->value, dado) == 0){
            return aux;
        }
        aux=aux->next; 
    }
    return NULL;
}

void freeLista(Lista* l){
    Elemento* aux = l->head;
    while(aux != NULL){
        aux=aux->next;
        removeElemento(aux->prev, l);
    }
    free(l);
}
