#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main(){
    FILE *fp;
    int quant_vertice;
    int a1,a2;
    float peso;
    int ordem,tamanho;
    fp = fopen("arquivo_teste.txt","r");
    fscanf(fp,"%d\n",&quant_vertice);
    GRAFO *grafo = criaGrafo(quant_vertice);
    while (!feof(fp))
    {
      fscanf (fp,"%d %d %f\n", &a1,&a2,&peso);
      criaAresta(grafo,a1,a2,peso);
    }   
    imprime(grafo);

    ordem = ordem_grafo(grafo);
    tamanho = tamanho_grafo(grafo);
    vizinho_vertice(grafo,4);
    grau_vertice(grafo,4);
    sequencia_graus(grafo);
    
    // for(int j = 0; j < grafo->vertices; j++){
    //   ADJACENCIA* prox = (*grafo).adj[j].cabeca;
    //   do{
    //     printf("\n %f", prox->peso);
    //     prox = prox->prox;
    //   }while(prox != NULL);
    // }



    for(int i = 0; i < ordem; i++){
      printf("\nExcentricidade do vertice %d = %f", i+1, BellmanFord(grafo, i));
    }
}