#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "cobertura.h"

void gerar_grafo_aleatorio(GrafoLista* g, double probabilidade) {
    int n = g->num_vertices;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((double)rand() / RAND_MAX < probabilidade) {
                adicionar_aresta(g, i, j);
            }
        }
    }
}

int main() {
    srand(42);

    printf("=== PRATICA 09: COBERTURA DE VERTICES ===\n\n");

    int tamanhos[] = {5, 8, 10, 12, 15};
    int qtd_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    printf("%-5s | %-15s | %-15s | %-12s | %-12s\n", "N", "Tam (BT)", "Tam (Guloso)", "Tempo BT (ms)", "Tempo Gul (ms)");
    printf("--------------------------------------------------------------------------------\n");

    for (int k = 0; k < qtd_tamanhos; k++) {
        int n = tamanhos[k];
        GrafoLista* g = criar_grafo(n);
        gerar_grafo_aleatorio(g, 0.4);

        bool atual[MAX_VERTICES] = {false};
        bool melhor_bt[MAX_VERTICES] = {false};
        int melhor_tam_bt = n + 1;

        clock_t inicio_bt = clock();
        cobertura_minima_bt(g, 0, atual, 0, melhor_bt, &melhor_tam_bt);
        clock_t fim_bt = clock();
        double tempo_bt = ((double)(fim_bt - inicio_bt) / CLOCKS_PER_SEC) * 1000.0;

        bool resultado_guloso[MAX_VERTICES] = {false};
        clock_t inicio_gul = clock();
        int tam_guloso = cobertura_gulosa(g, resultado_guloso);
        clock_t fim_gul = clock();
        double tempo_gul = ((double)(fim_gul - inicio_gul) / CLOCKS_PER_SEC) * 1000.0;

        printf("%-5d | %-15d | %-15d | %-12.4f | %-12.4f\n", n, melhor_tam_bt, tam_guloso, tempo_bt, tempo_gul);

        liberar_grafo(g);
    }

    return 0;
}