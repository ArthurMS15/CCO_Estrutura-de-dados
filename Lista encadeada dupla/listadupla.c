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
