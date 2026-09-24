#ifndef DAG_H
#define DAG_H

#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int destino;
    struct No *prox;
} No;

typedef struct
{
    int num_vertices;
    No **lista_adj;
} GrafoLista;

GrafoLista *criar_grafo(int vertices);
void adicionar_aresta(GrafoLista *g, int orig, int dest);
void destruir_grafo(GrafoLista *g);

int *ordenacao_topologica_kahn(GrafoLista *g, int *tamanho);
int *ordenacao_topologica_dfs(GrafoLista *g, int *tamanho);
int eh_dag(GrafoLista *g);

#endif