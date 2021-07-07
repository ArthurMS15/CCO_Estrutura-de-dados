#include <stdio.h>
#include <stdlib.h>
#define M 26

int main(){
    FILE *file = fopen("teste.txt", "r");

    if(file == NULL){
        printf("Não foi possivel ler os nomes\n");
        exit(0);
    }

    char nome[100];
    char aux;
    int i=1;

    while(fgets(nome, 100, file) != NULL){
        printf("%s", nome);
        int acumulador=0;
        for(int i=0; i< strlen(nome); i++){
            int aux=nome[i];
            acumulador = (31 * acumulador + nome[i]) % M;
        }
    }
    fclose(file);
    
}