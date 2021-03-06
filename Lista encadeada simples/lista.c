#include <stdio.h>
#include <stdlib.h>

typedef struct sElemento{
    struct sElemento *next;
    int dado;
} Elemento;

typedef struct sLista{
    struct sElemento *head;
    struct sElemento *tail;
    int size;
} Lista;


Lista* alocaLista();
Elemento* alocaElemento(int);
void insereElemento(Lista*, int, Elemento*);
int removeElemento(Lista*, Elemento*);
void imprimeLista(Lista*);
Elemento* pesquisarElemento(Lista*, int);
void freeLista(Lista*);

int main (){
    Lista *l;
    l=alocaLista();
    removeElemento(l, l->tail); 
    insereElemento(l, 1, l->tail);

    imprimeLista(l);

    insereElemento(l, 2, l->head);

    imprimeLista(l);

    insereElemento(l, 3, l->head->next); 

    imprimeLista(l);

    removeElemento(l, l->tail); 
    insereElemento(l, 4, NULL);

    imprimeLista(l);

    insereElemento(l, 5, NULL);

    imprimeLista(l);

    removeElemento(l, l->tail); 
    removeElemento(l, l->head);

    imprimeLista(l);

    removeElemento(l, NULL);
    
    imprimeLista(l);

    freeLista(l);
}

Elemento *alocaElemento(int d){
    Elemento *e;
    e=(Elemento*)malloc(d*sizeof(Elemento));
    e->next=NULL;
    e->dado=d;
    return e;
}

Lista *alocaLista(){
    Lista *l;
    l=(Lista*)malloc(sizeof(Lista));
    l->head=NULL;
    l->tail=NULL;
    l->size=0;
    return l;
}

void insereElemento(Lista* l, int dado, Elemento* pivo){
    Elemento *e=alocaElemento(dado);
    e->dado=dado;
    if(pivo==NULL){
        if (l->size==0){//lista->head==lista->tail==NULL
            l->tail=e;
        } 
        e->next=l->head;
        l->head=e;
    } else {
        if(pivo->next==NULL){
            l->tail=e;
        }
        e->next=pivo->next;
        pivo->next=e;
    }
    l->size++;
}

int removeElemento(Lista* l, Elemento* pivo){
    Elemento *ea; //ELEMENTO ANTIGO 
    int dado;
    if(l->size==0){
        printf("Erro: lista vazia\n");
        return -1;
    }
    if(pivo==NULL){
        ea=l->head;
        l->head=l->head->next;
        if(l->head==NULL){
            l->tail=NULL;
        }
    } else {
        if(pivo->next==NULL){
            printf("Erro: fim da lista\n");
            return -2;
        }
        ea=pivo->next;
        pivo->next=pivo->next->next;
        if(pivo->next==NULL){
            l->tail=pivo;
        }
    }
    dado=ea->dado;
    free(ea);
    l->size--;
    return dado;
}

void imprimeLista(Lista* l){
    Elemento *ea=l->head; //elemento auxiliar
    while(ea!=NULL){
        printf("%d\t", ea->dado);
        ea=ea->next;
    }
    printf("NULL\n");
}

Elemento *pesquisarElemento(Lista* l, int dado){
    Elemento* aux=l->head;
    while(aux!=NULL){
        if(aux->dado==dado){
            return aux;
        }
        aux=aux->next;
    }
    return NULL;
}

void freeLista(Lista* l){
    while(l->size!=0){
        removeElemento(l, NULL);
    }
    free(l);
}