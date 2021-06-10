#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sElemento{
    struct sElemento *next;
    struct sElemento *prev;
    char dado;
    int size;
} Elemento;

void push(Elemento*, char);
char pop(Elemento*);
int verify(char*, Elemento*);
int empty(Elemento*);
void imprimePilha(Elemento*);


int main(){
    char str[255];  
    Elemento cabeca; 
    Elemento *topo; 
    topo = &cabeca; 
    topo->next = NULL; 
    printf("Informe a string: "); 
    gets(str); 
    verify(str, topo);
    return 0; 
}

Elemento *alocaElemento(char d){
    Elemento *e;
    e=(Elemento*)malloc(d*sizeof(Elemento));
    e->next=NULL;
    e->prev=NULL;
    e->dado=d;
    e->size=0;
    return e;
}

void push(Elemento* t, char dado){
    Elemento *e=alocaElemento(dado);
    e->dado = dado; 
    e->next = t->next; 
    t->next = e;
}

char pop(Elemento* t){
    char c; 
    Elemento *pt; 
    pt = t->next; 
    c = pt->dado; 
    t->next = pt->next; 
    free(pt);
    return c; 
}

int verify(char* str, Elemento* t){ 
    char aux;
    for (int i=0; i<strlen(str); i++){ 
        if (str[i] == '(' || str[i]  == '[' || str[i]  == '{' ){ 
            push(t, str[i]);
            t->size++;
            printf("%c\n", t->dado);
        }
        if (str == ')' || str[i] == ']' || str[i] == '}' ){
            if(empty(t)==1){
                return -1;
            } else {
                aux = pop(t);
                t->size--; 
                if(aux != '(' || aux != '[' || aux != '{' ){
                    return -2;
                }
            }
        }
    }
    if(empty(t)==0){
        printf("A string nao eh valida");
        return -3;
    } else {
        printf("A string eh valida");
        return 1;
    }
} 

int empty(Elemento* t){
    if(t->size==0){
        return 1;
    } else {
        return 0;
    }
}
 