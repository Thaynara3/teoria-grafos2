#include "planaridade.h"

int contar_arestas(GrafoLista* g) {
    int total = 0;
    for (int i = 0; i < g->num_vertices; i++) {
        No* curr = g->lista[i];
        while (curr) {
            if (i < curr->destino) { 
                total++;
            }
            curr = curr->prox;
        }
    }
    return total;
}

bool eh_planar_euler(GrafoLista* g) {
    int n = g->num_vertices;
    int m = contar_arestas(g);

    if (n <= 2) return true;
    
    if (m > 3 * n - 6) {
        return false;
    }
    return true;
}

static bool tem_aresta(GrafoLista* g, int u, int v) {
    No* curr = g->lista[u];
    while (curr) {
        if (curr->destino == v) return true;
        curr = curr->prox;
    }
    return false;
}

bool eh_planar_kuratowski(GrafoLista* g) {
    int n = g->num_vertices;

    if (!eh_planar_euler(g)) return false;
    if (n < 5) return true;

    for (int v1 = 0; v1 < n - 4; v1++) {
        for (int v2 = v1 + 1; v2 < n - 3; v2++) {
            for (int v3 = v2 + 1; v3 < n - 2; v3++) {
                for (int v4 = v3 + 1; v4 < n - 1; v4++) {
                    for (int v5 = v4 + 1; v5 < n; v5++) {
                        int v[5] = {v1, v2, v3, v4, v5};
                        bool eh_k5 = true;
                        for (int i = 0; i < 5 && eh_k5; i++) {
                            for (int j = i + 1; j < 5; j++) {
                                if (!tem_aresta(g, v[i], v[j])) {
                                    eh_k5 = false;
                                    break;
                                }
                            }
                        }
                        if (eh_k5) return false;
                    }
                }
            }
        }
    }

    if (n >= 6) {
        for (int a1 = 0; a1 < n; a1++) {
            for (int a2 = a1 + 1; a2 < n; a2++) {
                for (int a3 = a2 + 1; a3 < n; a3++) {
                    for (int b1 = 0; b1 < n; b1++) {
                        if (b1 == a1 || b1 == a2 || b1 == a3) continue;
                        for (int b2 = b1 + 1; b2 < n; b2++) {
                            if (b2 == a1 || b2 == a2 || b2 == a3) continue;
                            for (int b3 = b2 + 1; b3 < n; b3++) {
                                if (b3 == a1 || b3 == a2 || b3 == a3) continue;

                                bool eh_k33 = true;
                                int setA[3] = {a1, a2, a3};
                                int setB[3] = {b1, b2, b3};

                                for (int i = 0; i < 3 && eh_k33; i++) {
                                    for (int j = 0; j < 3; j++) {
                                        if (!tem_aresta(g, setA[i], setB[j])) {
                                            eh_k33 = false;
                                            break;
                                        }
                                    }
                                }
                                if (eh_k33) return false; 
                            }
                        }
                    }
                }
            }
        }
    }

    return true;
}