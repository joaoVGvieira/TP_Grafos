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

ADJACENCIA* criaListaadj(int v, float peso){ 
	ADJACENCIA *temp = (ADJACENCIA *) malloc (sizeof(ADJACENCIA)); //aloca espaço para um no
	temp->vertice = v; //vertice alvo da adjacencia
	temp->peso = peso; //peso da aresta
	temp->visited = 0;
	temp->prox = NULL; 
	return(temp); //retorna endereço da adjacencia
}

void criaAresta(GRAFO *grafo, int verticeInicial, int verticeFinal, float p){ 



	if(!grafo) return;  

	if((verticeFinal<0)||(verticeFinal >= grafo->vertices))return;
	if((verticeInicial<0)||(verticeInicial >= grafo->vertices))return;
	
	ADJACENCIA *novo = criaListaadj(verticeFinal,p); 

	if(grafo->adj[verticeInicial].cabeca == NULL){ // lista vazia 
		novo->prox = grafo->adj[verticeInicial].cabeca; 
		grafo->adj[verticeInicial].cabeca=novo;

	}else if(novo->vertice < grafo->adj[verticeInicial].cabeca->vertice){ // novo é o menor item da lista

		novo->prox = grafo->adj[verticeInicial].cabeca;
		grafo->adj[verticeInicial].cabeca = novo;

	}else{ //novo esta no meio ou no final da lista

		ADJACENCIA *aux = grafo->adj[verticeInicial].cabeca;

		while(aux->prox != NULL && novo->vertice > aux->prox->vertice) aux = aux->prox;

		novo->prox = aux->prox;
		aux->prox = novo;

	} 



	novo = criaListaadj(verticeInicial,p);
	
	if(grafo->adj[verticeFinal].cabeca == NULL){  // lista vazia 
		novo->prox = grafo->adj[verticeFinal].cabeca; 
		grafo->adj[verticeFinal].cabeca=novo;

	}else if(novo->vertice < grafo->adj[verticeFinal].cabeca->vertice){  // novo é o menor item da lista
		novo->prox = grafo->adj[verticeFinal].cabeca;
		grafo->adj[verticeFinal].cabeca = novo;

	}else{  //novo esta no meio ou no final da lista

		ADJACENCIA *aux = grafo->adj[verticeFinal].cabeca;

		while(aux->prox != NULL && novo->vertice > aux->prox->vertice) aux = aux->prox;
		
		novo->prox = aux->prox;
		aux->prox = novo;

	}

	grafo->arestas++;

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
	for (int i = 0; i < grafo->vertices; i++){
		ADJACENCIA* prox = (*grafo).adj[i].cabeca;
		int u = i;
		int v = prox->vertice;
		float weight = prox->peso;
		if (distance[u] == float_max || distance[u] + weight < distance[v]){
			printf("\nEste gráfico contém um ciclo de aresta negativa\n");
			return 0.1;

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
	printf("a maior distancia eh %.2f\n", maior_distancia);
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

void buscaProfundidade(GRAFO *grafo, int ini, int *visitado, int cont){
    int i;
    visitado[ini] = cont; //Prenchendo os vertices visitados com o numero referente a ordem em que foram visitados

    ADJACENCIA* prox = (*grafo).adj[ini].cabeca;

    while(prox != NULL){ //Percorrendo as arestas do vertice ''ini''

        if(visitado[prox->vertice] == 0){ // se nao visitado
            prox->visited = 1;
            printf("-> %d ", prox->vertice);
            buscaProfundidade(grafo,prox->vertice,visitado,cont+1);

        }
        prox = prox-> prox;
    }
}

void preparaBuscaProfundidade(GRAFO *grafo, int ini){

    int* visitadoo = (int*)calloc(grafo->vertices , sizeof(int));
    int i, cont = 1;
    printf("\nSequencia de vertices visitados na Busca em Profundidade\n %d ",ini);
    buscaProfundidade(grafo,ini, visitadoo,cont);

    for(int j = 0; j < grafo->vertices; j++){
            ADJACENCIA* prox = (*grafo).adj[j].cabeca;
            while(prox != NULL){
                if(prox->visited == 0){
                    printf("Aresta de origem em %d e destino %d nao foi visitada\n", j, prox->vertice);

                }
				prox = prox->prox;
            }

}
}

float procuraMenorDistancia(GRAFO *grafo, int vertice){
    float float_max = FLT_MAX;
	
	int verticesCount = grafo->vertices;
	int edgesCount = grafo->arestas;
	float* distance = (float*)malloc(sizeof(float) * verticesCount);
	int* verticePercorrido = (int*)malloc(sizeof(int) * verticesCount);

	for (int i = 0; i < verticesCount; i++){
		distance[i] = float_max;

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
				prox = prox->prox;
			}
		}
	}
	float menor= distance[0];
	
	for (int i = 1; i < grafo->vertices; i++){
		if(distance[i] < menor){
			menor = distance[i];	
		}
		printf("%f\n",distance[i]);
	}
	
    return menor;
}
void menorCaminho(GRAFO *gr, int ini, int *ant, float *dist){
    float float_min = FLT_MIN;
    int i, cont, NV, ind, *visitado;
	float vert;
    cont = NV = gr->vertices;
    visitado = (int*) malloc(NV * sizeof(int));
    
    for(i=0; i < NV; i++){
        ant[i] = float_min ;
        dist[i] = float_min;
        visitado[i] = 0;
    }
    dist[ini] = 0;
    while(cont > 0){
        vert = procuraMenorDistancia(gr, ini);
        if(vert == (int)float_min)
            break;

        visitado[(int)vert] = 1;
        cont--;
        ADJACENCIA* prox = (*gr).adj[(int)vert].cabeca;
        for(i=0; i<prox->vertice; i++){
            ind = prox->peso;
            if(dist[ind] == float_min){
               dist[ind] =  prox->peso;
               ant[ind] = vert;
            }else{
                if(dist[ind] >  prox->peso){
                    dist[ind] =   prox->peso;
                    ant[ind] = vert;
                }
            }
        }
    }
} 