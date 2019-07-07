/**
 * Victor Luiz de França
 * 9790781
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct cabecalho {
	char status;
	int topoPilha;
	char tagCampo1;
	char desCampo1[55];
	char tagCampo2;
	char desCampo2[55];
	char tagCampo3;
	char desCampo3[55];
	char tagCampo4;
	char desCampo4[55];
	char tagCampo5;
	char desCampo5[55];
} cabecalho;

void novoCabecalho(cabecalho *cab);
void salvaCabecalho(cabecalho *cab);
void salvaCabecalhoArq(cabecalho *cab, FILE *arquivoTrab1si);
void readCabecalho(cabecalho *cab, FILE *arquivoTrab1si);
int RRN(int pos);
int POS(int RRN);
int ehValido(FILE *arquivoTrab1si);