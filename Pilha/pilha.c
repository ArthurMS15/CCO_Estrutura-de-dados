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

int main(){

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
    printf("%d", p->tail->dado);
}

//lastin firstout - vertical
//push() - empilhar - inserir
//pop() - desempilhar - remover
/*push(s,i) s.items[++s.top]=i em vetor
pilha - s
i - item
pop(s) x=s.items[stop--]; em vetor
overflow e underflow

stacktop(s) - retorna uma consulta do elemento q esta no topo da pilha mas sem remover
*/