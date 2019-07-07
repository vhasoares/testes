/**
 * Victor Luiz de França
 * 9790781
 */
#include "indice.h"

extern FILE *arquivoTrab1si;

void salvaIndice(indice ind, FILE *arquivo2) {
	int total = fwrite(ind.chaveBusca, 1, strlen(ind.chaveBusca)+1, arquivo2);
	for(int i=0; i<28-total; i++) {
		fputc('@', arquivo2);
	}
	fwrite(&ind.RRN, 4, 1, arquivo2);
}

int indiceSort(const void *lt, const void *gt) {
	indice *indexA = (indice *) lt;
	indice *indexB = (indice *) gt;
	if(indexA->chaveBusca[0] == 0 && indexB->chaveBusca[0] != 0) return 1;
	if(indexA->chaveBusca[0] != 0 && indexB->chaveBusca[0] == 0) return -1;
	int _strcmp = strcmp(indexA->chaveBusca, indexB->chaveBusca);
	if((indexA->chaveBusca[0] == 0 && indexB->chaveBusca == 0) || _strcmp == 0) return indexA->RRN - indexB->RRN;
	return _strcmp;
}

int lerTotalIndices(FILE *arquivoIndice) {
	rewind(arquivoIndice);
	fgetc(arquivoIndice);
	int ret;
	fread(&ret, sizeof(ret), 1, arquivoIndice);
	return ret;
}

void lerIndices(indice indices[], FILE *arquivoIndice) {
	int totalIndices = lerTotalIndices(arquivoIndice);
	fseek(arquivoIndice, 16000, SEEK_SET);
	for(int i=0; i<totalIndices; i++) {
		fread(indices[i].chaveBusca, 1, 28, arquivoIndice);
		fread(&(indices[i].RRN), 4, 1, arquivoIndice);
	}
}