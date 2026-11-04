#ifndef TPS_H
#define TPS_H

#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_V 100
#define INF 1000000000

int tsp_forca_bruta(int grafo[MAX_V][MAX_V], int n, int melhor_rota[]);
int tsp_vizinho_mais_proximo(int grafo[MAX_V][MAX_V], int n, int rota[]);
int tsp_insercao(int grafo[MAX_V][MAX_V], int n, int rota[]);
void grafo_para_tsp(int grafo_origem[MAX_V][MAX_V], int n, int grafo_tsp[MAX_V][MAX_V]);

#endif