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
Elemento *alocaElemento(int);
void insert(Fila*, int);
void imprimeFila(Fila*);
int empty(Fila*);


int main(){
    Fila *f;
    f=alocaFila();
    insert(f, 1);
    insert(f, 2);
    insert(f, 3);
    
    imprimeFila(f);
    
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

void insert(Fila* f, int d){
    Elemento *ea=alocaElemento(d);
    Elemento *pivo=f->tail;
    ea->dado=d;
    if(f->size<10){ 
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
    } else {
        printf("Estacionamento lotado, nao pode haver mais de 10 carros\n");
    }
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

/*void freeFila(FilaAscendente* f){
    Elemento* aux = f->head;
    while(aux != NULL){
        aux=aux->next;
        removeElemento(aux->prev, f);
    }
    free(f);
}*/


