#include <stdio.h>
#include <stdlib.h>

typedef struct sElemento{
    struct sElemento *next;
    struct sElemento *prev;
    int dado;
} Elemento;

typedef struct sFila{
    struct sElemento *head;
    struct sElemento *tail;
    int size;
} Fila;

void insert(Fila*, int);
void removeF(Fila*);
Fila* alocaFila();
Elemento* alocaElemento(int);
void imprimeFila(Fila*);
int empty(Fila*);
void freeFila(Fila*);

int main(){
    Fila *f;
    f=alocaFila();
    insert(f, 1);
    insert(f, 2);
    insert(f, 3);
    imprimeFila(f);
    removeF(f);
    imprimeFila(f);
    insert(f, 3);
    imprimeFila(f);
    empty(f);
    removeF(f);
    imprimeFila(f);
    removeF(f);
    imprimeFila(f);
    removeF(f);
    empty(f);
    freeFila(f);
}

void insert(Fila* f, int d){
    Elemento *ea=alocaElemento(d);
    Elemento *pivo=f->tail;
    ea->dado=d;
    if(f->size==0){
        f->head=ea;
        f->tail=ea;
    } else {
        ea->next=pivo->next;
        ea->prev=pivo;
        if(pivo->next==NULL){
            f->tail=ea;
        } else {
            pivo->next->prev=ea;
        }
        pivo->next=ea;
    }
    f->size++;
}

void removeF(Fila* f){
    int dado;
    Elemento *e=f->head;
    if(f->size>0){
        f->head=e->next;
        if(f->head==NULL){
            f->tail=NULL;
        } else {
            e->next->prev=NULL;
        }
        dado=e->dado;
        free(e);
        f->size--;
        printf("Primeiro da lista removido\n");
        return dado;
    } else {
        printf("Erro: lista vazia\n");
        return -1;
    }
}

Fila *alocaFila(){
    Fila *f;
    f=(Fila*)malloc(sizeof(Fila));
    f->head=NULL;
    f->tail=NULL;
    f->size=0;
    return f;
}

Elemento *alocaElemento(int d){
    Elemento *e;
    e=(Elemento*)malloc(d*sizeof(Elemento));
    e->next=NULL;
    e->prev=NULL;
    e->dado=d;
    return e;
}

void imprimeFila(Fila* f){
    Elemento *ea=f->head; //elemento auxiliar
    printf("NULL\t");
    while(ea!=NULL){
        printf("%d\t", ea->dado);
        ea=ea->next;
    }
    printf("NULL\n");
}

int empty(Fila* f){
    if(f->size==0){
        printf("Sim a lista esta vazia\n");
        return 1;
    } else {
        printf("Nao a lista nao esta vazia\n");
        return 0;
    }
}

void freeFila(Fila* f){
    Elemento* aux = f->head;
    while(aux != NULL){
        aux=aux->next;
        removeF(f);
    }
    free(f);
}
