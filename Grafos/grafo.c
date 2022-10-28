
#include "grafo.h"
#include <math.h>
#include <float.h>

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
	temp->vertice = v; //vertice alvo da adjacencia
	temp->peso = peso; //peso da aresta
	temp->prox = NULL; 
	return(temp); //retorno endereço da adjacencia
}

void criaAresta(GRAFO *grafo, int verticeInicial, int verticeFinal, float p) { //vai de verticeInicial a verticeFinal
	if(!grafo) return;  //ver se o grafo existe
	if((verticeFinal<0)||(verticeFinal >= grafo->vertices))return; //validade pra ver se os valores nao sao negativos
	if((verticeInicial<0)||(verticeInicial >= grafo->vertices))return; //ou maiores que o numero de vertices do grafo
	
	ADJACENCIA *novo = criaListaadj(verticeFinal,p); //crio adjacencia com o vertice final e o peso
	//coloco a adjacencia na lista do vertice inicial
	novo->prox = grafo->adj[verticeInicial].cabeca; //o campo prox da adjacencia vai apontar para quem a cabeça da lista apontava
	grafo->adj[verticeInicial].cabeca=novo; // e a cabeça da lista passa a apontar para o novo elemento

	novo = criaListaadj(verticeInicial,p); //crio adjacencia com o vertice final e o peso
	//coloco a adjacencia na lista do vertice inicial
	novo->prox = grafo->adj[verticeFinal].cabeca; //o campo prox da adjacencia vai receber a cabeça da lista
	grafo->adj[verticeFinal].cabeca=novo; // e a cabeça da lista passa a ser o novo elemento
	grafo->arestas++; // atualiza o numero de aresta no grafo


	return;
}

void imprime(GRAFO *grafo){
    printf("\n==== Info do Grafo ===\n");
	printf("Vertices: %d. Arestas: %d. \n",grafo->vertices,grafo->arestas); //imprime numero de vertices e arestas
	int i;
	for(i=0; i< grafo->vertices; i++){
		printf("%d: ",i+1); //imprimir em qual aresta esta
		ADJACENCIA *ad = grafo->adj[i].cabeca; //chamo a cebeça da lista de adjacencia desta aresta
			while(ad){ //enquanto as adjacencias nao forem nula
				printf("%d(%.2f) ",ad->vertice+1,ad->peso); //imprimir a adjacencia e o peso
				ad=ad->prox; //vai para a proxima adjacencia
			}
			
		printf("\n");	
	}
}

int ordem_grafo(GRAFO *grafo){
	printf("\nOrdem do grafo: %d",grafo->vertices);
	return grafo->vertices;
}

int tamanho_grafo(GRAFO *grafo){
	printf("\nTamanho do grafo: %d\n", grafo->arestas);
	return grafo->arestas;
}

void vizinho_vertice(GRAFO *grafo, int num){
	int i;
	for(i=0; i< grafo->vertices; i++){
		if (i == num)
		{
			printf("Vizinhos de %d: ",i+1);
			ADJACENCIA *ad = grafo->adj[i].cabeca; //chamo a cebeça da lista de adjacencia desta aresta
			while(ad){ //enquanto as adjacencias nao forem nula
				printf("%d ",ad->vertice+1); //imprimir a adjacencia e o peso
				ad=ad->prox; //vai para a proxima adjacencia
			}
			printf("\n");
		}
	}
}

void grau_vertice(GRAFO *grafo, int num){
	int i;
	int cont=0;
	for(i=0; i< grafo->vertices; i++){
		if (i == num)
		{
			printf("Grau do vertice %d: ",i+1);
			ADJACENCIA *ad = grafo->adj[i].cabeca; //chamo a cebeça da lista de adjacencia desta aresta
			while(ad){ //enquanto as adjacencias nao forem nula
				cont++;
				ad=ad->prox; //vai para a proxima adjacencia
			}
			printf("%d",cont);
			printf("\n");
		}
	}
}

