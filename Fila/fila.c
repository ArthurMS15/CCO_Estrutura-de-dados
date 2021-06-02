#include <stdio.h>
#include <stdlib.h>

typedef struct sElemento{
    struct sElemento *next;
    struct sElemento *prev;
    int dado;
} Elemento;

typedef struct sFila{
    struct sElemento *front;
    struct sElemento *rear;
    int size;
} Fila;

int main(){
    Fila *f;
    f=alocaFila();
}

void insert(Fila* f, int d){
    Elemento *ea=alocaElemento(d);
    Elemento *pivo=f->rear;
    ea->dado=d;
    if(f->size==0){
        f->front=ea;
        f->rear=ea;
    } else {

    }
    f->rear++;
    f->size+=(f->rear - f->front + 1);
}

Fila *alocaFila(){
    Fila *f;
    f=(Fila*)malloc(sizeof(Fila));
    f->front=0;
    f->rear=-1;
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

int empty(Fila* f){
    if(f->rear<f->front){
        return 1;
    } else {
        return 0;
    }
}