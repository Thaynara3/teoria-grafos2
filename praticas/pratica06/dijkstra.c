#include "dijkstra.h"

GrafoListaPonderado* criar_grafo(int num_vertices) {
    GrafoListaPonderado *g = (GrafoListaPonderado*) malloc(sizeof(GrafoListaPonderado));
    g->num_vertices = num_vertices;
    g->listas = (Aresta**) malloc(num_vertices * sizeof(Aresta*));
    for (int i = 0; i < num_vertices; i++) {
        g->listas[i] = NULL;
    }
    return g;
}

void adicionar_aresta(GrafoListaPonderado *g, int u, int v, int peso) {
    Aresta *nova1 = (Aresta*) malloc(sizeof(Aresta));
    nova1->destino = v;
    nova1->peso = peso;
    nova1->prox = g->listas[u];
    g->listas[u] = nova1;

    Aresta *nova2 = (Aresta*) malloc(sizeof(Aresta));
    nova2->destino = u;
    nova2->peso = peso;
    nova2->prox = g->listas[v];
    g->listas[v] = nova2;
}

void liberar_grafo(GrafoListaPonderado *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        Aresta *atual = g->listas[i];
        while (atual != NULL) {
            Aresta *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->listas);
    free(g);
}

static int vertice_menor_distancia(int *dist, bool *visitado, int V) {
    int min = INF;
    int min_index = -1;

    for (int v = 0; v < V; v++) {
        if (!visitado[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred) {
    int V = g->num_vertices;
    bool *visitado = (bool*) malloc(V * sizeof(bool));

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        pred[i] = -1;
        visitado[i] = false;
    }

    dist[origem] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = vertice_menor_distancia(dist, visitado, V);

        if (u == -1 || dist[u] == INF) break;

        visitado[u] = true;

        Aresta *aresta = g->listas[u];
        while (aresta != NULL) {
            int v = aresta->destino;
            int peso = aresta->peso;

            if (!visitado[v] && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                pred[v] = u;
            }
            aresta = aresta->prox;
        }
    }

    free(visitado);
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