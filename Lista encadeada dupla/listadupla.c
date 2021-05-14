#include <stdio.h>
#include <stdlib.h>

typedef struct sElemento{
    struct sElemento *next;
    struct sElemento *prev;
    int dado;
} Elemento;

typedef struct sLista{
    struct sElemento *head;
    struct sElemento *tail;
    int size;
} Lista;

Lista* alocaLista();
Elemento* alocaElemento(int);
void insereElemento(Lista*, Elemento*, int);
int removeElemento(Elemento*, Lista*);
void imprimeListaNext(Lista*);
void imprimeListaPrev(Lista*);

int main(){

}

Elemento *alocaElemento(int d){
    Elemento *e;
    e=(Elemento*)malloc(d*sizeof(Elemento));
    e->next=NULL;
    e->prev=NULL;
    e->dado=d;
    return e;
}

Lista *alocaLista(){
    Lista *l;
    l=(Lista*)malloc(sizeof(Lista));
    l->head=NULL;
    l->tail=NULL;
    l->size=0;
    return l;
}

void insereElemento(Lista* l, Elemento* pivo, int dado){
    Elemento *ea=alocaElemento(dado);
    ea->dado=dado;
    if((pivo==NULL) && (l->size>0)){
        return -1;
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
    int dado;
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
            if(e->next=NULL){
                l->tail=e->prev;
            } else {
                e->next->prev=e->prev;
            }
        }
        dado=e->dado;
        free(e);
        l->size--;
        return dado;
    }
    return -1;
}

void imprimeListaNext(Lista* l){
    Elemento *ea=l->head; //elemento auxiliar
    while(ea!=NULL){
        printf("%d\t", ea->dado);
        ea=ea->next;
    }
    printf("NULL\n");
}

void imprimeListaPrev(Lista* l){
    Elemento *ea=l->tail; //elemento auxiliar
    while(ea!=NULL){
        printf("%d\t", ea->dado);
        ea=ea->prev;
    }
    printf("NULL\n");
}