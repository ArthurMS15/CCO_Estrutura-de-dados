#include <stdio.h>
#include <stdlib.h>
#define N 10
#define M 10

int main(){
    int mat[N][M];
    int sl[N];
    float mc[M];
    int soma=0, cont=0, cont2=0;
    float media=0;

    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            mat[i][j]=rand()%10;
            mc[j]=0;
        }
        sl[i]=0;
    }

    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(mat[i][j]%2==1){
                soma+=mat[i][j];
            }
        }
        sl[i]=soma;
        soma=0;
    }
    
    for(int j=0;j<M;j++){
        for(int i=0;i<N;i++){
            if(mat[i][j]%2==0){
                media+=mat[i][j];
                cont++;
            }
        }
        media=media/cont;
        mc[j]=media;
        media=0;
        cont=0;
    }

    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(i==j){
                cont+=mat[i][j];
            }
        }
    }

    int j=M-1;
    int i=0;
    while(i<N){
        cont2+=mat[i][j];
        i++;
        j--;
    }


    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            printf("%d\t",mat[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");
    printf("Vetor com as somas dos valores impares das linhas:\n");
    for(int i=0; i<N; i++){
        printf("%d\t", sl[i]);
    }

    printf("\n\n");
    printf("Vetor com a media dos valores pares das colunas:\n");
    for(int j=0; j<M; j++){
        printf("%.2f\t", mc[j]);
    }

    printf("\n\n");
    printf("A diferenca entre a diagonal principal e a secundaria eh de:\n");
    cont=cont-cont2;
    printf("%d", cont);

    
}