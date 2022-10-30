#include <stdio.h>
#include <stdlib.h>
#include "Libs/grafo.h"
#include "Libs/menu.h"

int main(){
    FILE *fp;
    int opc;
    int v, verticeDestino;
    int quant_vertice;
    int a1,a2;
    float peso, menor_excentricidade;
    int ordem,tamanho;
    char nome_arquivo[1000];
    int exist = 0;
    do
    {
      menu_principal();
      scanf("%d",&opc);
      switch (opc)
      {
      case 1:
         printf("DIGITE O NOME DO ARQUIVO DE ENTRADA: ");
         scanf(" %[^\n]s ",nome_arquivo);
         fp = fopen(nome_arquivo,"r");
          if (fp == NULL)
          {
            printf("\n\nNome de arquivo digitado errado!!!!\n\n");
            break;
          }else
          {
            printf("\n\nLeitura realizada com sucesso!!!\n\n");
          }
          
         fscanf(fp,"%d\n",&quant_vertice);
         GRAFO *grafo = criaGrafo(quant_vertice);
          while (!feof(fp)){
             fscanf (fp,"%d %d %f\n", &a1,&a2,&peso);
             criaAresta(grafo,a1,a2,peso);
          }
          exist=1;   
        break;
      case 2:
         if (fp==NULL)
         {
           printf("\n\nNao existe grafo !!!!\n\n");
         }
         else
         {
          printf("\nOrdem do grafo:%d\n\n",ordem_grafo(grafo));
         }
        break;
        case 3:
         if (fp==NULL)
         {
           printf("\n\nNao existe grafo !!!!\n\n");
         }
         else
         {
            printf("\nTamanho do grafo:%d\n\n",tamanho_grafo(grafo));
         }
        break;
        case 4:
         if (fp==NULL)
         {
           printf("\n\nNao existe grafo !!!!\n\n");
         }
         else
         {
           printf("\nDigite qual vertice vc quer saber os vizinhos:");
           scanf("%d",&v);
           if (v<0 || v > ordem_grafo(grafo)-1)
           {
             printf("\n\nNao tem esse vertice no grafo!!!\n\n");
           }
           else
           {
              vizinho_vertice(grafo,v);
           }
           printf("\n");
         }
        break;
        case 5:
         if (fp==NULL)
         {
           printf("\n\nNao existe grafo !!!!\n\n");
         }
         else
         {
            printf("\n");
            sequencia_graus(grafo);
         }
         printf("\n\n");
        break;
        case 6:
            if (fp==NULL)
         {
           printf("\n\nNao existe grafo !!!!\n\n");
         }
         else
         {
           printf("\nDigite qual vertice vc quer saber o grau :");
           scanf("%d",&v);
           if (v<0 || v > ordem_grafo(grafo)-1)
           {
             printf("\n\nNao tem esse vertice no grafo!!!\n\n");
           }
           else
           {
              grau_vertice(grafo,v);
           }
           printf("\n");
         }
        break;
        case 7:
         if (fp==NULL)
         {
           printf("\n\nNao existe grafo !!!!\n\n");
         }
         else
         {
         printf("\nDigite qual vertice vc quer saber o excentricidade :");
         scanf("%d",&v);
           if (v<0 || v > ordem_grafo(grafo)-1)
           {
             printf("\n\nNao tem esse vertice no grafo!!!\n\n");
           }
           else
           {
              execetridade_grafo(grafo,v);
           }
           printf("\n");
         }
        break;
        case 8:
         if (fp==NULL)
         {
           printf("\n\nNao existe grafo !!!!\n\n");
         }
         else
         {
            printf("\n\n");
            printf("Raio do grafo:%2.f\n",raio_grafo(grafo));
         }
         printf("\n\n");
        break;
        case 9:
         if (fp==NULL)
         {
           printf("\n\nNao existe grafo !!!!\n\n");
         }
         else
         {
            printf("\n\n");
            printf("diamentro do grafo:%2.f\n",diametro_grafo(grafo));
         }
         printf("\n\n");
        break;
        case 10:
         if (fp==NULL)
         {
           printf("\n\nNao existe grafo !!!!\n\n");
         }
         else
         {
            printf("\n");
            centro_grafo(grafo);
         }
         printf("\n\n");
        break;
        case 11:
         if (fp==NULL)
         {
           printf("\n\nNao existe grafo !!!!\n\n");
         }
         else
         {
          printf("\nDigite qual vertice vc quer saber a profudidade :");
          scanf("%d",&v);
           if (v<0 || v > ordem_grafo(grafo)-1)
           {
             printf("\n\nNao tem esse vertice no grafo!!!\n\n");
           }
           else
           {
              preparaBuscaProfundidade(grafo,v);
           }
           printf("\n");
         }
          break;
        case 12:
         if (fp==NULL)
         {
           printf("\n\nNao existe grafo !!!!\n\n");
         }
         else
         {
          printf("\nDigite qual vertice vc quer saber a distancia :");
          scanf("%d",&v);
           if (v<0 || v > ordem_grafo(grafo)-1)
           {
             printf("\n\nNao tem esse vertice no grafo!!!\n\n");
           }
           else
           {
              procuraMenorDistancia(grafo,v);
           }
           printf("\n");
         }
          break;
         case 13:
          if (fp==NULL)
         {
           printf("\n\nNao existe grafo !!!!\n\n");
         }
         else
         {
          printf("\nVertice de origem: ");
          scanf("%d",&v);
          printf("Vertice de destino: ");
          scanf("%d",&verticeDestino);
           if (v<0 || v > ordem_grafo(grafo)-1)
           {
             printf("\n\nNao tem esse vertice no grafo!!!\n\n");
           }
           else
           {
              Dijkstra(grafo,v,verticeDestino);
           }
           printf("\n");
         }
          break;
        case 14:
           if (fp==NULL)
         {
           printf("\n\nNao existe grafo !!!!\n\n");
         }
         else
         {
          printf("\nDigite qual vertice vc quer saber a centralidade :");
          scanf("%d",&v);
           if (v<0 || v > ordem_grafo(grafo)-1)
           {
             printf("\n\nNao tem esse vertice no grafo!!!\n\n");
           }
           else
           {
              printf("centralidade do vertice %d do grafo:%2.f\n",v,centralidadeProximidade(grafo,v));
           }
           printf("\n");
         }
          break;
         case 15:
           if (fp==NULL)
         {
           printf("\n\nNao existe grafo !!!!\n\n");
         }
         else
         {
          printf("\n");
          imprime(grafo);
           printf("\n");
         }
          break; 
        case 0:
           printf("\n\nVolte Sempre!!!!\n\n");
        break;
      default:
        printf("\n\nOPCAO INVALIDA!!!\n\n");
        break;
      }
    } while (opc!=0);
    
}




