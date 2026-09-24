#ifndef PLANARIDADE_H
#define PLANARIDADE_H

#include "conectividade.h"

int contar_arestas(GrafoLista* g);
bool eh_planar_euler(GrafoLista* g);
bool eh_planar_kuratowski(GrafoLista* g);

#endif