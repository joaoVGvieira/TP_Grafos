#include "../Libs/grafo.h"
#include <math.h>
#include <float.h>

int N=0;
#define TRUE 1;
#define FALSE 0;
#define INT_MAX   (2147483647)

//funçao para criar um GRAFO
GRAFO *criaGrafo (int v) {
	int i;
	
	GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO)); //aloca espaço para estrtura grafo
	g->vertices = v; //atualizo o numero de vertice
	g->arestas = 0;  //atualizo o numero de arestas
	g->adj = (VERTICE *)calloc(v, sizeof(VERTICE)); //ler abaixo
	//Dentro da estrturua tem se o arranjo para o ponteiro de vertice, nao o arranjo em si 	
	// entao aloco o arranjo com (v) o numero de vertice desejado
	for (i=0; i<v; i++){ 
		g->adj[i].cabeca=NULL; //coloco NULL em todas arestas
		g->adj[i].grau = 0;
	}
	g->M = alocaMatriz(v);
	return(g);
}


void GRAPHInsert(GRAFO *G, int u, int v, float custo){
    /* A função insere uma aresta uv na matriz de incidências
     * e guarda o custo da aresta no vetor de custos.
    */
    if(G->M[u][v] != custo || G->M[v][u] != custo){ //Verifica se já não há tal aresta
        G->M[u][v] = custo;
        G->M[v][u] = custo;
    }
}

float **alocaMatriz(int v){
    int i, j;
    float **m = malloc(v * sizeof(float *));
    if(m == NULL) return NULL; //memória insuficiente
    for (i = 0; i < v; i++){
        m[i] = malloc((v * sizeof(float)));
        if(m[i] == NULL){ //memória insuficiente
            for(j = 0; j < i; j++) free(m[j]);
            free(m);
            return NULL;
        }
    }
    for(i = 0; i < v; i++) //preenchendo os espaços com infinito
        for(j = 0; j < v; j++)
            m[i][j] = FLT_MAX;

    return m;
}//alocaMatriz()

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

	grafo->adj[verticeInicial].grau +=1;

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

	grafo->adj[verticeFinal].grau +=1;
	grafo->arestas++;

	return;
}

void imprime(GRAFO *grafo){

    printf("\n==== Info do Grafo ===\n");
	printf("Vertices: %d. Arestas: %d. \n",grafo->vertices,grafo->arestas); //imprime numero de vertices e arestas
	int i;
	for(i=0; i< grafo->vertices; i++){
		printf("%d: ",i); //imprimir em qual aresta esta
		ADJACENCIA *ad = grafo->adj[i].cabeca; //chamo a cebeça da lista de adjacencia desta aresta
			while(ad){ //enquanto as adjacencias nao forem nula
				printf("%d(%.2f) ",ad->vertice,ad->peso); //imprimir a adjacencia e o peso
				ad=ad->prox; //vai para a proxima adjacencia
			}
			
		printf("\n");	
	}
}

int ordem_grafo(GRAFO *grafo){
	return grafo->vertices;
}

int tamanho_grafo(GRAFO *grafo){
	return grafo->arestas;
}

void grauVerices(GRAFO *grafo){

	for(int i = 0; i < grafo->vertices; i ++){
		printf("Grau do vertice %d = %d \n", i, grafo->adj[i].grau);
	}
	
}

