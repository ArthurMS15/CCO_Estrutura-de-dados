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
    int max ;
    Elemento  *follow, *follow1, *p, *p1 ;
    if(fa->size!=0){ 
        p=p1=fa->head;
        follow=follow1=NULL ;
        max=fa->head->dado ;
        while(p!=NULL){
                if(max<p->dado){
                        max=p->dado;
                        follow1=follow;
                        p1=p;
                    }
                follow=p;
                p=p->next;
            }
        /* Deleting the node with min value */
        if(p1==fa->head) /* deleting first node.*/
            {
                fa->head=fa->head->next ;
                if(fa->head==NULL) /* Deleting the only one node */
                    fa->tail=NULL ;
            }
        else if(p1==fa->tail) /* Deleting last node */
            {
                fa->tail=follow1 ;
                fa->tail->next=NULL ;
            }
        else 			/* deleting any other node.*/
            follow1->next=p1->next ;
        free(p1) ;
        return max ; /* DONT FORGET LAST 2 STATEMENTS.*/
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