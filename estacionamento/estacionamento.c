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

Fila *alocaFila();
Elemento *alocaElemento(int);
void insert(Fila*, int, Elemento*);
int retiraEstacionamento(Fila*, Fila*, int);
int retiraEstacionamentoEspera(Fila* f, int);
Elemento *pesquisarElemento(Fila*, int);
int removeFila(Fila*);
int removeElemento(Elemento*, Fila*);
void imprimeFila(Fila*);
int empty(Fila*);
void freeFila(Fila*);

int main(){
    Fila *f;
    f=alocaFila();
    Fila *fe;
    fe=alocaFila();
    insert(f, 1, f->tail);
    insert(f, 2, f->tail);
    insert(f, 3, f->tail);
    insert(f, 4, f->tail);
    insert(f, 5, f->tail);
    imprimeFila(f);
    retiraEstacionamento(f, fe, 4);
    imprimeFila(f);
    insert(f, 6, f->tail);
    insert(f, 7, f->tail);
    insert(f, 8, f->tail);
    insert(f, 9, f->tail);
    insert(f, 10, f->tail);
    insert(f, 11, f->tail);
    imprimeFila(f);
    insert(f, 12, f->tail);
    insert(fe, 12, f->tail);
    imprimeFila(fe);
    retiraEstacionamento(f, fe, 5);
    imprimeFila(fe);
    imprimeFila(f);
    freeFila(f);
    freeFila(fe);
}

Fila *alocaFila(){
    Fila *f;
    f=(Fila*)malloc(sizeof(Fila));
    f->head=NULL;
    f->tail=NULL;
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

void insert(Fila* f, int d, Elemento* pivo){
    Elemento *ea=alocaElemento(d);
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
        printf("Insira seu carro na lista de espera - estacionamento lotado\n");
    }
}

int retiraEstacionamento(Fila* f, Fila* fe, int encontrado){
    Elemento *prim_original, *aux, *prim_atual;
    int atual, a_encontrar=0;

    prim_original=f->tail;
    aux=pesquisarElemento(f, encontrado);
    
    if(f->size!=0){ 
        if(aux!=NULL){
            a_encontrar=aux->dado;
            do{
                atual = removeFila(f);
                if(atual!=a_encontrar){
                    insert(f, atual, f->head);
                }
                prim_atual=f->tail;
            } while (prim_atual != prim_original);
        } else {
            printf("Carro nao encontrado no estacionamento\n");
        }
    } else {
        printf("Erro: estacionamento vazio\n");
        return -1;
    }
    while(fe->head != NULL && f->size<10){
        insert(f, fe->head->dado, f->tail);
        retiraEstacionamentoEspera(fe, f->head->dado);
    }
}

int retiraEstacionamentoEspera(Fila* f, int encontrado){
    Elemento *prim_original, *aux, *prim_atual;
    int atual, a_encontrar=0;

    prim_original=f->tail;
    aux=pesquisarElemento(f, encontrado);
    
    if(f->size!=0){ 
        if(aux!=NULL){
            a_encontrar=aux->dado;
            do{
                atual = removeFila(f);
                if(atual!=a_encontrar){
                    insert(f, atual, f->head);
                }
                prim_atual=f->tail;
            } while (prim_atual != prim_original);
        } else {
            printf("Carro nao encontrado no estacionamento\n");
        }
    } else {
        printf("Erro: estacionamento vazio\n");
        return -1;
    }
}

Elemento *pesquisarElemento(Fila* f, int dado){
    Elemento* aux=f->head;
    while(aux!=NULL){
        if(aux->dado==dado){
            return aux;
        }
        aux=aux->next; 
    }
    return NULL;
}

int removeFila(Fila* f){
    return removeElemento(f->tail, f);
}

int removeElemento(Elemento* e, Fila* f){
    int dado;
    if((e!=NULL) && (f->size>0)){
        if(e==f->head){
            f->head=e->next;
            if(f->head==NULL){
                f->tail=NULL;
            } else {
                e->next->prev=NULL;
            }
        } else {
            e->prev->next=e->next;
            if(e->next==NULL){
                f->tail=e->prev;
            } else {
                e->next->prev=e->prev;
            }
        }
        dado=e->dado;
        free(e);
        f->size--;
        return dado;
    }
    printf("Erro: elemento NULL ou lista vazia\n");
    return -1;
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
    Elemento* next = aux->next;
    while(aux != NULL){
        free(aux);
        aux = next;
        if(aux!= NULL){
            next = next->next;
        }
    }
    free(next);
    free(f);
}



