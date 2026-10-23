#ifndef COLORACAO_H
#define COLORACAO_H

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

int* coloracao_gulosa(GrafoLista *g, int *num_cores);
int* coloracao_welsh_powell(GrafoLista *g, int *num_cores);
bool eh_bipartido(GrafoLista *g);

#endif 