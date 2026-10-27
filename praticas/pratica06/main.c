#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

int main() {
    int num_vertices = 6;
    GrafoListaPonderado *g = criar_grafo(num_vertices);

    adicionar_aresta(g, 0, 1, 4);
    adicionar_aresta(g, 0, 2, 2);
    adicionar_aresta(g, 1, 2, 1);
    adicionar_aresta(g, 1, 3, 5);
    adicionar_aresta(g, 1, 4, 8);
    adicionar_aresta(g, 2, 3, 4);
    adicionar_aresta(g, 2, 4, 10);
    adicionar_aresta(g, 3, 4, 2);
    adicionar_aresta(g, 3, 5, 5);
    adicionar_aresta(g, 4, 5, 2);

    int dist[6];
    int pred[6];
    int origem = 0;

    dijkstra(g, origem, dist, pred);

    for (int i = 0; i < num_vertices; i++) {
        printf("d(%c) = %d, p(%c) = %c => ", 
               'A' + i, dist[i], 
               'A' + i, (pred[i] == -1) ? 'A' : 'A' + pred[i]);
        reconstruir_caminho(origem, i, pred);
        printf("\n");
    }

    liberar_grafo(g);
    return 0;
}