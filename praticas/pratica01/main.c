#include <stdio.h>
#include "grafo_matriz.h"
#include "grafo_lista.h"

int main() {
    printf("=== TESTANDO GRAFO MATRIZ ===\n\n");

    GrafoMatriz *grafo_m = criar_grafo_matriz(8);

    inserir_aresta_matriz(grafo_m, 0, 1);
    inserir_aresta_matriz(grafo_m, 0, 2);
    inserir_aresta_matriz(grafo_m, 0, 3);
    inserir_aresta_matriz(grafo_m, 1, 4);
    inserir_aresta_matriz(grafo_m, 1, 5);
    inserir_aresta_matriz(grafo_m, 2, 3);
    inserir_aresta_matriz(grafo_m, 2, 6);
    inserir_aresta_matriz(grafo_m, 3, 6);
    inserir_aresta_matriz(grafo_m, 7, 4);
    inserir_aresta_matriz(grafo_m, 7, 5);
    inserir_aresta_matriz(grafo_m, 7, 6);

    printf("Matriz de Adjacencia - Grafo nao orientado:\n");
    exibir_matriz(grafo_m);

    printf("\nGrau do vertice 0: %d\n", grau_matriz(grafo_m, 0));
    printf("Vertices 0 e 1 sao adjacentes? %s\n", sao_adjacentes_matriz(grafo_m, 0, 1) ? "Sim" : "Nao");
    printf("Vertices 0 e 4 sao adjacentes? %s\n", sao_adjacentes_matriz(grafo_m, 0, 4) ? "Sim" : "Nao");

    remover_aresta_matriz(grafo_m, 0, 1);
    printf("\nApos remover a aresta (0,1):\n");
    printf("Grau do vertice 0: %d\n", grau_matriz(grafo_m, 0));
    printf("Vertices 0 e 1 sao adjacentes? %s\n", sao_adjacentes_matriz(grafo_m, 0, 1) ? "Sim" : "Nao");

    liberar_grafo_matriz(grafo_m);


    printf("\n=== TESTANDO GRAFO LISTA ===\n\n");

    GrafoLista *grafo_l = criar_grafo_lista(8);

    inserir_aresta_lista(grafo_l, 0, 1);
    inserir_aresta_lista(grafo_l, 0, 2);
    inserir_aresta_lista(grafo_l, 0, 3);
    inserir_aresta_lista(grafo_l, 1, 4);
    inserir_aresta_lista(grafo_l, 1, 5);

    printf("Grau do vertice 0 na lista: %d\n", grau_lista(grafo_l, 0));
    printf("Vertices 0 e 1 sao adjacentes na lista? %s\n", sao_adjacentes_lista(grafo_l, 0, 1) ? "Sim" : "Nao");

    remover_aresta_lista(grafo_l, 0, 1);
    printf("Apos remover aresta (0,1), grau do vertice 0: %d\n", grau_lista(grafo_l, 0));

    liberar_grafo_lista(grafo_l);

    return 0;
}