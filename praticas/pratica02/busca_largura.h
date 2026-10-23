#ifndef BUSCA_LARGURA_H
#define BUSCA_LARGURA_H

#include <stdbool.h>

typedef struct No
{
    int vertice;
    struct No *prox;
} No;

typedef struct GrafoLista
{
    int num_vertices;
    No **adj;
} GrafoLista;

typedef struct
{
    int *dados;
    int capacidade;
    int inicio;
    int fim;
    int tamanho;
} Fila;

Fila *criar_fila(int capacidade);
void destruir_fila(Fila *f);
bool fila_vazia(Fila *f);
void enfileirar(Fila *f, int v);
int desenfileirar(Fila *f);

GrafoLista *criar_grafo(int vertices);
void destruir_grafo(GrafoLista *g);
void adicionar_aresta(GrafoLista *g, int u, int v);

void bfs(GrafoLista *g, int origem, int *dist, int *pred);
bool eh_bipartido(GrafoLista *g);

#endif