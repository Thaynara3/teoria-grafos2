#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "busca_largura.h"

Fila* criar_fila(int capacidade) {
    Fila *f = (Fila*) malloc(sizeof(Fila));
    f->capacidade = capacidade;
    f->dados = (int*) malloc(capacidade * sizeof(int));
    f->inicio = 0;
    f->fim = -1;
    f->tamanho = 0;
    return f;
}

void destruir_fila(Fila *f) {
    if (f) {
        free(f->dados);
        free(f);
    }
}

bool fila_vazia(Fila *f) {
    return f->tamanho == 0;
}

void enfileirar(Fila *f, int v) {
    if (f->tamanho == f->capacidade) return;
    f->fim = (f->fim + 1) % f->capacidade;
    f->dados[f->fim] = v;
    f->tamanho++;
}

int desenfileirar(Fila *f) {
    if (fila_vazia(f)) return -1;
    int v = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->tamanho--;
    return v;
}

GrafoLista* criar_grafo(int vertices) {
    GrafoLista *g = (GrafoLista*) malloc(sizeof(GrafoLista));
    g->num_vertices = vertices;
    g->adj = (No**) malloc(vertices * sizeof(No*));
    for (int i = 0; i < vertices; i++) {
        g->adj[i] = NULL;
    }
    return g;
}

void destruir_grafo(GrafoLista *g) {
    if (!g) return;
    for (int i = 0; i < g->num_vertices; i++) {
        No *atual = g->adj[i];
        while (atual) {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->adj);
    free(g);
}

void adicionar_aresta(GrafoLista *g, int u, int v) {
    No *novo1 = (No*) malloc(sizeof(No));
    novo1->vertice = v;
    novo1->prox = g->adj[u];
    g->adj[u] = novo1;

    No *novo2 = (No*) malloc(sizeof(No));
    novo2->vertice = u;
    novo2->prox = g->adj[v];
    g->adj[v] = novo2;
}

void bfs(GrafoLista *g, int origem, int *dist, int *pred) {
    for (int i = 0; i < g->num_vertices; i++) {
        dist[i] = -1;
        pred[i] = -1;
    }

    Fila *f = criar_fila(g->num_vertices);
    dist[origem] = 0;
    enfileirar(f, origem);

    while (!fila_vazia(f)) {
        int u = desenfileirar(f);

        No *vert = g->adj[u];
        while (vert != NULL) {
            int v = vert->vertice;
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                pred[v] = u;
                enfileirar(f, v);
            }
            vert = vert->prox;
        }
    }

    destruir_fila(f);
}

bool eh_bipartido(GrafoLista *g) {
    int *cor = (int*) malloc(g->num_vertices * sizeof(int));
    for (int i = 0; i < g->num_vertices; i++) {
        cor[i] = 0;
    }

    Fila *f = criar_fila(g->num_vertices);

    for (int i = 0; i < g->num_vertices; i++) {
        if (cor[i] == 0) {
            cor[i] = 1;
            enfileirar(f, i);

            while (!fila_vazia(f)) {
                int u = desenfileirar(f);

                No *vert = g->adj[u];
                while (vert != NULL) {
                    int v = vert->vertice;
                    if (cor[v] == 0) {
                        cor[v] = (cor[u] == 1) ? 2 : 1;
                        enfileirar(f, v);
                    } else if (cor[v] == cor[u]) {
                        free(cor);
                        destruir_fila(f);
                        return false;
                    }
                    vert = vert->prox;
                }
            }
        }
    }

    free(cor);
    destruir_fila(f);
    return true;
}