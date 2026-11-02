#include "cobertura.h"

GrafoLista* criar_grafo(int num_vertices) {
    GrafoLista* g = (GrafoLista*)malloc(sizeof(GrafoLista));
    g->num_vertices = num_vertices;
    for (int i = 0; i < num_vertices; i++) {
        g->lista[i] = NULL;
    }
    return g;
}

void adicionar_aresta(GrafoLista* g, int u, int v) {
    No* novo1 = (No*)malloc(sizeof(No));
    novo1->vertice = v;
    novo1->proximo = g->lista[u];
    g->lista[u] = novo1;

    No* novo2 = (No*)malloc(sizeof(No));
    novo2->vertice = u;
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

bool eh_cobertura(GrafoLista *g, bool no_conjunto[]) {
    for (int u = 0; u < g->num_vertices; u++) {
        No* curr = g->lista[u];
        while (curr) {
            int v = curr->vertice;
            if (u < v && !no_conjunto[u] && !no_conjunto[v]) {
                return false;
            }
            curr = curr->proximo;
        }
    }
    return true;
}

void cobertura_minima_bt(GrafoLista *g, int idx, bool atual[], int tam_atual, bool melhor[], int *melhor_tam) {
    if (tam_atual >= *melhor_tam) return;

    if (idx == g->num_vertices) {
        if (eh_cobertura(g, atual)) {
            *melhor_tam = tam_atual;
            for (int i = 0; i < g->num_vertices; i++) melhor[i] = atual[i];
        }
        return;
    }

    atual[idx] = true;
    cobertura_minima_bt(g, idx + 1, atual, tam_atual + 1, melhor, melhor_tam);

    atual[idx] = false;
    cobertura_minima_bt(g, idx + 1, atual, tam_atual, melhor, melhor_tam);
}

int cobertura_gulosa(GrafoLista *g, bool resultado[]) {
    int n = g->num_vertices;
    for (int i = 0; i < n; i++) resultado[i] = false;

    int tam_cobertura = 0;

    while (!eh_cobertura(g, resultado)) {
        int max_grau = -1, melhor_v = -1;

        for (int i = 0; i < n; i++) {
            if (!resultado[i]) {
                int grau_atual = 0;
                No* curr = g->lista[i];
                while (curr) {
                    if (!resultado[curr->vertice]) grau_atual++;
                    curr = curr->proximo;
                }
                if (grau_atual > max_grau) {
                    max_grau = grau_atual;
                    melhor_v = i;
                }
            }
        }

        if (melhor_v == -1 || max_grau == 0) break;
        resultado[melhor_v] = true;
        tam_cobertura++;
    }

    return tam_cobertura;
}