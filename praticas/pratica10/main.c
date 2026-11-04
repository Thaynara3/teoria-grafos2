#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "hamiltoniano.h"
#include "tps.h"

void gerar_grafo_completo_ponderado(int grafo[MAX_V][MAX_V], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                grafo[i][j] = 0;
            } else {
                grafo[i][j] = 1 + rand() % 50;
            }
        }
    }
}

int main() {
    srand(42);

    printf("=== PRATICA 10: CAMINHO HAMILTONIANO E TSP ===\n\n");

    int tamanhos[] = {5, 8, 10, 12};
    int qtd_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    printf("%-3s | %-12s | %-12s | %-12s | %-10s | %-10s | %-10s\n", "N", "Custo FB", "Custo VMP", "Custo Ins", "T.FB (ms)", "T.VMP(ms)", "T.Ins(ms)");
    printf("------------------------------------------------------------------------------------------\n");

    for (int k = 0; k < qtd_tamanhos; k++) {
        int n = tamanhos[k];
        int g[MAX_V][MAX_V];
        gerar_grafo_completo_ponderado(g, n);

        int rota_fb[MAX_V], rota_vmp[MAX_V], rota_ins[MAX_V];

        clock_t i_fb = clock();
        int c_fb = tsp_forca_bruta(g, n, rota_fb);
        clock_t f_fb = clock();
        double t_fb = ((double)(f_fb - i_fb) / CLOCKS_PER_SEC) * 1000.0;

        clock_t i_vmp = clock();
        int c_vmp = tsp_vizinho_mais_proximo(g, n, rota_vmp);
        clock_t f_vmp = clock();
        double t_vmp = ((double)(f_vmp - i_vmp) / CLOCKS_PER_SEC) * 1000.0;

        clock_t i_ins = clock();
        int c_ins = tsp_insercao(g, n, rota_ins);
        clock_t f_ins = clock();
        double t_ins = ((double)(f_ins - i_ins) / CLOCKS_PER_SEC) * 1000.0;

        printf("%-3d | %-12d | %-12d | %-12d | %-10.4f | %-10.4f | %-10.4f\n", n, c_fb, c_vmp, c_ins, t_fb, t_vmp, t_ins);
    }

    return 0;
}