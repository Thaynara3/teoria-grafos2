#ifndef AGM_H
#define AGM_H

#include <stdbool.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define MAX_ARESTAS 1000

typedef struct {
    int origem;
    int destino;
    int peso;
} Aresta;

typedef struct {
    int pai[MAX_VERTICES];
    int nivel[MAX_VERTICES];
} UnionFind;

typedef struct No {
    int vertice;
    int peso;
    struct No* proximo;
} No;

typedef struct {
    int num_vertices;
    No* lista[MAX_VERTICES];
} GrafoLista;

typedef UnionFind DSU;

GrafoLista* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoLista* g, int u, int v, int peso);
void liberar_grafo(GrafoLista* g);

void inicializar_union_find(UnionFind *uf, int n);
int encontrar(UnionFind *uf, int x);
int unir(UnionFind *uf, int a, int b);

DSU* criar_dsu(int n);
int find(DSU *d, int x);
bool unir_dsu(DSU *d, int x, int y);
void liberar_dsu(DSU *d);

int kruskal(GrafoLista *g, Aresta *resultado_mst);
int prim(GrafoLista *g, int origem, int *pai);

#endif