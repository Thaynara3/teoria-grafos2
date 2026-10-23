#ifndef CONECTIVIDADE_H
#define CONECTIVIDADE_H
#ifndef MAX_VERTICES
#define MAX_VERTICES 100
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct No {
    int destino;
    struct No* prox;
} No;

typedef struct {
    int num_vertices;
    No* lista[MAX_VERTICES];
} GrafoLista;

GrafoLista* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoLista* g, int u, int v);
void liberar_grafo(GrafoLista* g);

void dfs_articulacoes(GrafoLista* g, int u, bool visitado[], int descoberta[], int low[], int pai[], bool articulacao[], int* tempo);
void detectar_articulacoes_e_pontes(GrafoLista* g);

#endif