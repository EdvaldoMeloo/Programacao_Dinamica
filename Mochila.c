#include <stdio.h>
#include <stdlib.h>

typedef struct produtos{
    int peso;
    int custo;
}Prod;

typedef struct tabela{
    int custo;
    int x;
}tabela;

int mochila(int n, int M, Prod p[n], int sol[n]);

int main(){
    int n, M;
    int i;
    int lucro;

    FILE * arq;
    arq = fopen("mochila01.txt", "r");

    if(arq == 0){
        printf("Erro ao abrir o arquivo!\n");
        return 0;
    }

    fscanf(arq, "%d", &n); /// Quantidade de Produtos
    fscanf(arq, "%d", &M); /// Capacidade da Mochila

    Prod p[n]; /// Variavel do tipo Produtos
    int sol[n];

    for(i=0; i<n; i++){
        fscanf(arq, "%d %d", &p[i].peso, &p[i].custo);
        sol[i] = 0;
    }

    fclose(arq);

    /// Mochila
    lucro = mochila(n,M,p,sol);

    /// Imprimindo a solucao
    printf("Solucao: ");
    for(i=0; i<n; i++){
        printf("%d ", sol[i]);
    }
    printf("\n");
    printf("Lucro = %d", lucro);

    printf("\n\n");
    system("PAUSE");
    return 0;
}


int mochila(int n, int M, Prod p[n], int sol[n]){
    int i, y;
    tabela G[M+1][n+1];
    int valor;
    int ind;

    /// Inicializacao
    for(y=0; y<=M; y++){
        G[y][n].custo = 0;
        G[y][n].x = 0;
    }

    for(i=n-1; i>=0; i--){
        for(y=0; y<=M; y++){
            if(p[i].peso <= y){
                valor = G[y][i+1].custo;
                ind = y-p[i].peso;

                if(valor < G[ind][i+1].custo + p[i].custo){
                    G[y][i].custo = G[ind][i+1].custo+p[i].custo;
                    G[y][i].x = 1;
                }
                else{
                    G[y][i].custo = valor;
                    G[y][i].x = 0;
                }
            }
            else{
                G[y][i].custo = 0;
                G[y][i].x = 0;
            }
        }
    }

    y = M;
    for(i=0; i<n; i++){
        if(G[y][i].x == 1){
            sol[i] = 1;
            y = y - p[i].peso;
        }
        else{
            sol[i] = 0;
        }
    }

    return G[M][0].custo;
}
