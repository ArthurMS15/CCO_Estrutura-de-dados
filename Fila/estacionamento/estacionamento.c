#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sCarro{
    char placa[7];
    int manobra;
} Carro;

typedef struct sElemento{
    struct sElemento *next;
    struct sElemento *prev;
    Carro info;
} Elemento;

typedef struct sFila{
    Elemento *elemento;
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

Elemento *alocaElemento(Carro dado){
    Elemento *e;
    e=(Elemento*)malloc(sizeof(Elemento));
    e->info=dado;
    e->next=NULL;
    e->prev=NULL;
    return e;
}


