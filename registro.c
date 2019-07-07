/**
 * Victor Luiz de França
 * 9790781
 */
#include "registro.h"

extern FILE *arquivoTrab1si;

void novoRegistro(registro *reg, cabecalho *cab){
	memset(reg, '@', sizeof(registro));
	reg->removido = '-';
	reg->encadeamento = -1;
	reg->nroInscricao = -1;
	reg->nota = -1;
	reg->data[0] = '\0';
	reg->tagCampo4 = cab->tagCampo4;
	reg->tagCampo5 = cab->tagCampo5;
	reg->indTam4 = 0;
	reg->indTam5 = 0;
	reg->cidade[0] = '\0';
	reg->nomeEscola[0] = '\0';
}


void defineRegistro(registro *reg, char *nroInscricao, char *nota, char *data, char *cidade, char *nomeEscola) {
	if(strlen(nroInscricao)) {
		reg->nroInscricao = atoi(nroInscricao);
	}
	reg->nota = strlen(nota) == 0 ? -1 : atof(nota);
	if(strlen(data)) {
		strcpy(reg->data,data);
	}
	if(strlen(cidade)) {
		reg->indTam4 = strlen(cidade)+2;
		strcpy(reg->cidade,cidade);
	}
	if(strlen(nomeEscola)) {
		reg->indTam5 = strlen(nomeEscola)+2;
		strcpy(reg->nomeEscola,nomeEscola);
	}
}


void salvaRegistro(registro *reg) {
	salvaRegistroArq(reg, arquivoTrab1si);
}

void salvaRegistroArq(registro *reg, FILE *arquivoTrab1si) {
	// soma dos caracteres
	int soma = 0;
	soma += 1*fwrite(&reg->removido, 1, 1, arquivoTrab1si);
	soma += 4*fwrite(&reg->encadeamento, 4, 1, arquivoTrab1si);
	soma += 4*fwrite(&reg->nroInscricao, 4, 1, arquivoTrab1si);
	soma += 8*fwrite(&reg->nota, 8, 1, arquivoTrab1si);
	soma += 10*fwrite(reg->data, 10, 1, arquivoTrab1si);

	if(reg->indTam4) {
		soma += 4*fwrite(&reg->indTam4, 4, 1, arquivoTrab1si);
		soma += 1*fwrite(&reg->tagCampo4, 1, 1, arquivoTrab1si);
		soma += (reg->indTam4-1)*fwrite(reg->cidade, reg->indTam4-1, 1, arquivoTrab1si);
	}
	if(reg->indTam5) {
		soma += 4*fwrite(&reg->indTam5, 4, 1, arquivoTrab1si);
		soma += 1*fwrite(&reg->tagCampo5, 1, 1, arquivoTrab1si);
		soma += (reg->indTam5-1)*fwrite(reg->nomeEscola, reg->indTam5-1, 1, arquivoTrab1si);
	}
	for(int i=soma; i<80; i++) {
		fputc('@', arquivoTrab1si);
	}
}

int qsort_reg(const void *ptr1, const void *ptr2) {
	registro *regA = (registro *) ptr1;
	registro *regB = (registro *) ptr2;
	if(regA->removido == '*') return 1;
	if(regB->removido == '*') return -1;
	return regA->nroInscricao - regB->nroInscricao;
}

int lerRegistro(registro *reg, cabecalho *cab) {
	return lerRegistroArq(reg, cab, arquivoTrab1si);
}

int lerRegistroArq(registro *reg, cabecalho *cab, FILE *arquivoTrab1si) {
	memset(reg, 0, sizeof(registro));
	int ret = fread(&reg->removido, 1, 1, arquivoTrab1si);
	if(!ret) {
		return ret;
	}
	fread(&reg->encadeamento, 4, 1, arquivoTrab1si);
	fread(&reg->nroInscricao, 4, 1, arquivoTrab1si);
	fread(&reg->nota, 8, 1, arquivoTrab1si);
	fread(reg->data, 10, 1, arquivoTrab1si);

	int indTam;
	char tagCampo;
	fread(&indTam, 4, 1, arquivoTrab1si);
	fread(&tagCampo, 1, 1, arquivoTrab1si);

	if(tagCampo == cab->tagCampo4) {
		reg->indTam4 = indTam;
		reg->tagCampo4 = tagCampo;
		fread(reg->cidade, indTam-1, 1, arquivoTrab1si);
		// parte pro próximo
		fread(&indTam, 4, 1, arquivoTrab1si);
		fread(&tagCampo, 1, 1, arquivoTrab1si);
	}
	if(tagCampo == cab->tagCampo5) {
		reg->indTam5 = indTam;
		reg->tagCampo5 = tagCampo;
		fread(reg->nomeEscola, indTam-1, 1, arquivoTrab1si);
	}
	return ret;
}

int nextRegArq(int pos, FILE *arquivoTrab1si) {
	pos -= pos % 80;
	pos += 80;
	fseek(arquivoTrab1si, pos, SEEK_SET);
	return pos;
}

int nextReg(int pos) {
	return nextRegArq(pos, arquivoTrab1si);
}