#include <stdio.h>
#include <stdlib.h>

typedef struct adjacencia {
    int vertice; // vertice de destino 
    float peso; // peso associado a aresta que leva ao vertice de destino
    struct adjacencia *prox; // O proximo elemento da lista de adjacencias
}ADJACENCIA;

typedef struct vertice {
    ADJACENCIA *cabeca; //possui apenas a cabeca da lista de adjacencia
}VERTICE;

typedef struct grafo { 
    int vertices; // numero de vertice total do grafo
    int arestas; // numero de arestas totais do grafo
    VERTICE *adj; // Arranjo de vertices da estrutura
}GRAFO;


GRAFO *criaGrafo (int v);

ADJACENCIA *criaListaadj(int v, float peso);

void criaAresta(GRAFO *gr, int vi, int vf, float p);

void imprime(GRAFO *gr);