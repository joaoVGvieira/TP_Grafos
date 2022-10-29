#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main(){
    FILE *fp;
    int quant_vertice,debug=0;
    int a1,a2;
    float peso, menor_excentricidade;
    int ordem,tamanho;
    fp = fopen("arquivo_teste.txt","r");
    fscanf(fp,"%d\n",&quant_vertice);
    GRAFO *grafo = criaGrafo(quant_vertice);
    
    while (!feof(fp)){
      fscanf (fp,"%d %d %f\n", &a1,&a2,&peso);
      criaAresta(grafo,a1,a2,peso);
    }  
     
    imprime(grafo);
   
    ordem = ordem_grafo(grafo);
    tamanho = tamanho_grafo(grafo);
    vizinho_vertice(grafo,4);
    grau_vertice(grafo,4);
    sequencia_graus(grafo);
    Caminho(grafo, 2);   
    
   /*printf("\n\nRaio do grafo = %.2f", raio_grafo(grafo));
   printf("\n\nDiametro do grafo = %.2f", diametro_grafo(grafo));

    centro_grafo(grafo);

    for(int i = 0; i < ordem; i++){
      printf("\nCentralidade de proximidade do vertice %d = %.2f", i+1, centralidadeProximidade(grafo, i));
    }
    printf("\n");


    //void menorCaminho_Grafo(grafo, 0, int *ant, float *dist){

    preparaBuscaProfundidade(grafo, 2);*/


}




