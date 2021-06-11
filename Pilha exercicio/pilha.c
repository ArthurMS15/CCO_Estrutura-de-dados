#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sElemento{
    struct sElemento *next;
    struct sElemento *prev;
    char dado;
} Elemento;

typedef struct sPilha{
    struct sElemento *head;
    struct sElemento *tail;
    int size;
} Pilha;

Pilha *alocaPilha();
Elemento *alocaElemento(char);
void imprimePilha(Pilha*);
int empty(Pilha*);
void stacktop(Pilha*);
void push(Pilha*, char);
char pop(Pilha*);
void freePilha(Pilha*);
int verificar(char*, Pilha*);


int main(){
    Pilha *p;
    p=alocaPilha();
    char str[255];  
    printf("Informe a string: "); 
    gets(str);
    verificar(str, p); 
    return 0;
}

Pilha *alocaPilha(){
    Pilha *p;
    p=(Pilha*)malloc(sizeof(Pilha));
    p->head=NULL;
    p->tail=NULL;
    p->size=0;
    return p;
}

Elemento *alocaElemento(char d){
    Elemento *e;
    e=(Elemento*)malloc(d*sizeof(Elemento));
    e->next=NULL;
    e->prev=NULL;
    e->dado=d;
    return e;
}

void push(Pilha* p, char dado){
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

char pop(Pilha* p){
    char dado;
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

int verificar(char* str, Pilha* p){
    for (int i=0; i<strlen(str); i++){
        if (str[i] == '(' || str[i]  == '[' || str[i]  == '{' ){ 
                push(p, str[i]);
        } else if (str[i] == ')' || str[i]  == ']' || str[i]  == '}' ){
            if(empty(p)==1){
                printf("Equacao invalida\n");
                return 0;
            } else {
                pop(p);
            }
        }      
    }
    if(empty(p)==1){
        printf("Equacao valida\n");
    } else {
        printf("Equacao invalida\n");
    }
}

void imprimePilha(Pilha* p){
    Elemento *ea=p->tail; //elemento auxiliar
    printf("NULL\n");
    while(ea!=NULL){
        printf("%c\n", ea->dado);
        ea=ea->prev;
    }
    printf("NULL\n");
}

int empty(Pilha* p){
    if(p->size==0){
        return 1;
    } else {
        return 0;
    }
}

void stacktop(Pilha* p){
    printf("Elemento do topo: %d\n", p->tail->dado);
}

void freePilha(Pilha* p){
    Elemento* aux = p->tail;
    while(aux != NULL){
        aux=aux->prev;
        pop(p);
    }
    free(p);
}

 