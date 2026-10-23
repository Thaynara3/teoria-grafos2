#include <stdio.h>
#include <stdlib.h>
#include "coloracao.h"

void imprimir_coloracao(const char* nome_algoritmo, int* cores, int num_vertices, int num_cores) {
    printf("=== %s ===\n", nome_algoritmo);
    printf("Numero de cores utilizadas: %d\n", num_cores);
    for (int i = 0; i < num_vertices; i++) {
        printf("Vertice %d -> Cor %d\n", i, cores[i]);
    }
    printf("\n");
}

int main() {
    printf("=== PRATICA 05: COLORACAO DE GRAFOS ===\n\n");

    printf("--- Teste 1: Grafo Bipartido (C4) ---\n");
    GrafoLista* g1 = criar_grafo(4);
    adicionar_aresta(g1, 0, 1);
    adicionar_aresta(g1, 1, 2);
    adicionar_aresta(g1, 2, 3);
    adicionar_aresta(g1, 3, 0);

    printf("E Bipartido? %s\n\n", eh_bipartido(g1) ? "SIM (2-colorivel)" : "NAO");

    int cores_g1_guloso, cores_g1_wp;
    int* c1_guloso = coloracao_gulosa(g1, &cores_g1_guloso);
    int* c1_wp = coloracao_welsh_powell(g1, &cores_g1_wp);

    imprimir_coloracao("Guloso Simples", c1_guloso, 4, cores_g1_guloso);
    imprimir_coloracao("Welsh-Powell", c1_wp, 4, cores_g1_wp);

    printf("--- Teste 2: Grafo Nao Bipartido ---\n");
    GrafoLista* g2 = criar_grafo(4);
    adicionar_aresta(g2, 0, 1);
    adicionar_aresta(g2, 1, 2);
    adicionar_aresta(g2, 2, 0); 
    adicionar_aresta(g2, 2, 3);

    printf("E Bipartido? %s\n\n", eh_bipartido(g2) ? "SIM (2-colorivel)" : "NAO");

    int cores_g2_guloso, cores_g2_wp;
    int* c2_guloso = coloracao_gulosa(g2, &cores_g2_guloso);
    int* c2_wp = coloracao_welsh_powell(g2, &cores_g2_wp);

    imprimir_coloracao("Guloso Simples", c2_guloso, 4, cores_g2_guloso);
    imprimir_coloracao("Welsh-Powell", c2_wp, 4, cores_g2_wp);

    free(c1_guloso);
    free(c1_wp);
    free(c2_guloso);
    free(c2_wp);
    liberar_grafo(g1);
    liberar_grafo(g2);

    return 0;
}