#include <stdio.h>
#include <stdlib.h>
#include "dag.h"

void imprimir_array(int *arr, int tamanho, const char *metodo) {
    if (arr == NULL) {
        printf("%s: Ciclo detectado! Ordenação impossível.\n", metodo);
        return;
    }
    printf("%s: ", metodo);
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    printf("=== TESTE 1: Grafo Acíclico Dirigido (DAG) ===\n");
    GrafoLista *dag = criar_grafo(6);
    adicionar_aresta(dag, 5, 2);
    adicionar_aresta(dag, 5, 0);
    adicionar_aresta(dag, 4, 0);
    adicionar_aresta(dag, 4, 1);
    adicionar_aresta(dag, 2, 3);
    adicionar_aresta(dag, 3, 1);

    if (eh_dag(dag)) {
        printf("Grafo 1 é um DAG (Acíclico).\n");
    } else {
        printf("Grafo 1 possui ciclo.\n");
    }

    int tam_kahn = 0, tam_dfs = 0;
    int *res_kahn = ordenacao_topologica_kahn(dag, &tam_kahn);
    int *res_dfs = ordenacao_topologica_dfs(dag, &tam_dfs);

    imprimir_array(res_kahn, tam_kahn, "Kahn (BFS)");
    imprimir_array(res_dfs, tam_dfs, "DFS");

    free(res_kahn);
    free(res_dfs);
    destruir_grafo(dag);

    printf("\n=== TESTE 2: Grafo Cíclico ===\n");
    GrafoLista *ciclico = criar_grafo(3);
    adicionar_aresta(ciclico, 0, 1);
    adicionar_aresta(ciclico, 1, 2);
    adicionar_aresta(ciclico, 2, 0);

    if (eh_dag(ciclico)) {
        printf("Grafo 2 é um DAG (Acíclico).\n");
    } else {
        printf("Grafo 2 possui ciclo.\n");
    }

    res_kahn = ordenacao_topologica_kahn(ciclico, &tam_kahn);
    res_dfs = ordenacao_topologica_dfs(ciclico, &tam_dfs);

    imprimir_array(res_kahn, tam_kahn, "Kahn (BFS)");
    imprimir_array(res_dfs, tam_dfs, "DFS");

    free(res_kahn);
    free(res_dfs);
    destruir_grafo(ciclico);

    return 0;
}