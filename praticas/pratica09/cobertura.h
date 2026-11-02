#ifndef COBERTURA_H
#define COBERTURA_H

#include <stdbool.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct No {
    int vertice;
    struct No* proximo;
} No;

typedef struct {
    int num_vertices;
    No* lista[MAX_VERTICES];
} GrafoLista;

GrafoLista* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoLista* g, int u, int v);
void liberar_grafo(GrafoLista* g);

bool eh_cobertura(GrafoLista *g, bool no_conjunto[]);
void cobertura_minima_bt(GrafoLista *g, int idx, bool atual[], int tam_atual, bool melhor[], int *melhor_tam);
int cobertura_gulosa(GrafoLista *g, bool resultado[]);

#endif