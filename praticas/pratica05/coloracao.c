#include "coloracao.h"

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

int* coloracao_gulosa(GrafoLista *g, int *num_cores) {
    int n = g->num_vertices;
    int* resultado = (int*)malloc(n * sizeof(int));
    bool* cores_indisponiveis = (bool*)malloc(n * sizeof(bool));

    for (int i = 0; i < n; i++) {
        resultado[i] = -1; 
    }

 
    resultado[0] = 0;
    int max_cor = 0;

    for (int u = 1; u < n; u++) {

        for (int c = 0; c < n; c++) {
            cores_indisponiveis[c] = false;
        }

        No* curr = g->lista[u];
        while (curr) {
            int vizinho = curr->destino;
            if (resultado[vizinho] != -1) {
                cores_indisponiveis[resultado[vizinho]] = true;
            }
            curr = curr->prox;
        }

        int cr;
        for (cr = 0; cr < n; cr++) {
            if (!cores_indisponiveis[cr]) break;
        }

        resultado[u] = cr;
        if (cr > max_cor) max_cor = cr;
    }

    *num_cores = max_cor + 1;
    free(cores_indisponiveis);
    return resultado;
}

typedef struct {
    int id;
    int grau;
} VerticeGrau;

static int comparar_graus(const void* a, const void* b) {
    VerticeGrau* v1 = (VerticeGrau*)a;
    VerticeGrau* v2 = (VerticeGrau*)b;
    return v2->grau - v1->grau; 
}

int* coloracao_welsh_powell(GrafoLista *g, int *num_cores) {
    int n = g->num_vertices;
    VerticeGrau* vg = (VerticeGrau*)malloc(n * sizeof(VerticeGrau));

    for (int i = 0; i < n; i++) {
        vg[i].id = i;
        vg[i].grau = 0;
        No* curr = g->lista[i];
        while (curr) {
            vg[i].grau++;
            curr = curr->prox;
        }
    }

    qsort(vg, n, sizeof(VerticeGrau), comparar_graus);

    int* resultado = (int*)malloc(n * sizeof(int));
    bool* cores_indisponiveis = (bool*)malloc(n * sizeof(bool));

    for (int i = 0; i < n; i++) {
        resultado[i] = -1;
    }

    int max_cor = 0;

    for (int i = 0; i < n; i++) {
        int u = vg[i].id;

        for (int c = 0; c < n; c++) {
            cores_indisponiveis[c] = false;
        }

        No* curr = g->lista[u];
        while (curr) {
            int vizinho = curr->destino;
            if (resultado[vizinho] != -1) {
                cores_indisponiveis[resultado[vizinho]] = true;
            }
            curr = curr->prox;
        }

        int cr;
        for (cr = 0; cr < n; cr++) {
            if (!cores_indisponiveis[cr]) break;
        }

        resultado[u] = cr;
        if (cr > max_cor) max_cor = cr;
    }

    *num_cores = max_cor + 1;
    free(vg);
    free(cores_indisponiveis);
    return resultado;
}

bool eh_bipartido(GrafoLista *g) {
    int n = g->num_vertices;
    int cor[MAX_VERTICES];
    for (int i = 0; i < n; i++) cor[i] = -1; 

    int fila[MAX_VERTICES];

    for (int i = 0; i < n; i++) {
        if (cor[i] == -1) {
            cor[i] = 1;
            int inicio = 0, fim = 0;
            fila[fim++] = i;

            while (inicio < fim) {
                int u = fila[inicio++];

                No* curr = g->lista[u];
                while (curr) {
                    int v = curr->destino;

                    if (cor[v] == -1) {
                        cor[v] = 1 - cor[u];
                        fila[fim++] = v;
                    } else if (cor[v] == cor[u]) {
                        return false;
                    }
                    curr = curr->prox;
                }
            }
        }
    }
    return true;
}