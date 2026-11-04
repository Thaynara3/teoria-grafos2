#include "hamiltoniano.h"

bool eh_caminho_hamiltoniano(int grafo[MAX_V][MAX_V], int caminho[], int n) {
    bool visitado[MAX_V] = {false};

    for (int i = 0; i < n; i++) {
        int v = caminho[i];
        if (v < 0 || v >= n || visitado[v]) return false;
        visitado[v] = true;
    }

    for (int i = 0; i < n - 1; i++) {
        int u = caminho[i];
        int v = caminho[i + 1];
        if (grafo[u][v] == 0) return false;
    }

    return true;
}

bool encontrar_caminho_hamiltoniano_bt(int grafo[MAX_V][MAX_V], int n, int pos, int caminho[], bool visitado[]) {
    if (pos == n) {
        return eh_caminho_hamiltoniano(grafo, caminho, n);
    }

    for (int v = 0; v < n; v++) {
        if (!visitado[v]) {
            if (pos > 0 && grafo[caminho[pos - 1]][v] == 0) continue;

            caminho[pos] = v;
            visitado[v] = true;

            if (encontrar_caminho_hamiltoniano_bt(grafo, n, pos + 1, caminho, visitado)) {
                return true;
            }

            visitado[v] = false;
        }
    }

    return false;
}