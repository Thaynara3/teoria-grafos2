#include <stdio.h>
#include <stdlib.h>
#include "bellman_ford.h"

int main() {
    printf("=== PRATICA 07: ALGORITMO DE BELLMAN-FORD ===\n\n");

    printf("--- Teste 1: Grafo sem ciclo negativo ---\n");
    int num_vertices1 = 5; 
    GrafoListaPonderado* g1 = criar_grafo(num_vertices1);

    adicionar_aresta(g1, 0, 1, 6);  
    adicionar_aresta(g1, 0, 2, 7);  
    adicionar_aresta(g1, 1, 2, 8);  
    adicionar_aresta(g1, 1, 3, 5);  
    adicionar_aresta(g1, 1, 4, -4); 
    adicionar_aresta(g1, 2, 3, -3); 
    adicionar_aresta(g1, 2, 4, 9);  
    adicionar_aresta(g1, 3, 1, -2); 
    adicionar_aresta(g1, 4, 3, 7);  

    int dist1[5], pred1[5];
    if (bellman_ford(g1, 0, dist1, pred1)) {
        printf("Caminhos minimos a partir de A:\n");
        for (int i = 0; i < num_vertices1; i++) {
            printf("d(%c) = %d => ", 'A' + i, dist1[i]);
            reconstruir_caminho(0, i, pred1);
            printf("\n");
        }
    }

    printf("\n--- Teste 2: Grafo com ciclo negativo ---\n");
    int num_vertices2 = 4; 
    GrafoListaPonderado* g2 = criar_grafo(num_vertices2);

    adicionar_aresta(g2, 0, 1, 1);  
    adicionar_aresta(g2, 1, 2, 2);  
    adicionar_aresta(g2, 2, 3, -5); 
    adicionar_aresta(g2, 3, 1, 1);  

    int dist2[4], pred2[4];
    if (!bellman_ford(g2, 0, dist2, pred2)) {
        printf("Sucesso na deteccao do ciclo negativo!\n");
    }

    liberar_grafo(g1);
    liberar_grafo(g2);

    return 0;
}