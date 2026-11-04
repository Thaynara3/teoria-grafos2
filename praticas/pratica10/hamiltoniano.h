#ifndef HAMILTONIANO_H
#define HAMILTONIANO_H

#include <stdbool.h>
#include <stdlib.h>

#define MAX_V 100

bool eh_caminho_hamiltoniano(int grafo[MAX_V][MAX_V], int caminho[], int n);
bool encontrar_caminho_hamiltoniano_bt(int grafo[MAX_V][MAX_V], int n, int pos, int caminho[], bool visitado[]);

#endif