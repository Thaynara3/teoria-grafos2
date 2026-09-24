#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "busca_profundidade.h"

Pilha* criar_pilha(int capacidade) {
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    p->capacidade = capacidade;
    p->topo = -1;
    p->dados = (int*) malloc(capacidade * sizeof(int));
    return p;
}

void destruir_pilha(Pilha *p) {
    if (p) {
        free(p->dados);
        free(p);
    }
}

bool pilha_vazia(Pilha *p) {
    return p->topo == -1;
}

void empilhar(Pilha *p, int v) {
    if (p->topo < p->capacidade - 1) {
        p->dados[++(p->topo)] = v;
    }
}

int desempilhar(Pilha *p) {
    if (pilha_vazia(p)) return -1;
    return p->dados[(p->topo)--];
}

// --- DFS Entrada (d) e Saída (f) ---
void dfs_recursiva(GrafoLista *g, int u, int *visitado, int *d, int *f, int *tempo) {
    visitado[u] = 1;
    (*tempo)++;
    if (d) d[u] = *tempo;

    No *vert = g->adj[u];
    while (vert != NULL) {
        int v = vert->vertice;
        if (!visitado[v]) {
            dfs_recursiva(g, v, visitado, d, f, tempo);
        }
        vert = vert->prox;
    }

    (*tempo)++;
    if (f) f[u] = *tempo;
}

int contar_componentes(GrafoLista *g) {
    int *visitado = (int*) calloc(g->num_vertices, sizeof(int));
    int componentes = 0;
    int tempo = 0;

    for (int i = 0; i < g->num_vertices; i++) {
        if (!visitado[i]) {
            componentes++;
            dfs_recursiva(g, i, visitado, NULL, NULL, &tempo);
        }
    }

    free(visitado);
    return componentes;
}

static bool dfs_ciclo_helper(GrafoLista *g, int u, int pai, bool *visitado) {
    visitado[u] = true;

    No *vert = g->adj[u];
    while (vert != NULL) {
        int v = vert->vertice;
        if (!visitado[v]) {
            if (dfs_ciclo_helper(g, v, u, visitado))
                return true;
        } else if (v != pai) {
            return true;
        }
        vert = vert->prox;
    }
    return false;
}

bool tem_ciclo(GrafoLista *g) {
    bool *visitado = (bool*) calloc(g->num_vertices, sizeof(bool));

    for (int i = 0; i < g->num_vertices; i++) {
        if (!visitado[i]) {
            if (dfs_ciclo_helper(g, i, -1, visitado)) {
                free(visitado);
                return true;
            }
        }
    }

    free(visitado);
    return false;
}