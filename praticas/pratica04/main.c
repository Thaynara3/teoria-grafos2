#include <stdio.h>
#include "conectividade.h"
#include "planaridade.h"

int main() {
    printf("=== PRATICA 04: CONECTIVIDADE E PLANARIDADE ===\n\n");

    printf("--- Testando Grafo 1 (Conectividade) ---\n");
    GrafoLista* g1 = criar_grafo(5);
    adicionar_aresta(g1, 0, 1);
    adicionar_aresta(g1, 1, 2);
    adicionar_aresta(g1, 2, 3);
    adicionar_aresta(g1, 3, 4);

    detectar_articulacoes_e_pontes(g1);

    printf("\nPlanaridade (Euler): %s\n", eh_planar_euler(g1) ? "SIM" : "NAO");
    printf("Planaridade (Kuratowski): %s\n\n", eh_planar_kuratowski(g1) ? "SIM" : "NAO");

    printf("--- Testando Grafo 2 (K5 - Grafo Completo de 5 Vertices) ---\n");
    GrafoLista* g2 = criar_grafo(5);
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            adicionar_aresta(g2, i, j);
        }
    }

    detectar_articulacoes_e_pontes(g2);

    printf("\nPlanaridade (Euler): %s\n", eh_planar_euler(g2) ? "SIM" : "NAO");
    printf("Planaridade (Kuratowski): %s\n", eh_planar_kuratowski(g2) ? "SIM" : "NAO");

    liberar_grafo(g1);
    liberar_grafo(g2);

    return 0;
}