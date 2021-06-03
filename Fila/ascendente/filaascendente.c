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
    int front;
    int rear;
    int size;
} FilaAscendente;

void insert(FilaAscendente*, int);
void removeElemento(FilaAscendente*);
FilaAscendente *alocaFila();
Elemento *alocaElemento(int);
void imprimeFila(FilaAscendente*);
int empty(FilaAscendente* fa);

int main(){
    FilaAscendente *fa;
    fa=alocaFila();
    insert(fa, 2);
    insert(fa, 1);
    insert(fa, 3);
    imprimeFila(fa);
    removeElemento(fa);
    imprimeFila(fa);
}

void insert(FilaAscendente* fa, int d){
    Elemento *ea=alocaElemento(d);
    Elemento *pivo=fa->tail;
    ea->dado=d;
    if(fa->size==0){
        fa->head=ea;
        fa->tail=ea;
    } else {
        ea->next=pivo->next;
        ea->prev=pivo;
        if(pivo->next==NULL){
            fa->tail=ea;
        } else {
            pivo->next->prev=ea;
        }
        pivo->next=ea;
    }
    fa->rear++;
    fa->size+=(fa->rear - fa->front + 1);
}

void removeElemento(FilaAscendente* fa){
    Elemento *e=fa->head;
    int auxmin=acharMinimo(fa);
    int **pp;
    if(fa->size>0){
        while(e!=NULL){
            if(e->dado==auxmin){
                pp=&e;
            }
            e=e->next;
        }
        free(*pp);
        fa->front++;
        fa->size+=(fa->rear - fa->front + 1);
        printf("Menor da lista removido\n");
    } else {
        printf("Erro: lista vazia\n");
    }
}

int acharMaximo(FilaAscendente* fa){
    Elemento *e=fa->head;
    int max=0;
    while(e!=NULL){
        if(max<=e->dado){
            max=e->dado;
        }
        e=e->next;
    }
    return max;
}

int acharMinimo(FilaAscendente* fa){
    Elemento *e=fa->head;
    int max=acharMaximo(fa);
    int min=max+1;
    while(e!=NULL){
        if(e->dado<=min){
            min=e->dado;
        }
        e=e->next;
    }
    return min;
}

FilaAscendente *alocaFila(){
    FilaAscendente *fa;
    fa=(FilaAscendente*)malloc(sizeof(FilaAscendente));
    fa->head=NULL;
    fa->tail=NULL;
    fa->front=0;
    fa->rear=-1;
    fa->size=0;
    return fa;
}

Elemento *alocaElemento(int d){
    Elemento *e;
    e=(Elemento*)malloc(d*sizeof(Elemento));
    e->next=NULL;
    e->prev=NULL;
    e->dado=d;
    return e;
}

void imprimeFila(FilaAscendente* fa){
    Elemento *ea=fa->head; //elemento auxiliar
    printf("NULL\t");
    while(ea!=NULL){
        printf("%d\t", ea->dado);
        ea=ea->next;
    }
    printf("NULL\n");
}

int empty(FilaAscendente* fa){
    if(fa->rear<fa->front){
        printf("Sim a lista esta vazia\n");
        return 1;
    } else {
        printf("Nao a lista nao esta vazia\n");
        return 0;
    }
}