void sequencia_graus(GRAFO *grafo){
	int i;
	int cont=0;
	int vet[grafo->vertices];

	for(i=0; i< grafo->vertices; i++){
			ADJACENCIA *ad = grafo->adj[i].cabeca; //chamo a cebeça da lista de adjacencia desta aresta
			while(ad){ //enquanto as adjacencias nao forem nula
				cont++;
				ad=ad->prox; //vai para a proxima adjacencia
			}
			vet[i] = cont;
			cont=0;
	}
	 for (i = 0; i < grafo->vertices - 1; ++i) {
        for (int j = i + 1; j < grafo->vertices; ++j) {
            if (vet[i] > vet[j]) {
                int temp = vet[i];
                vet[i] = vet[j];
                vet[j] = temp;
            }
        }
    }
	printf("Sequencia de Graus:");
	for (i = 0; i < grafo->vertices; i++)
	{
		printf(" %d",vet[i]);
	}
	printf("\n");
}

void exetricidade_do_grafo(GRAFO *grafo, int vet1){
	
}

float BellmanFord(GRAFO *grafo, int vertice){

	float float_max = FLT_MAX;

	int verticesCount = grafo->vertices;
	int edgesCount = grafo->arestas;
	float* distance = (float*)malloc(sizeof(float) * verticesCount);
	int* verticePercorrido = (int*)malloc(sizeof(int) * verticesCount);

	for (int i = 0; i < verticesCount; i++){
		distance[i] = float_max;
		// verticePercorrido[i] = 0;
	}

	distance[vertice] = 0;


	for(int i = 1; i <= verticesCount; i ++){
		for(int j = 0; j < verticesCount; j++){
			ADJACENCIA* prox = (*grafo).adj[j].cabeca;
			while(prox != NULL){

				int u = j;
				int v = prox->vertice;
				float weight = prox->peso;

				if (distance[u] != float_max && distance[u] + weight < distance[v])
					distance[v] = distance[u] + weight;
					// verticePercorrido[u] = v;

				

				prox = prox->prox;
			}
		}
	}

	float maior_distancia = distance[0];
	
	for (int i = 1; i < grafo->vertices; i++){
		if(distance[i] > maior_distancia){
			maior_distancia = distance[i];	
		}
	}
	// for (int i = 0; i < verticesCount; i++){
	// 	printf("\nVertice %d passou por %d", i ,verticePercorrido[i]);
	// }
	
	return maior_distancia;
}

float raio_grafo(GRAFO *grafo){
	float raio;
	int vertice;

	for(int i = 0; i < grafo->vertices; i++){
		if(i == 0){
			raio = BellmanFord(grafo, i);
			vertice = 0;
		}
		if(BellmanFord(grafo, i) < raio){
			raio = BellmanFord(grafo, i);
			vertice = i;
		}
	}

	return raio;
}

float diametro_grafo(GRAFO *grafo){
	float diametro;
	int vertice;

	for(int i = 0; i < grafo->vertices; i++){
		if(i == 0){
			diametro = BellmanFord(grafo, i);
			vertice = 0;
		}
		if(BellmanFord(grafo, i) > diametro){
			diametro = BellmanFord(grafo, i);
			vertice = i;
		}
	}

	return diametro;
}

void centro_grafo(GRAFO *grafo){
	printf("\nVertices que fazer parte do centro: ");
    for(int i = 0; i < grafo->vertices; i++){
      	if(BellmanFord(grafo, i) == raio_grafo(grafo)){
        	printf("%d ", i+1);
      	}
    }
	return;
}

float centralidadeProximidade(GRAFO *grafo, int vertice){

	float float_max = FLT_MAX;

	int verticesCount = grafo->vertices;
	int edgesCount = grafo->arestas;
	float* distance = (float*)malloc(sizeof(float) * verticesCount);
	int* verticePercorrido = (int*)malloc(sizeof(int) * verticesCount);

	for (int i = 0; i < verticesCount; i++){
		distance[i] = float_max;
		// verticePercorrido[i] = 0;
	}

	distance[vertice] = 0;


	for(int i = 1; i <= verticesCount; i ++){
		for(int j = 0; j < verticesCount; j++){
			ADJACENCIA* prox = (*grafo).adj[j].cabeca;
			while(prox != NULL){

				int u = j;
				int v = prox->vertice;
				float weight = prox->peso;

				if (distance[u] != float_max && distance[u] + weight < distance[v])
					distance[v] = distance[u] + weight;
					// verticePercorrido[u] = v;

				

				prox = prox->prox;
			}
		}
	}

	float soma = 0;
	
	for (int i = 0; i < grafo->vertices; i++){
		soma += distance[i];
	}
	
	return (verticesCount-1)/soma;
}