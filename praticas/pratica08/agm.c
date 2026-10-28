#include "agm.h"
#include <stdio.h>
#include <limits.h>

GrafoLista* criar_grafo(int num_vertices) {
    GrafoLista* g = (GrafoLista*)malloc(sizeof(GrafoLista));
    g->num_vertices = num_vertices;
    for (int i = 0; i < num_vertices; i++) {
        g->lista[i] = NULL;
    }
    return g;
}

void adicionar_aresta(GrafoLista* g, int u, int v, int peso) {
    No* novo1 = (No*)malloc(sizeof(No));
    novo1->vertice = v;
    novo1->peso = peso;
    novo1->proximo = g->lista[u];
    g->lista[u] = novo1;

    No* novo2 = (No*)malloc(sizeof(No));
    novo2->vertice = u;
    novo2->peso = peso;
    novo2->proximo = g->lista[v];
    g->lista[v] = novo2;
}

void liberar_grafo(GrafoLista* g) {
    if (!g) return;
    for (int i = 0; i < g->num_vertices; i++) {
        No* atual = g->lista[i];
        while (atual) {
            No* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(g);
}

void inicializar_union_find(UnionFind *uf, int n) {
    for (int i = 0; i < n; i++) {
        uf->pai[i] = i;
        uf->nivel[i] = 0;
    }
}

int encontrar(UnionFind *uf, int x) {
    if (uf->pai[x] != x) {
        uf->pai[x] = encontrar(uf, uf->pai[x]);
    }
    return uf->pai[x];
}

int unir(UnionFind *uf, int a, int b) {
    int raiz_a = encontrar(uf, a);
    int raiz_b = encontrar(uf, b);

    if (raiz_a == raiz_b) return 0;

    if (uf->nivel[raiz_a] < uf->nivel[raiz_b]) {
        uf->pai[raiz_a] = raiz_b;
    } else if (uf->nivel[raiz_a] > uf->nivel[raiz_b]) {
        uf->pai[raiz_b] = raiz_a;
    } else {
        uf->pai[raiz_b] = raiz_a;
        uf->nivel[raiz_a]++;
    }
    return 1;
}

static int comparar(const void *a, const void *b) {
    Aresta *x = (Aresta *)a;
    Aresta *y = (Aresta *)b;
    return x->peso - y->peso;
}

int kruskal(GrafoLista *g, Aresta *resultado_mst) {
    int n = g->num_vertices;
    Aresta arestas[MAX_ARESTAS];
    int m = 0;

    for (int u = 0; u < n; u++) {
        No* curr = g->lista[u];
        while (curr) {
            if (u < curr->vertice) {
                arestas[m].origem = u;
                arestas[m].destino = curr->vertice;
                arestas[m].peso = curr->peso;
                m++;
            }
            curr = curr->proximo;
        }
    }

    UnionFind uf;
    inicializar_union_find(&uf, n);

    qsort(arestas, m, sizeof(Aresta), comparar);

    int qtd_agm = 0;
    int custo_total = 0;

    for (int i = 0; i < m && qtd_agm < n - 1; i++) {
        int u = arestas[i].origem;
        int v = arestas[i].destino;

        if (unir(&uf, u, v)) {
            resultado_mst[qtd_agm++] = arestas[i];
            custo_total += arestas[i].peso;
        }
    }

    return custo_total;
}

int prim(GrafoLista *g, int origem, int *pai) {
    int chave[MAX_VERTICES];
    int naAGM[MAX_VERTICES];

    for (int i = 0; i < g->num_vertices; i++) {
        chave[i] = INT_MAX;
        pai[i] = -1;
        naAGM[i] = 0;
    }

    chave[origem] = 0;

    for (int i = 0; i < g->num_vertices; i++) {
        int menor = INT_MAX;
        int u = -1;

        for (int j = 0; j < g->num_vertices; j++) {
            if (!naAGM[j] && chave[j] < menor) {
                menor = chave[j];
                u = j;
            }
        }

        if (u == -1) break;

        naAGM[u] = 1;

        No *no = g->lista[u];
        while (no != NULL) {
            int v = no->vertice;
            int peso = no->peso;

            if (!naAGM[v] && peso < chave[v]) {
                chave[v] = peso;
                pai[v] = u;
            }
            no = no->proximo;
        }
    }

    int custo_total = 0;
    for (int i = 0; i < g->num_vertices; i++) {
        if (chave[i] != INT_MAX) {
            custo_total += chave[i];
        }
    }

    return custo_total;
}