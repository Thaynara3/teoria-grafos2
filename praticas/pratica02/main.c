#include <stdio.h>
#include <stdlib.h>
#include "busca_largura.h"
#include "busca_profundidade.h"

int main()
{
    printf("=== PRATICA 02: TEORIA DE GRAFOS (BFS / DFS) ===\n\n");

    GrafoLista *g = criar_grafo(6);

    adicionar_aresta(g, 0, 1);
    adicionar_aresta(g, 0, 2);
    adicionar_aresta(g, 1, 3);
    adicionar_aresta(g, 2, 4);

    // 1. Testando BFS
    int *dist = (int *)malloc(6 * sizeof(int));
    int *pred = (int *)malloc(6 * sizeof(int));
    bfs(g, 0, dist, pred);

    printf("[1] Executando BFS a partir da origem 0:\n");
    for (int i = 0; i < 6; i++)
    {
        printf("  Vertice %d -> Distancia: %d, Predecessor: %d\n", i, dist[i], pred[i]);
    }

    int *visitado = (int *)calloc(6, sizeof(int));
    int *d = (int *)calloc(6, sizeof(int));
    int *f = (int *)calloc(6, sizeof(int));
    int tempo = 0;

    dfs_recursiva(g, 0, visitado, d, f, &tempo);

    printf("\n[2] Executando DFS (Tempos de Descoberta e Finalizacao):\n");
    for (int i = 0; i < 6; i++)
    {
        printf("  Vertice %d -> Entrada d[%d]: %d, Saida f[%d]: %d\n", i, i, d[i], i, f[i]);
    }

    printf("\n[3] Propriedades do Grafo:\n");
    printf("  Componentes Conexos: %d\n", contar_componentes(g));
    printf("  Possui Ciclo? %s\n", tem_ciclo(g) ? "Sim" : "Nao");
    printf("  E Bipartido? %s\n", eh_bipartido(g) ? "Sim" : "Nao");

    adicionar_aresta(g, 1, 2);
    printf("\n[4] Apos adicionar aresta (1, 2):\n");
    printf("  Possui Ciclo? %s\n", tem_ciclo(g) ? "Sim" : "Nao");
    printf("  E Bipartido? %s\n", eh_bipartido(g) ? "Sim" : "Nao");

    free(dist);
    free(pred);
    free(visitado);
    free(d);
    free(f);
    destruir_grafo(g);

    return 0;
}