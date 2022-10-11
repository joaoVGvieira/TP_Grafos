#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main(){
  FILE *fp;
  int quant_vertice;
  int a1,a2;
  float peso;
  fp = fopen("arquivo_teste.txt","r");
  fscanf(fp,"%d\n",&quant_vertice);
  GRAFO *gr = criaGrafo(quant_vertice);
  while (!feof(fp))
  {
    fscanf (fp,"%d %d %f\n", &a1,&a2,&peso);
    criaAresta(gr,a1,a2,peso);
  }   
  imprime(gr);
}