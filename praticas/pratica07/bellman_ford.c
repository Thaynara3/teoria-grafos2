#include "bellman_ford.h"

GrafoListaPonderado* criar_grafo(int num_vertices) {
    GrafoListaPonderado* g = (GrafoListaPonderado*)malloc(sizeof(GrafoListaPonderado));
    g->num_vertices = num_vertices;
    for (int i = 0; i < num_vertices; i++) {
        g->lista[i] = NULL;
    }
    return g;
}

void adicionar_aresta(GrafoListaPonderado* g, int u, int v, int peso) {
    Aresta* nova = (Aresta*)malloc(sizeof(Aresta));
    nova->destino = v;
    nova->peso = peso;
    nova->prox = g->lista[u];
    g->lista[u] = nova;
}

void liberar_grafo(GrafoListaPonderado* g) {
    if (!g) return;
    for (int i = 0; i < g->num_vertices; i++) {
        Aresta* atual = g->lista[i];
        while (atual) {
            Aresta* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g);
}

void reconstruir_ciclo_negativo(GrafoListaPonderado *g, int vertice_no_ciclo, int *pred) {
    int n = g->num_vertices;
    int v = vertice_no_ciclo;

    for (int i = 0; i < n; i++) {
        v = pred[v];
    }

    int ciclo[MAX_VERTICES + 1];
    int tam = 0;
    int curr = v;

    do {
        ciclo[tam++] = curr;
        curr = pred[curr];
    } while (curr != v && tam < n);
    ciclo[tam++] = v;

    printf("Ciclo Negativo Detectado: ");
    for (int i = tam - 1; i >= 0; i--) {
        printf("%c", 'A' + ciclo[i]);
        if (i > 0) printf(" -> ");
    }
    printf("\n");
}

int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred) {
    int n = g->num_vertices;

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        pred[i] = -1;
    }
    dist[origem] = 0;

    for (int i = 1; i <= n - 1; i++) {
        for (int u = 0; u < n; u++) {
            if (dist[u] == INF) continue;

            Aresta* curr = g->lista[u];
            while (curr != NULL) {
                int v = curr->destino;
                int peso = curr->peso;

                if (dist[u] + peso < dist[v]) {
                    dist[v] = dist[u] + peso;
                    pred[v] = u;
                }
                curr = curr->prox;
            }
        }
    }

    for (int u = 0; u < n; u++) {
        if (dist[u] == INF) continue;

        Aresta* curr = g->lista[u];
        while (curr != NULL) {
            int v = curr->destino;
            int peso = curr->peso;

            if (dist[u] + peso < dist[v]) {
                pred[v] = u;
                reconstruir_ciclo_negativo(g, v, pred);
                return 0; 
            }
            curr = curr->prox;
        }
    }

    return 1;
}

void reconstruir_caminho(int origem, int destino, int *pred) {
    if (origem == destino) {
        printf("%c", 'A' + origem);
        return;
    }
    if (pred[destino] == -1) {
        printf("Sem caminho");
        return;
    }
    reconstruir_caminho(origem, pred[destino], pred);
    printf(" -> %c", 'A' + destino);
}