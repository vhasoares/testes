/**
 * Victor Luiz de França
 * 9790781
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct indice {
	char chaveBusca[28];
	int RRN;
} indice;

void salvaIndice(indice indices, FILE *arquivo2);
int indiceSort(const void *lt, const void *gt);
int lerTotalIndices(FILE *arquivoIndice);
void lerIndices(indice indices[], FILE *arquivoIndice);