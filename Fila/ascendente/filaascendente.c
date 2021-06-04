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
} FilaAscendente;

void insert(FilaAscendente*, int);
int removeElemento(FilaAscendente*);
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
    fa->size++;
}

int removeElemento(FilaAscendente* fa){
    int min;
    Elemento  *salvafila_aux, *salvafila, *aux_e, *guardar_aux_e;
    if(fa->size!=0){ 
        aux_e=guardar_aux_e=fa->head;
        salvafila_aux=salvafila=NULL;
        min=fa->head->dado;

        while(aux_e!=NULL){
            if(min>aux_e->dado){
                min=aux_e->dado;
                salvafila=salvafila_aux;
                guardar_aux_e=aux_e;
            }
            salvafila_aux=aux_e;
            aux_e=aux_e->next;
        }

        if(guardar_aux_e==fa->head){ 
            fa->head=fa->head->next;
            if(fa->head==NULL){ 
                fa->tail=NULL;
            }
        } else if(guardar_aux_e==fa->tail){ 
            fa->tail=salvafila; 
            fa->tail->next=NULL; 
        }
        else { 
            salvafila->next=guardar_aux_e->next; 
        }

        free(guardar_aux_e);
        return min; 
    } else {
        printf("Erro: lista vazia\n");
        return -1;
    }
}

FilaAscendente *alocaFila(){
    FilaAscendente *fa;
    fa=(FilaAscendente*)malloc(sizeof(FilaAscendente));
    fa->head=NULL;
    fa->tail=NULL;
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
    if(fa->size==0){
        printf("Sim a lista esta vazia\n");
        return 1;
    } else {
        printf("Nao a lista nao esta vazia\n");
        return 0;
    }
}