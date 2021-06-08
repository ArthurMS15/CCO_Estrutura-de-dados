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
int empty(FilaAscendente*);
void freeFila(FilaAscendente*);

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
    int max;
    Elemento  *salvafila_aux, *salvafila, *aux_e, *guardar_aux_e;

    if(fa->size!=0){ 
        aux_e=guardar_aux_e=fa->head;
        salvafila_aux=salvafila=NULL;
        max=fa->head->dado;

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

        if(guardar_aux_e==fa->head){ // caso o elemento seja o primeiro da fila
            fa->head=fa->head->next;
            if(fa->head==NULL){ 
                fa->tail=NULL;
            }
        } else if(guardar_aux_e==fa->tail){ //caso o elemento seja o ultimo da fila
            fa->tail=salvafila; //tail será igual ao valor que o salvafila guardou do salvafila_aux quando foi encontrado o dado de valor maximo
            fa->tail->next=NULL; //garantindo que posteior ao tail tenha um null, caso o salvafila tenha sido algum elemento do meio da fila
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

Elemento *pesquisarElementoNext(FilaAscendente* l, int dado){
    Elemento* aux=l->head;
    while(aux!=NULL){
        if(aux->dado==dado){
            return aux;
        }
        aux=aux->next; 
    }
    return NULL;
}

void freeFila(FilaAscendente* f){
    Elemento* aux = f->head;
    while(aux != NULL){
        aux=aux->next;
        removeElemento(/*aux->prev,*/ f);
    }
    free(f);
}