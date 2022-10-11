
#include "grafo.h"

//funçao para criar um GRAFO
GRAFO *criaGrafo (int v) {
	int i;
	
	GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO)); //aloca espaço para estrtura grafo
	g->vertices = v; //atualizo o numero de vertice
	g->arestas = 0;  //atualizo o numero de vertice
	g->adj = (VERTICE *)malloc(v*sizeof(VERTICE)); //ler abaixo
	//Dentro da estrturua tem se o arranjo para o ponteiro de vertice, nao o arranjo em si 	
	// entao aloco o arranjo com (v) o numero de vertice desejado
	for (i=0; i<v; i++){ 
		g->adj[i].cabeca=NULL; //coloco NULL em todas arestas
	}
	return(g);
}

//funçao para adicionar arestas no GRAFO

ADJACENCIA *criaListaadj(int v, float peso){ 
	ADJACENCIA *temp = (ADJACENCIA *) malloc (sizeof(ADJACENCIA)); //aloca espaço para um no
	temp->vertice =v; //vertice alvo da adjacencia
	temp->peso = peso; //peso da aresta
	temp->prox = NULL; 
	return(temp); //retorno endereço da adjacencia
}

void criaAresta(GRAFO *gr, int vi, int vf, float p) { //vai de vi a vf
	if(!gr) return;  //ver se o grafo existe
	if((vf<0)||(vf >= gr->vertices))return; //validade pra ver  se os valores nao sao negativos
	if((vi<0)||(vf >= gr->vertices))return; //ou maiores que o numero de vertices do grafo
	
	ADJACENCIA *novo = criaListaadj(vf,p); //crio adjacencia com o vertice final e o peso
	//coloco a adjacencia na lista do vertice inicial
	novo->prox = gr->adj[vi].cabeca; //o campo prox da adjacencia vai receber a cabeça da lista
	gr->adj[vi].cabeca=novo; // e a cabeça da lista passa a ser o novo elemento
	gr->arestas++; // atualiza o numero de aresta no grafo
	return;
}

void imprime(GRAFO *gr){
    printf("\n==== Info do Grafo ===\n");
	printf("Vertices: %d. Arestas: %d. \n",gr->vertices,gr->arestas); //imprime numero de vertices e arestas
	int i;
	for(i=0; i< gr->vertices; i++){
		printf("%d: ",i); //imprimir em qual aresta esta
		ADJACENCIA *ad = gr->adj[i].cabeca; //chamo a cebeça da lista de adjacencia desta aresta
			while(ad){ //enquanto as adjacencias nao forem nula
				printf("%d(%.2f) ",ad->vertice,ad->peso); //imprimir a adjacencia e o peso
				ad=ad->prox; //vai para a proxima adjacencia
			}
			
		printf("\n");	
	}
}