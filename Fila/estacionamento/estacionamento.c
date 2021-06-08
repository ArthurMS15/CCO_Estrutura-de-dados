#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

Fila *alocaFila();
Elemento *alocaElemento(Carro);

int main(){
    
    
}

Fila *alocaFila(){
    Fila *f;
    f=(Fila*)malloc(sizeof(Fila));
    f->size=0;
    return f;
}

Elemento *alocaElemento(int dado){
    Elemento *e;
    e=(Elemento*)malloc(sizeof(Elemento));
    e->dado=dado;
    e->next=NULL;
    e->prev=NULL;
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


