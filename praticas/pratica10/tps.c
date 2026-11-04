#include "tps.h"

static void tsp_bt_aux(int grafo[MAX_V][MAX_V], int n, int pos, int custo_atual, int origem, int rota_atual[], bool usado[], int *melhor_custo, int melhor_rota[]) {
    if (pos == n) {
        int v_final = rota_atual[pos - 1];
        if (grafo[v_final][origem] > 0 && grafo[v_final][origem] < INF) {
            int custo_total = custo_atual + grafo[v_final][origem];
            if (custo_total < *melhor_custo) {
                *melhor_custo = custo_total;
                for (int i = 0; i < n; i++) melhor_rota[i] = rota_atual[i];
            }
        }
        return;
    }

    for (int v = 0; v < n; v++) {
        if (!usado[v]) {
            int u = rota_atual[pos - 1];
            if (grafo[u][v] > 0 && grafo[u][v] < INF) {
                if (custo_atual + grafo[u][v] < *melhor_custo) {
                    usado[v] = true;
                    rota_atual[pos] = v;
                    tsp_bt_aux(grafo, n, pos + 1, custo_atual + grafo[u][v], origem, rota_atual, usado, melhor_custo, melhor_rota);
                    usado[v] = false;
                }
            }
        }
    }
}

int tsp_forca_bruta(int grafo[MAX_V][MAX_V], int n, int melhor_rota[]) {
    int melhor_custo = INF;
    int rota_atual[MAX_V];
    bool usado[MAX_V] = {false};

    rota_atual[0] = 0;
    usado[0] = true;

    tsp_bt_aux(grafo, n, 1, 0, 0, rota_atual, usado, &melhor_custo, melhor_rota);
    return melhor_custo;
}

int tsp_vizinho_mais_proximo(int grafo[MAX_V][MAX_V], int n, int rota[]) {
    bool visitado[MAX_V] = {false};
    rota[0] = 0;
    visitado[0] = true;
    int custo_total = 0;

    for (int i = 0; i < n - 1; i++) {
        int u = rota[i];
        int prox_v = -1;
        int menor_peso = INF;

        for (int v = 0; v < n; v++) {
            if (!visitado[v] && grafo[u][v] < menor_peso) {
                menor_peso = grafo[u][v];
                prox_v = v;
            }
        }

        if (prox_v == -1) return INF;

        rota[i + 1] = prox_v;
        visitado[prox_v] = true;
        custo_total += menor_peso;
    }

    custo_total += grafo[rota[n - 1]][rota[0]];
    return custo_total;
}

int tsp_insercao(int grafo[MAX_V][MAX_V], int n, int rota[]) {
    bool em_subcircuito[MAX_V] = {false};
    int tam = 0;

    rota[0] = 0;
    em_subcircuito[0] = true;
    tam = 1;

    int menor_dist = INF, segundo_v = -1;
    for (int v = 1; v < n; v++) {
        if (grafo[0][v] < menor_dist) {
            menor_dist = grafo[0][v];
            segundo_v = v;
        }
    }

    if (segundo_v != -1) {
        rota[1] = segundo_v;
        em_subcircuito[segundo_v] = true;
        tam = 2;
    }

    while (tam < n) {
        int k_escolhido = -1;
        int dist_min = INF;

        for (int k = 0; k < n; k++) {
            if (!em_subcircuito[k]) {
                for (int i = 0; i < tam; i++) {
                    if (grafo[rota[i]][k] < dist_min) {
                        dist_min = grafo[rota[i]][k];
                        k_escolhido = k;
                    }
                }
            }
        }

        if (k_escolhido == -1) break;

        int melhor_pos = -1;
        int menor_aumento = INF;

        for (int i = 0; i < tam; i++) {
            int u = rota[i];
            int v = rota[(i + 1) % tam];
            int aumento = grafo[u][k_escolhido] + grafo[k_escolhido][v] - grafo[u][v];

            if (aumento < menor_aumento) {
                menor_aumento = aumento;
                melhor_pos = i + 1;
            }
        }

        for (int j = tam; j > melhor_pos; j--) {
            rota[j] = rota[j - 1];
        }

        rota[melhor_pos] = k_escolhido;
        em_subcircuito[k_escolhido] = true;
        tam++;
    }

    int custo_total = 0;
    for (int i = 0; i < n; i++) {
        custo_total += grafo[rota[i]][rota[(i + 1) % n]];
    }

    return custo_total;
}

void grafo_para_tsp(int grafo_origem[MAX_V][MAX_V], int n, int grafo_tsp[MAX_V][MAX_V]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                grafo_tsp[i][j] = 0;
            } else if (grafo_origem[i][j] != 0) {
                grafo_tsp[i][j] = 1;
            } else {
                grafo_tsp[i][j] = 2;
            }
        }
    }
}