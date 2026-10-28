#include <stdio.h>
#include <stdlib.h>
#include "agm.h"

int main() {
    printf("=== PRATICA 08: ARVORE GERADORA MINIMA (AGM) ===\n\n");

    // Teste com o grafo da Atividade Guiada do Slide 20:
    // V = {A, B, C, D, E} -> (A=0, B=1, C=2, D=3, E=4)
    int num_vertices = 5;
    GrafoLista* g = criar_grafo(num_vertices);

    adicionar_aresta(g, 0, 1, 2); // (A, B, 2)
    adicionar_aresta(g, 0, 2, 3); // (A, C, 3)
    adicionar_aresta(g, 1, 2, 1); // (B, C, 1)
    adicionar_aresta(g, 1, 3, 4); // (B, D, 4)
    adicionar_aresta(g, 2, 3, 5); // (C, D, 5)
    adicionar_aresta(g, 2, 4, 7); // (C, E, 7)
    adicionar_aresta(g, 3, 4, 6); // (D, E, 6)

    printf("--- Algoritmo de Kruskal ---\n");
    Aresta resultado_kruskal[MAX_VERTICES];
    int custo_kruskal = kruskal(g, resultado_kruskal);

    printf("Arestas na AGM:\n");
    for (int i = 0; i < num_vertices - 1; i++) {
        printf("%c - %c (peso %d)\n", 'A' + resultado_kruskal[i].origem, 'A' + resultado_kruskal[i].destino, resultado_kruskal[i].peso);
    }
    printf("Custo total (Kruskal): %d\n\n", custo_kruskal);

    printf("--- Algoritmo de Prim ---\n");
    int pai_prim[MAX_VERTICES];
    int custo_prim = prim(g, 0, pai_prim);

    printf("Arestas na AGM:\n");
    for (int i = 1; i < num_vertices; i++) {
        printf("%c - %c\n", 'A' + pai_prim[i], 'A' + i);
    }
    printf("Custo total (Prim): %d\n", custo_prim);

    liberar_grafo(g);
    return 0;
}