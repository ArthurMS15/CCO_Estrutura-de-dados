#include <stdio.h>
#include <stdlib.h>

typedef struct sElemento{
    struct sElemento *next;
    struct sElemento *prev;
    int dado;
} Elemento;

typedef struct sPilha{
    struct sElemento *head;
    struct sElemento *tail;
    int size;
} Pilha;


Pilha *alocaPilha();
Elemento *alocaElemento(int);
void imprimePilha(Pilha*);
int empty(Pilha*);
void stacktop(Pilha*);
void push(Pilha*, int);
int pop(Pilha*);

int main(){
    Pilha *p;
    p=alocaPilha();
    push(p, 1);
    push(p, 2);
    push(p, 3);
    imprimePilha(p);
    stacktop(p);
    pop(p);
    imprimePilha(p);
    stacktop(p);
}

Pilha *alocaPilha(){
    Pilha *p;
    p=(Pilha*)malloc(sizeof(Pilha));
    p->head=NULL;
    p->tail=NULL;
    p->size=0;
    return p;
}

Elemento *alocaElemento(int d){
    Elemento *e;
    e=(Elemento*)malloc(d*sizeof(Elemento));
    e->next=NULL;
    e->prev=NULL;
    e->dado=d;
    return e;
}

void imprimePilha(Pilha* p){
    Elemento *ea=p->tail; //elemento auxiliar
    printf("NULL\n");
    while(ea!=NULL){
        printf("%d\n", ea->dado);
        ea=ea->prev;
    }
    printf("NULL\n");
}

int empty(Pilha* p){
    if(p->size==0){
        printf("Sim a pilha esta vazia\n");
        return 1;
    } else {
        printf("Nao a pilha nao esta vazia\n");
        return 0;
    }
}

void stacktop(Pilha* p){
    printf("Elemento do topo: %d\n", p->tail->dado);
}

void push(Pilha* p, int dado){
    Elemento *ea=alocaElemento(dado);
    Elemento *pivo=p->tail;
    ea->dado=dado;
    if(p->size==0){
        p->head=ea;
        p->tail=ea;
    } else {
        ea->next=pivo->next;
        ea->prev=pivo;
        if(pivo->next==NULL){
            p->tail=ea;
        } else {
            pivo->next->prev=ea;
        }
        pivo->next=ea;
    }
    p->size++;
}

int pop(Pilha* p){
    int dado;
    Elemento *e=p->tail;
    if((p!=NULL) && (p->size>0)){
        if(e==p->head){
            p->head=e->next;
            if(p->head==NULL){
                p->tail=NULL;
            } else {
                e->next->prev=NULL;
            }
        } else {
            e->prev->next=e->next;
            if(e->next==NULL){
                p->tail=e->prev;
            } else {
                e->next->prev=e->prev;
            }
        }
        dado=e->dado;
        free(e);
        p->size--;
        return dado;
    }
    printf("Erro: elemento NULL ou lista vazia\n");
    return -1;
}

//lastin firstout - vertical
/*push(s,i) s.items[++s.top]=i em vetor
pilha - s
i - item
pop(s) x=s.items[stop--]; em vetor
overflow e underflow
*/