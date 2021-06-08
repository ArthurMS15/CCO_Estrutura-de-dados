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
} FilaDescendente;

void insert(FilaDescendente*, int);
int removeElemento(FilaDescendente*);
FilaDescendente *alocaFila();
Elemento *alocaElemento(int);
void imprimeFila(FilaDescendente*);
int empty(FilaDescendente*);
Elemento *pesquisarElementoNext(FilaDescendente*, int);
void freeFila(FilaDescendente*);

int main(){
    FilaDescendente *fd;
    fd=alocaFila();
    insert(fd, 2);
    insert(fd, 1);
    insert(fd, 3);
    imprimeFila(fd);
    removeElemento(fd);
    imprimeFila(fd);
    empty(fd);
    pesquisarElementoNext(fd, 3);
    freeFila(fd);
}

void insert(FilaDescendente* fd, int d){
    Elemento *ea=alocaElemento(d);
    Elemento *pivo=fd->tail;
    ea->dado=d;
    if(fd->size==0){
        fd->head=ea;
        fd->tail=ea;
    } else {
        ea->next=pivo->next;
        ea->prev=pivo;
        if(pivo->next==NULL){ 
            fd->tail=ea;
        } else {
            pivo->next->prev=ea;
        }
        pivo->next=ea;
    }
    fd->size++;
}

int removeElemento(FilaDescendente* fd){
    int max;
    Elemento  *salvafila_aux, *salvafila, *aux_e, *guardar_aux_e;

    if(fd->size!=0){ 
        aux_e=guardar_aux_e=fd->head;
        salvafila_aux=salvafila=NULL;
        max=fd->head->dado;

        while(aux_e!=NULL){
            if(max<aux_e->dado){
                max=aux_e->dado;
                salvafila=salvafila_aux;
                guardar_aux_e=aux_e;
            }
            salvafila_aux=aux_e;
            aux_e=aux_e->next;
        }
        //aux_e servindo apenas para continuar a lista no while, verificando os dados;
        //guardar_aux_e assim como o nome representa vai servir para guardar o elemento auxiliar quando for encontrado um dado maximo;
        //o salvafila_aux, vai passar a guardar o aux_e também caso o elemento na fila não seja o maior, sendo assim o salvafila quando encontrado vai passar a guardar também o salvafila_aux.

        if(guardar_aux_e==fd->head){ // caso o elemento seja o primeiro da fila
            fd->head=fd->head->next;
            if(fd->head==NULL){ 
                fd->tail=NULL;
            }
        } else if(guardar_aux_e==fd->tail){ //caso o elemento seja o ultimo da fila
            fd->tail=salvafila; //tail será igual ao valor que o salvafila guardou do salvafila_aux quando foi encontrado o dado de valor maximo
            fd->tail->next=NULL; //garantindo que posteior ao tail tenha um null, caso o salvafila tenha sido algum elemento do meio da fila
        }
        else { 
            salvafila->next=guardar_aux_e->next; //se o guardar_aux_e não for nem o ultimo e nem o primeiro elemento
        }
        //garantir ordem na lista

        free(guardar_aux_e);
        return max; 
    } else {
        printf("Erro: lista vazia\n");
        return -1;
    }
}

FilaDescendente *alocaFila(){
    FilaDescendente *fd;
    fd=(FilaDescendente*)malloc(sizeof(FilaDescendente));
    fd->head=NULL;
    fd->tail=NULL;
    fd->size=0;
    return fd;
}

Elemento *alocaElemento(int d){
    Elemento *e;
    e=(Elemento*)malloc(d*sizeof(Elemento));
    e->next=NULL;
    e->prev=NULL;
    e->dado=d;
    return e;
}

void imprimeFila(FilaDescendente* fd){
    Elemento *ea=fd->head; //elemento auxiliar
    printf("NULL\t");
    while(ea!=NULL){
        printf("%d\t", ea->dado);
        ea=ea->next;
    }
    printf("NULL\n");
}

int empty(FilaDescendente* fd){
    if(fd->size==0){
        printf("Sim a lista esta vazia\n");
        return 1;
    } else {
        printf("Nao a lista nao esta vazia\n");
        return 0;
    }
}

Elemento *pesquisarElementoNext(FilaDescendente* fd, int dado){
    Elemento* aux=fd->head;
    while(aux!=NULL){
        if(aux->dado==dado){
            return aux;
        }
        aux=aux->next; 
    }
    return NULL;
}

void freeFila(FilaDescendente* fd){
    Elemento* aux = fd->head;
    Elemento* next = aux->next;
    while(aux != NULL){
        free(aux);
        aux = next;
        if(aux!= NULL){
            next = next->next;
        }
    }
    free(next);
    free(fd);
}