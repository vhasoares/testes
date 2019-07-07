/**
 * Victor Luiz de França
 * 9790781
 */
#include "cabecalho.h"

extern FILE *arquivoTrab1si;

void novoCabecalho(cabecalho *cab) {
	memset(cab, '@', sizeof(cabecalho));

	cab->status = '1';
	cab->topoPilha = -1;
	cab->tagCampo1 = '1';
	cab->tagCampo2 = '2';
	cab->tagCampo3 = '3';
	cab->tagCampo4 = '4';
	cab->tagCampo5 = '5';
	strcpy(cab->desCampo1, "numero de inscricao do participante do ENEM");
	strcpy(cab->desCampo2, "nota do participante do ENEM na prova de matematica");
	strcpy(cab->desCampo3, "data");
	strcpy(cab->desCampo4, "cidade na qual o participante do ENEM mora");
	strcpy(cab->desCampo5, "nome da escola de ensino medio");
}

void salvaCabecalho(cabecalho *cab) {
	salvaCabecalhoArq(cab, arquivoTrab1si);
}

void salvaCabecalhoArq(cabecalho *cab, FILE *arquivoTrab1si) {
	fwrite(&cab->status,1,1,arquivoTrab1si);
	fwrite(&cab->topoPilha,4,1,arquivoTrab1si);
	fwrite(&cab->tagCampo1,1,1,arquivoTrab1si);
	fwrite(cab->desCampo1,55,1,arquivoTrab1si);
	fwrite(&cab->tagCampo2,1,1,arquivoTrab1si);
	fwrite(cab->desCampo2,55,1,arquivoTrab1si);
	fwrite(&cab->tagCampo3,1,1,arquivoTrab1si);
	fwrite(cab->desCampo3,55,1,arquivoTrab1si);
	fwrite(&cab->tagCampo4,1,1,arquivoTrab1si);
	fwrite(cab->desCampo4,55,1,arquivoTrab1si);
	fwrite(&cab->tagCampo5,1,1,arquivoTrab1si);
	fwrite(cab->desCampo5,55,1,arquivoTrab1si);
	for(int i=285;i<16000;i++){
		fputc('@',arquivoTrab1si);
	}
}

void readCabecalho(cabecalho *cab, FILE *arquivoTrab1si) {
	fread(&cab->status,1,1,arquivoTrab1si);
	fread(&cab->topoPilha,4,1,arquivoTrab1si);
	fread(&cab->tagCampo1,1,1,arquivoTrab1si);
	fread(cab->desCampo1,55,1,arquivoTrab1si);
	fread(&cab->tagCampo2,1,1,arquivoTrab1si);
	fread(cab->desCampo2,55,1,arquivoTrab1si);
	fread(&cab->tagCampo3,1,1,arquivoTrab1si);
	fread(cab->desCampo3,55,1,arquivoTrab1si);
	fread(&cab->tagCampo4,1,1,arquivoTrab1si);
	fread(cab->desCampo4,55,1,arquivoTrab1si);
	fread(&cab->tagCampo5,1,1,arquivoTrab1si);
	fread(cab->desCampo5,55,1,arquivoTrab1si);
	fseek(arquivoTrab1si,16000,SEEK_SET);
}

int RRN(int pos) {
	return (pos-16000)/80;
}

int POS(int RRN) {
	return RRN*80+16000;
}

int ehValido(FILE *arquivoTrab1si) {
	rewind(arquivoTrab1si);
	if(fgetc(arquivoTrab1si) == '1') {
		rewind(arquivoTrab1si);
		return 1;
	}
	printf("Falha no processamento do arquivo.\n");
	exit(0);
	return 0;
}