#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dag.h"

GrafoLista* criar_grafo(int vertices) {
    GrafoLista *g = (GrafoLista*) malloc(sizeof(GrafoLista));
    g->num_vertices = vertices;
    g->lista_adj = (No**) malloc(vertices * sizeof(No*));
    for (int i = 0; i < vertices; i++) {
        g->lista_adj[i] = NULL;
    }
    return g;
}

void adicionar_aresta(GrafoLista *g, int orig, int dest) {
    No *novo = (No*) malloc(sizeof(No));
    novo->destino = dest;
    novo->prox = g->lista_adj[orig];
    g->lista_adj[orig] = novo;
}

void destruir_grafo(GrafoLista *g) {
    if (!g) return;
    for (int i = 0; i < g->num_vertices; i++) {
        No *atual = g->lista_adj[i];
        while (atual != NULL) {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->lista_adj);
    free(g);
}

int* ordenacao_topologica_kahn(GrafoLista *g, int *tamanho) {
    int n = g->num_vertices;
    int *grau_entrada = (int*) calloc(n, sizeof(int));

    for (int u = 0; u < n; u++) {
        No *atual = g->lista_adj[u];
        while (atual != NULL) {
            grau_entrada[atual->destino]++;
            atual = atual->prox;
        }
    }

    int *fila = (int*) malloc(n * sizeof(int));
    int inicio = 0, fim = 0;

    for (int i = 0; i < n; i++) {
        if (grau_entrada[i] == 0) {
            fila[fim++] = i;
        }
    }

    int *resultado = (int*) malloc(n * sizeof(int));
    int count = 0;

    while (inicio < fim) {
        int u = fila[inicio++];
        resultado[count++] = u;

        No *atual = g->lista_adj[u];
        while (atual != NULL) {
            int v = atual->destino;
            grau_entrada[v]--;
            if (grau_entrada[v] == 0) {
                fila[fim++] = v;
            }
            atual = atual->prox;
        }
    }

    free(grau_entrada);
    free(fila);

    if (count != n) {
        free(resultado);
        *tamanho = 0;
        return NULL;
    }

    *tamanho = n;
    return resultado;
}

static bool dfs_topologica_aux(int u, GrafoLista *g, int *estado, int *resultado, int *idx) {
    estado[u] = 1; 

    No *atual = g->lista_adj[u];
    while (atual != NULL) {
        int v = atual->destino;
        if (estado[v] == 1) {
            
            return false;
        }
        if (estado[v] == 0) {
            if (!dfs_topologica_aux(v, g, estado, resultado, idx)) {
                return false;
            }
        }
        atual = atual->prox;
    }

    estado[u] = 2; 
    resultado[(*idx)--] = u; 
    return true;
}

int* ordenacao_topologica_dfs(GrafoLista *g, int *tamanho) {
    int n = g->num_vertices;
    int *estado = (int*) calloc(n, sizeof(int));
    int *resultado = (int*) malloc(n * sizeof(int));
    int idx = n - 1;

    for (int i = 0; i < n; i++) {
        if (estado[i] == 0) {
            if (!dfs_topologica_aux(i, g, estado, resultado, &idx)) {
                free(estado);
                free(resultado);
                *tamanho = 0;
                return NULL; 
            }
        }
    }

    free(estado);
    *tamanho = n;
    return resultado;
}

int eh_dag(GrafoLista *g) {
    int tamanho = 0;
    int *ordem = ordenacao_topologica_kahn(g, &tamanho);
    if (ordem != NULL) {
        free(ordem);
        return 1; 
    }
    return 0; 
}