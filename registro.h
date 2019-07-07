/**
 * Victor Luiz de França
 * 9790781
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cabecalho.h"

typedef struct registro {
	char removido;
	int encadeamento;

	int nroInscricao;
	double nota;
	// data tem 10 chars
	char data[11];

	// cidade
	int indTam4;
	char tagCampo4;
	char cidade[100];

	// nomeEscola
	int indTam5;
	char tagCampo5;
	char nomeEscola[100];
} registro;

void novoRegistro(registro *reg, cabecalho *cab);
void salvaRegistro(registro *reg);
void defineRegistro(registro *reg, char *nroInscricao, char *nota, char *data, char *cidade, char *nomeEscola);
int qsort_reg(const void *ptr1, const void *ptr2);
void salvaRegistroArq(registro *reg, FILE *arquivoTrab1si);
int lerRegistro(registro *reg, cabecalho *cab);
int lerRegistroArq(registro *reg, cabecalho *cab, FILE *arquivoTrab1si);
int nextRegArq(int pos, FILE *arquivoTrab1si);
int nextReg(int pos);