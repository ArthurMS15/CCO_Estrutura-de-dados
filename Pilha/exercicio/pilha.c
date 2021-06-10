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
    char aux[255];
    /*for (int i=0; i<strlen(str); i++){
        if (str[i] == ')' || str[i]  == ']' || str[i]  == '}' || str[i] == '(' || str[i]  == '[' || str[i]  == '{' ){ 
            aux[i]=str[i];
        }
    }*/
    /*for (int i=0; i<strlen(str); i++){
        printf("%c\n", aux[i]);
    }*/
    for (int i=0; i<strlen(str); i++){
          
            if (str[0] == ')' || str[0]  == ']' || str[0]  == '}' ){
                printf("Erro: nao se pode comecar com ), ] ou }\n");
                return -1;
            } else{
                if (str[i] == '(' || str[i]  == '[' || str[i]  == '{' ){ 
                    push(p, str[i]);
                }
                if (str[i] == '('){
                    for (int i=0; i<strlen(str); i++){
                        if(str[i] == ')' || str[i]  == ']' || str[i]  == '}'){
                            if(str[i] == ')'){
                                pop(p);
                            } else {
                                printf("Erro: Adicionou parenteses mas nao fechou com ele ou nao fechou\n");
                                validar(p);
                                return -2;
                            }
                        }
                    }
                }

                if (str[i] == '['){
                    for (int i=0; i<strlen(str); i++){
                        if(str[i] == ')' || str[i]  == ']' || str[i]  == '}'){
                            if(str[i] == ')'){
                                printf("teste\n");
                                //ok fechou o parenteses
                                for (int i=0; i<strlen(str); i++){
                                    if(str[i] == ')' || str[i]  == ']' || str[i]  == '}'){
                                        if(str[i] == ']'){
                                            pop(p);
                                        } else{
                                            printf("Erro: Adicionou colchetes mas nao fechou com ele ou nao fechou\n");
                                            validar(p);
                                            return -2;
                                        }
                                    }
                                }
                            } else {
                                printf("Erro: Nao adicionou parenteses ou adicionou mas nao o fechou\n");
                                validar(p);
                                return -2;
                            }
                        }
                    }
                }


            }
        
    }
    validar(p);
}

void validar(Pilha* p){
    if(empty(p)==1){
        printf("Equacao valida\n");
    } else {
        printf("Equacao invalida\n");
    }
    return 0;
}

/*int verify(char* str, Elemento* t){ 
    char aux;
    for (int i=0; i<strlen(str); i++){ 
        if (str[i] == '(' || str[i]  == '[' || str[i]  == '{' ){ 
            push(t, str[i]);
            t->size++;
            printf("%c\n", t->dado);
        }
        if (str[i] == ')' || str[i] == ']' || str[i] == '}' ){
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
}*/

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

 