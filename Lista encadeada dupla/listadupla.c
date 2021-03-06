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
Elemento* pesquisarElementoNext(Lista*, int);
Elemento* pesquisarElementoPrev(Lista*, int);
void freeLista(Lista*);

int main(){
    Lista *l;
    l=alocaLista();

    removeElemento(l->tail, l); 
    insereElemento(l, l->tail, 1);
    
    imprimeListaNext(l);

    insereElemento(l, l->head, 2);

    imprimeListaNext(l);

    insereElemento(l, l->head->next, 3); 

    imprimeListaNext(l);
    imprimeListaPrev(l);

    removeElemento(l->tail, l); 

    imprimeListaNext(l);

    insereElemento(l, NULL, 4);
    insereElemento(l, NULL, 5);

    removeElemento(l->tail, l);

    imprimeListaNext(l);

    removeElemento(l->head, l);

    imprimeListaNext(l);

    insereElemento(l, l->tail, 1);

    imprimeListaNext(l);

    freeLista(l);
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
            if(e->next==NULL){
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
    printf("Erro: elemento NULL ou lista vazia\n");
    return -1;
}

void imprimeListaNext(Lista* l){
    Elemento *ea=l->head; //elemento auxiliar
    printf("NULL\t");
    while(ea!=NULL){
        printf("%d\t", ea->dado);
        ea=ea->next;
    }
    printf("NULL\n");
}

void imprimeListaPrev(Lista* l){
    Elemento *ea=l->tail; //elemento auxiliar
    printf("NULL\t");
    while(ea!=NULL){
        printf("%d\t", ea->dado);
        ea=ea->prev;
    }
    printf("NULL\n");
}

Elemento *pesquisarElementoNext(Lista* l, int dado){
    Elemento* aux=l->head;
    while(aux!=NULL){
        if(aux->dado==dado){
            return aux;
        }
        aux=aux->next; 
    }
    return NULL;
}

Elemento *pesquisarElementoPrev(Lista* l, int dado){
    Elemento* aux=l->tail;
    while(aux!=NULL){
        if(aux->dado==dado){
            return aux;
        }
        aux=aux->prev; 
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