void vizinho_vertice(GRAFO *grafo, int num){
	int i;
	for(i=0; i< grafo->vertices; i++){
		if (i == num)
		{
			printf("\n\nVizinhos de %d: ",i);
			ADJACENCIA *ad = grafo->adj[i].cabeca; //chamo a cebeça da lista de adjacencia desta aresta
			while(ad){ //enquanto as adjacencias nao forem nula
				printf("%d ",ad->vertice); //imprimir a adjacencia e o peso
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
			printf("\nGrau do vertice %d: ",i);
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

float execetridade_grafo(GRAFO *grafo, int vertice){

	float float_max = FLT_MAX;

	//Inicializa os vetores e variaveis
	int verticesCount = grafo->vertices;
	int edgesCount = grafo->arestas;
	float* distance = (float*)malloc(sizeof(float) * verticesCount);
	int* verticePercorrido = (int*)malloc(sizeof(int) * verticesCount);

	for (int i = 0; i < verticesCount; i++){
		distance[i] = float_max;
	}

	distance[vertice] = 0;

	//Laco principal que calcula todas as distancias
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

	//verifica se ha ciclo de aresta negativa
	for (int i = 0; i < grafo->vertices; i++){
		ADJACENCIA* prox = (*grafo).adj[i].cabeca;
		int u = i;
		int v = prox->vertice;
		float weight = prox->peso;
		if (distance[u] != float_max && distance[u] + weight < distance[v]){
			if (N==0)
			{
				printf("\nEste grafo contem um ciclo de aresta negativa\n");
				N++;
			}
		}
				 		
	}

	float maior_distancia = distance[0];

	//Pega a maior distancia para todos os vertices do grafo(excentricidade)
	for (int i = 1; i < grafo->vertices; i++){
		if(distance[i] > maior_distancia){
			maior_distancia = distance[i];	
		}
	}

	return maior_distancia;
}

float raio_grafo(GRAFO *grafo){
	float raio;
	int vertice;
	N=0;

	for(int i = 0; i < grafo->vertices; i++){
		if(i == 0){
			raio = execetridade_grafo(grafo, i);
			vertice = 0;
		}
		if(execetridade_grafo(grafo, i) < raio){
			raio = execetridade_grafo(grafo, i);
			vertice = i;
		}
	}

	return raio;
}

float diametro_grafo(GRAFO *grafo){

	float diametro;
	int vertice;
	N = 0;
	for(int i = 0; i < grafo->vertices; i++){
		if(i == 0){
			diametro = execetridade_grafo(grafo, i);
			vertice = 0;
		}
		if(execetridade_grafo(grafo, i) > diametro){
			diametro = execetridade_grafo(grafo, i);
			vertice = i;
		}
	}

	return diametro;
}

void centro_grafo(GRAFO *grafo){

	float float_max = FLT_MAX;

	//Inicializa os vetores e variaveis
	int verticesCount = grafo->vertices;
	int edgesCount = grafo->arestas;
	float* distance = (float*)malloc(sizeof(float) * verticesCount);
	int* verticePercorrido = (int*)malloc(sizeof(int) * verticesCount);

	for (int i = 0; i < verticesCount; i++){
		distance[i] = float_max;
	}
	int vertice =0;
	distance[vertice] = 0;

	//Laco principal que calcula todas as distancias
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

	//verifica se ha ciclo de aresta negativa
	for (int i = 0; i < grafo->vertices; i++){
		ADJACENCIA* prox = (*grafo).adj[i].cabeca;
		int u = i;
		int v = prox->vertice;
		float weight = prox->peso;
		if (distance[u] != float_max && distance[u] + weight < distance[v]){
			printf("\nEste grafo contem um ciclo de aresta negativa\n");
			return;

		}
				 		
	}




	if(execetridade_grafo(grafo, 0) == 0.0125){
		printf("\nEste grafo contem um ciclo de aresta negativa\n");
		 return;
	}

	printf("\nVertices que fazer parte do centro: ");
    for(int i = 0; i < grafo->vertices; i++){
      	if(execetridade_grafo(grafo, i) == raio_grafo(grafo)){
        	printf("%d ", i+1);
      	}
    }
	return;
}

float centralidadeProximidade(GRAFO *grafo, int vertice){

	float float_max = FLT_MAX;

	//Inicializa vetores e variaveis
	int verticesCount = grafo->vertices;
	int edgesCount = grafo->arestas;
	float* distance = (float*)malloc(sizeof(float) * verticesCount);
	int* verticePercorrido = (int*)malloc(sizeof(int) * verticesCount);

	for (int i = 0; i < verticesCount; i++){
		distance[i] = float_max;
	}

	distance[vertice] = 0;

	//Laco principal verifica as distancias
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

	float soma = 0;
	
	//Soma as distancias
	for (int i = 0; i < grafo->vertices; i++){
		soma += distance[i];
	}
	//Retorna a centralicade efetuando a conta necessaria

	for (int i = 0; i < grafo->vertices; i++){
		ADJACENCIA* prox = (*grafo).adj[i].cabeca;
		int u = i;
		int v = prox->vertice;
		float weight = prox->peso;
		if (distance[u] != float_max && distance[u] + weight < distance[v]){
			printf("\nEste grafo contem um ciclo de aresta negativa\n");
			return 0.0125;

		}
				 		
	}

	return (verticesCount-1)/soma;
}

void preencheVisitado(GRAFO *grafo, int verticeOrigem, int verticeDestino){

	ADJACENCIA* prox = (*grafo).adj[verticeDestino].cabeca;
	while(prox != NULL){ //Percorrendo as arestas do vertice ''ini''

		if(prox->vertice == verticeOrigem){
			prox->visited = 1;
		}
		prox = prox-> prox;
	}
}


void buscaProfundidade(GRAFO *grafo, int ini, int *visitado, int cont){
    int i;
    visitado[ini] = cont; //Prenchendo os vertices visitados com o numero referente a ordem em que foram visitados
	// ini vertice origem
	// prox->vertice vertice destino
    ADJACENCIA* prox = (*grafo).adj[ini].cabeca;

    while(prox != NULL){ //Percorrendo as arestas do vertice ''ini''

        if(visitado[prox->vertice] == 0){ // se nao visitado
            prox->visited = 1;
			preencheVisitado(grafo,  ini, prox->vertice);
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
	printf("\n");

	//Verifica quais arestas nao foram visitadas
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



float procuraMenorDistancia(GRAFO *grafo, int vertice, int verticeDestino){
    float float_max = FLT_MAX;
	
	//Inicializa vetores e variaveis
	int verticesCount = grafo->vertices;
	int edgesCount = grafo->arestas;
	float* distance = (float*)malloc(sizeof(float) * verticesCount);
	int* verticePercorrido = (int*)malloc(sizeof(int) * verticesCount);

	for (int i = 0; i < verticesCount; i++){
		distance[i] = float_max;

	}
	
	
	distance[vertice] = 0;
	int vets[vertice];
	int cont=0;

	//Laco principal para calcular as distancias
	for(int i = 1; i <= verticesCount; i ++){
		for(int j = 0; j < verticesCount; j++){
			ADJACENCIA* prox = (*grafo).adj[j].cabeca;
			while(prox != NULL){

				int u = j;
				int v = prox->vertice;
				float weight = prox->peso;

				if (distance[u] != float_max && distance[u] + weight < distance[v]){
					distance[v] = distance[u] + weight;
				}
				prox = prox->prox;
			}
		}
	}
	
	for (int i = 0; i < grafo->vertices; i++){
		ADJACENCIA* prox = (*grafo).adj[i].cabeca;
		int u = i;
		int v = prox->vertice;
		float weight = prox->peso;
		if (distance[u] != float_max && distance[u] + weight < distance[v]){
			printf("\nEste grafo contem um ciclo de aresta negativa\n");
			return 0.0125;

		}
				 		
	}

    return distance[verticeDestino];
}




//Funcao auxiliar da Dijkstra
void relaxa(GRAFO *grafo, float *distancia, int *antecessor, int verticeOrigem, int verticeDestino){

    ADJACENCIA *aux = grafo->adj[verticeOrigem].cabeca;

    while(aux->vertice != verticeDestino && aux) aux = aux->prox;

    if(aux != NULL){
        if(distancia[verticeDestino] > distancia[verticeOrigem] + aux->peso){
            distancia[verticeDestino] = distancia[verticeOrigem] + aux->peso;
            antecessor[verticeDestino] = verticeOrigem;
        }
    }
    return;
}

//Funcao auxiliar da Dijkstra
int existeAberto(GRAFO *grafo, int *aberto){
    for(int i = 0; i< grafo->vertices; i++) if(aberto[i]) return(1);
    return(0);  
}

//Funcao auxiliar da Dijkstra
int MenorDistancia(GRAFO *grafo, int *aberto, float *distancia){
    int i;
    for(i = 0; grafo->vertices; i++) if(aberto[i]) break;
    
    if(i == grafo->vertices) return -1;

    int menor = i;

    for(i = menor + 1; i < grafo->vertices; i++){
        if(aberto[i] && distancia[menor] > distancia[i]) menor = i;
    }
    return menor;

}

void Dijkstra(GRAFO *grafo, int verticeOrigem, int verticeDestino){

	//Condicional que verifica se o grafo possui pesos negativos

	for(int j = 0; j < grafo->vertices; j++){
			ADJACENCIA* prox = (*grafo).adj[j].cabeca;
			while(prox != NULL){

				if(prox->peso < 0){
					printf("\nO grafo possui peso negativo, nao e possivel calcular o caminho minimo!\n");
					return;
				}

				prox = prox->prox;
			}
	}

	//Prepara vetores
    float *distancia = (float*)malloc(grafo->vertices * sizeof(float));
    int *antecessor = (int*)malloc(grafo->vertices * sizeof(int));
    int *aberto = (int*)malloc(grafo->vertices * sizeof(int));

	//Inicializa os vetores
    for(int i = 0; i < grafo->vertices; i++){
        distancia[i] = INT_MAX/2;
        antecessor[i] = -1;
        aberto[i] = 1;
    } 
    distancia[verticeOrigem] = 0;    
	//Comeca algoritmo dijkstra
    while(existeAberto(grafo, aberto)){
        int u = MenorDistancia(grafo, aberto, distancia);
        aberto[u] = 0;
        ADJACENCIA* ad = grafo->adj[u].cabeca;
        while(ad != NULL){
            relaxa(grafo, distancia, antecessor, u, ad->vertice);
            ad = ad->prox;
        }
    }

	int vertice = verticeDestino;
	printf("\n");

	//Printa o menor caminho ate o vertice de destino
	while(vertice != verticeOrigem){
		printf("%d <- ", vertice);
		vertice = antecessor[vertice];
	}
	printf("%d",verticeOrigem);
	
}

bool conjZ(bool *z, int V){
    int v;
    for(v = 0; v < V; v++){
        if(!z[v]) return true;
    }
    return false;
}


void printArvore(int *ant, float *chave, int V){
    int i=0; 
	float custo = 0;
	FILE *arq;
	arq = fopen("arvore.txt", "w");
	if (arq == NULL) // Se não conseguiu criar
	{	
   		printf("Problemas na CRIACAO do arquivo\n");
   		return;
	}else{
		fprintf(arq," == Arvore geradora minima ==  \n");
		for(i = 1; i < V; i++){
			fprintf(arq,"%d %d %.2f\n",ant[i],i,chave[i]);
			custo += chave[i];
		}
		fprintf(arq,"Custo Total: %.2f", custo);
		fclose(arq);
	}
		
}

int minValor(float chave[], bool z[], int V) {
    float min = FLT_MAX, min_index = 0, v;

    for (int v = 0; v < V; v++){
        if (z[v] == false && chave[v] < min){
            min = chave[v];
            min_index = v;
        }
    }
    return min_index;
}

void algPrim(GRAFO *G){
	int qtdV = G->vertices;
    int ant[qtdV]; //Vetor para armazenar a AGM
    float chave[qtdV]; //Vetor que armazena os custos mínimos da fronteira de cada vértice
    bool z[qtdV]; //Vetor que armazena os vértices inseridos no conjunto Z
    int i, j, v;

    for(i = 0; i < qtdV; i++) { //Iniciando vetores
        z[i] = false;
        chave[i] = FLT_MAX;
    }

    //O vértice 0 será a raiz da AGM
    chave[0] = 0;
    ant[0] = -1;

    //Enquanto existir vértice não inserido em Z
    while(conjZ(z, qtdV)){
        int u = minValor(chave, z, qtdV); //Busca o indice com aresta de menor custo na fronteira
        z[u] = true; //Insere u em Z

        //Atualize o valor da chave e o índice anterior dos vértices adjacentes ao vértice selecionado.
        //Considere apenas os vértices que ainda não estão incluídos na AGM
        for(v = 0; v < qtdV; v++){
            if(G->M[u][v] && z[v] == false && G->M[u][v] <= chave[v]){
                ant[v] = u;
                chave[v] = G->M[u][v];
            }
        }
    }

    printArvore(ant, chave, qtdV);
}


void buscaCiclo(GRAFO *grafo, int ini, int *visitado, int cont){
    int i;
    visitado[ini] = cont; //Prenchendo os vertices visitados com o numero referente a ordem em que foram visitados
	// ini vertice origem
	// prox->vertice vertice destino
    ADJACENCIA* prox = (*grafo).adj[ini].cabeca;

    while(prox != NULL){ //Percorrendo as arestas do vertice ''ini''

        if(visitado[prox->vertice] == 0){ // se nao visitado
            prox->visited = 1;
			preencheVisitado(grafo,  ini, prox->vertice);
            buscaCiclo(grafo,prox->vertice,visitado,cont+1);

        }
        prox = prox-> prox;
    }
}

void verificaCiclo(GRAFO *grafo){
	int ini = 0;
	bool temciclo = false;
    int* visitadoo = (int*)calloc(grafo->vertices , sizeof(int));
    int i, cont = 1;

    buscaCiclo(grafo,ini, visitadoo,cont);
	//Verifica quais arestas nao foram visitadas
    for(int j = 0; j < grafo->vertices; j++){
            ADJACENCIA* prox = (*grafo).adj[j].cabeca;
            while(prox != NULL){
                if(prox->visited == 0){
                    printf("\nO grafo possui ciclo!\n");
					temciclo= true;
					j= grafo->vertices;
					break;
                }
				prox = prox->prox;
            }

	}
	if (temciclo!=true)
	{
		printf("\nO grafo nao possui ciclo!\n");
	}
	for(int j = 0; j < grafo->vertices; j++){
            ADJACENCIA* prox = (*grafo).adj[j].cabeca;
            while(prox != NULL){
				prox->visited = 0;
				prox = prox->prox;
            }

	}
}