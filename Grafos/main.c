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
               printf("\n");
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
         printf("\nDigite qual vertice vc quer saber a excentricidade :");
         scanf("%d",&v);
           if (v<0 || v > (ordem_grafo(grafo)-1))
           {
             printf("\n\nNao tem esse vertice no grafo!!!\n\n");
           }
           else
           {

                if (execetridade_grafo(grafo,v)<0)
              {
                
              }
              else
              {
                  printf("execentricidade do vertice %d:%.2f\n",v,execetridade_grafo(grafo,v));
              }  

                       
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
            
            if (raio_grafo(grafo)<0)
              {
                
              }
              else
              {
                  printf("raio do grafo:%.2f\n",raio_grafo(grafo));
              }   
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
              if (diametro_grafo(grafo)<0)
              {
                
              }
              else
              {
                  printf("diamentro do grafo:%.2f\n",diametro_grafo(grafo));
              }
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
          printf("\nDigite vertice de origem da busca em profudidade :");
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
          printf("\nVertice de Origem: ");
          scanf("%d",&v);
          printf("Vertice de Destino: ");
          scanf("%d",&verticeDestino);
           if (v<0 || v > ordem_grafo(grafo)-1)
           {
             printf("\n\nNao tem esse vertice no grafo!!!\n\n");
           }
           else
           {
              
                printf("\nMenor distancia de %d -> %d = %.2f", v, verticeDestino, procuraMenorDistancia(grafo,v,verticeDestino));
              
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
           if (v<0 || v > ordem_grafo(grafo)-1 || verticeDestino<0 || verticeDestino > ordem_grafo(grafo)-1 )
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
              
                printf("\ncentralidade do vertice %d do grafo:%.2f\n",v,centralidadeProximidade(grafo,v)); 
                  
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
        case 16:
            verificaCiclo(grafo);
          break;
          case 17:
             algPrim(grafo);
          break;
      default:
        printf("\n\nOPCAO INVALIDA!!!\n\n");
        break;
      }
    } while (opc!=0);
    
}




