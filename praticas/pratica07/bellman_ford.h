#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#ifndef MAX_VERTICES
#define MAX_VERTICES 100
#endif

#define INF 1000000000

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Aresta {
    int destino;
    int peso;
    struct Aresta* prox;
} Aresta;

typedef struct {
    int num_vertices;
    Aresta* lista[MAX_VERTICES];
} GrafoListaPonderado;

GrafoListaPonderado* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoListaPonderado* g, int u, int v, int peso);
void liberar_grafo(GrafoListaPonderado* g);

int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred);
void reconstruir_ciclo_negativo(GrafoListaPonderado *g, int vertice_no_ciclo, int *pred);
void reconstruir_caminho(int origem, int destino, int *pred);

#endif 