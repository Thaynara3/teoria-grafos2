#include "conectividade.h"

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
    novo1->destino = v;
    novo1->prox = g->lista[u];
    g->lista[u] = novo1;

    No* novo2 = (No*)malloc(sizeof(No));
    novo2->destino = u;
    novo2->prox = g->lista[v];
    g->lista[v] = novo2;
}

void liberar_grafo(GrafoLista* g) {
    if (!g) return;
    for (int i = 0; i < g->num_vertices; i++) {
        No* atual = g->lista[i];
        while (atual) {
            No* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g);
}

void dfs_articulacoes(GrafoLista* g, int u, bool visitado[], int descoberta[], int low[], int pai[], bool articulacao[], int* tempo) {
    int filhos = 0;
    visitado[u] = true;
    descoberta[u] = low[u] = ++(*tempo);

    No* curr = g->lista[u];
    while (curr != NULL) {
        int v = curr->destino;

        if (!visitado[v]) {
            filhos++;
            pai[v] = u;

            dfs_articulacoes(g, v, visitado, descoberta, low, pai, articulacao, tempo);

            if (low[v] < low[u]) {
                low[u] = low[v];
            }

            if (pai[u] == -1 && filhos > 1) {
                articulacao[u] = true;
            }

            if (pai[u] != -1 && low[v] >= descoberta[u]) {
                articulacao[u] = true;
            }

            if (low[v] > descoberta[u]) {
                printf("[Ponte Detectada] Aresta: (%d, %d)\n", u, v);
            }
        } 
        else if (v != pai[u]) {
            if (descoberta[v] < low[u]) {
                low[u] = descoberta[v];
            }
        }
        curr = curr->prox;
    }
}

void detectar_articulacoes_e_pontes(GrafoLista* g) {
    bool visitado[MAX_VERTICES] = {false};
    int descoberta[MAX_VERTICES] = {0};
    int low[MAX_VERTICES] = {0};
    int pai[MAX_VERTICES];
    bool articulacao[MAX_VERTICES] = {false};
    int tempo = 0;

    for (int i = 0; i < g->num_vertices; i++) {
        pai[i] = -1;
    }

    printf("--- Buscando Pontes ---\n");
    for (int i = 0; i < g->num_vertices; i++) {
        if (!visitado[i]) {
            dfs_articulacoes(g, i, visitado, descoberta, low, pai, articulacao, &tempo);
        }
    }

    printf("\n--- Vertices de Corte (Articulacoes) ---\n");
    bool encontrou = false;
    for (int i = 0; i < g->num_vertices; i++) {
        if (articulacao[i]) {
            printf("Vertice de corte: %d\n", i);
            encontrou = true;
        }
    }
    if (!encontrou) {
        printf("Nenhum vertice de corte encontrado.\n");
    }
}