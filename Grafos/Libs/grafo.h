#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct adjacencia {
    int vertice; // vertice de destino 
    float peso; // peso associado a aresta que leva ao vertice de destino
    int visited;
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

int ordem_grafo(GRAFO *grafo);

int tamanho_grafo(GRAFO *grafo);

void vizinho_vertice(GRAFO *grafo, int num);

void grau_vertice(GRAFO *grafo, int num);

void sequencia_graus(GRAFO *grafo);

float execetridade_grafo(GRAFO *grafo, int vertice);

float raio_grafo(GRAFO *grafo);

float diametro_grafo(GRAFO *grafo);

void centro_grafo(GRAFO *grafo);

float centralidadeProximidade(GRAFO *grafo, int vertice);

void Caminho(GRAFO *grafo, int vertice);

void buscaProfundidade(GRAFO*grafo, int ini, int *visitado, int cont);

void preparaBuscaProfundidade(GRAFO *grafo, int ini);

float procuraMenorDistancia(GRAFO *grafo, int vertice);

void relaxa(GRAFO *grafo, float *distancia, int *antecessor, int verticeOrigem, int verticeDestino);

int existeAberto(GRAFO *grafo, int *aberto);

int MenorDistancia(GRAFO *grafo, int *aberto, float *distancia);

void Dijkstra(GRAFO *grafo, int verticeOrigem);