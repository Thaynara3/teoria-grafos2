#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "cobertura.h"

void montar_grafo_slide(GrafoLista* g) {
    adicionar_aresta(g, 0, 1); 
    adicionar_aresta(g, 0, 2); 
    adicionar_aresta(g, 1, 2); 
    adicionar_aresta(g, 1, 3); 
    adicionar_aresta(g, 1, 4); 
    adicionar_aresta(g, 2, 3); 
    adicionar_aresta(g, 2, 4); 
    adicionar_aresta(g, 3, 4); 
    adicionar_aresta(g, 3, 5); 
    adicionar_aresta(g, 4, 5); 
}

int main() {
    printf("=== PRATICA 09: COBERTURA DE VERTICES ===\n\n");

    int n = 6; 
    GrafoLista* g = criar_grafo(n);
    montar_grafo_slide(g);

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

    printf("Tamanho Cobertura Minima (BT): %d\n", melhor_tam_bt);
    printf("Tamanho Cobertura (Gulosa): %d\n", tam_guloso);

    liberar_grafo(g);
    return 0;
}