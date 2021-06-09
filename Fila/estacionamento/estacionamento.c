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

typedef struct sFilaEspera{
    struct sElemento *head;
    struct sElemento *tail;
    int size;
} FilaEspera;

Fila *alocaFila();
Elemento *alocaElemento(int);
void insert(Fila*, int);
void insertHead(Fila*, int);
void insertEspera(FilaEspera*, int);
int retiraEstacionamento(Fila*, FilaEspera*, int);
Elemento *pesquisarElemento(Fila*, int);
int removeFila(Fila*);
int removeElemento(Elemento*, Fila*);
void imprimeFila(Fila*);
int empty(Fila*);
void freeFila(Fila*);

int main(){
    Fila *f;
    f=alocaFila();
    FilaEspera *fe;
    fe=alocaFila();
    insert(f, 1);
    insert(f, 2);
    insert(f, 3);
    insert(f, 4);
    insert(f, 5);
    imprimeFila(f);
    retiraEstacionamento(f, fe, 4);
    imprimeFila(f);
    insert(f, 6);
    insert(f, 7);
    insert(f, 8);
    insert(f, 9);
    insert(f, 10);
    insert(f, 11);
    imprimeFila(f);
    insert(f, 12);
    insertEspera(fe, 12);
    imprimeFila(fe);
    retiraEstacionamento(f, fe, 5);
    imprimeFila(fe);
    imprimeFila(f);
    insertEspera(fe, 13);
    imprimeFila(fe);
    retiraEstacionamento(f, fe, 6);
    imprimeFila(fe);
    imprimeFila(f);
    freeFila(fe);
    freeFila(f);
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
        printf("Insira seu carro na lista de espera - estacionamento lotado\n");
    }
}


void insertHead(Fila* f, int d){
    Elemento *ea=alocaElemento(d);
    Elemento *pivo=f->head;
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

void insertEspera(FilaEspera* fe, int d){
    Elemento *ea=alocaElemento(d);
    Elemento *pivo=fe->tail;
    ea->dado=d;
    if(fe->size==0){
        fe->head=ea;
        fe->tail=ea;
    } else {
        ea->next=pivo->next;
        ea->prev=pivo;
        if(pivo->next==NULL){ 
            fe->tail=ea;
        } else {
            pivo->next->prev=ea;
        }
        pivo->next=ea;
    }
    fe->size++;
}

int retiraEstacionamento(Fila* f, FilaEspera* fe, int encontrado){
    Elemento *prim_original, *aux, *prim_atual;
    int atual, a_encontrar=0;
    int aux_size=f->size;

    prim_original=f->tail;
    aux=pesquisarElemento(f, encontrado);
    
    if(f->size!=0){ 
        if(aux!=NULL){
            a_encontrar=aux->dado;
            do{
                atual = removeFila(f);
                if(atual!=a_encontrar){
                    insertHead(f, atual);
                }
                prim_atual=f->tail;
            } while (prim_atual != prim_original);
        } else {
            printf("Carro nao encontrado no estacionamento\n");
        }
        if(aux_size==10 && fe->size>0){
            insert(f, fe->tail->dado);
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



