/**
 * Victor Luiz de França
 * 9790781
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "registro.h"
#include "indice.h"
#include "SCC0215012019escreverTela2.h"

FILE *arquivoTrab1si = NULL;
FILE *arquivoIndice = NULL;
int totalIndices;
indice *indices;
int leitura15;

FILE *abrirArquivo(char *nome,char *modo){
	FILE *retorno = fopen(nome,modo);
	if(retorno == NULL) {
		printf("Falha no carregamento do arquivo.\n");
		exit(0);
	}
	return retorno;
}

int main() {
	#ifdef SGDB
		freopen("cases/4.in", "r", stdin);
		freopen("runcodes/4.out", "w", stdout);
	#endif // SGDB
	int n;
	scanf("%d", &n);

	if(n == 1) {
		char nome[100];
		scanf("%s", nome);

		FILE *arquivoCsv = abrirArquivo(nome,"rb");
		arquivoTrab1si = abrirArquivo("arquivoTrab1si.bin","wb");

		// salva o cabeçalho
		cabecalho cab;
		novoCabecalho(&cab);
		// escrevendo
		salvaCabecalho(&cab);

		// le a primeira linha do csv
		char linha[200];
		fgets(linha,200,arquivoCsv);

		while(1) {
			char *virgula = ",";
			fgets(linha,200,arquivoCsv);
			if(feof(arquivoCsv)) {
				break;
			}
			// tira o \n
			linha[strlen(linha)-2] = '\0';
			char *nroInscricao;
			char *nota;
			char *data;
			char *cidade;
			char *nomeEscola;

			nroInscricao = linha;
			int i = 0;

			while(1) {
				if(linha[i] == ',') {
					linha[i] = 0;
					i++;
					nota = linha+i;
					break;
				}
				i++;
			}
			while(1) {
				if(linha[i] == ',') {
					linha[i] = 0;
					i++;
					data = linha+i;
					break;
				}
				i++;
			}
			while(1) {
				if(linha[i] == ',') {
					linha[i] = 0;
					i++;
					cidade = linha+i;
					break;
				}
				i++;
			}
			while(1) {
				if(linha[i] == ',') {
					linha[i] = 0;
					i++;
					nomeEscola = linha+i;
					break;
				}
				i++;
			}

			registro reg;
			novoRegistro(&reg, &cab);
			defineRegistro(&reg, nroInscricao, nota, data, cidade, nomeEscola);
			salvaRegistro(&reg);
		}


		fclose(arquivoCsv);
		fclose(arquivoTrab1si);
		printf("arquivoTrab1si.bin");
	}
	else if(n == 2 || n == 3 || n == 4 || n == 5 || n == 6 || n == 7 || n == 8 || n == 13 || n == 14 || n == 15) {
		char nome[100];
		char nome2[100];
		char campo[100];
		char busca[100];
		int rrn;
		scanf("%s ",nome);
		if(n == 13 || n == 14 || n == 15) {
			scanf("%s ", nome2);
		}
		if(n == 3 || n == 15) {
			scanf("%s ",campo);
			scan_quote_string(busca);
		}
		else if(n == 4) {
			scanf("%d",&rrn);
		}
		if(n == 15) {
			FILE *arquivoIndice = fopen(nome2, "r");
			ehValido(arquivoIndice);
			fclose(arquivoIndice);
			printf("*** Realizando a busca sem o auxílio de índice\n");
		}
		// faz a leitura do arquivo
		cabecalho cab;
		if(n == 2 || n == 3 || n == 4 || n == 15) {
			// modo leitura
			arquivoTrab1si = abrirArquivo(nome,"rb");
		}
		else {
			// modo escrita
			arquivoTrab1si = abrirArquivo(nome,"rb+");
			if(fgetc(arquivoTrab1si) != '1') {
				// tem que ser igual a 1
				printf("Falha no processamento do arquivo.\n");
				exit(0);
			}
			rewind(arquivoTrab1si);
			fputc('0', arquivoTrab1si);
		}
		if(n == 13 || n == 14) {
			arquivoIndice = fopen(nome2, "rb+");
			ehValido(arquivoIndice);
			totalIndices = lerTotalIndices(arquivoIndice);
			indices = (indice *) malloc(sizeof(indice) * totalIndices);
			lerIndices(indices, arquivoIndice);
		}
		// número de registros
		fseek(arquivoTrab1si,0,SEEK_END);
		int tamArquivo = ftell(arquivoTrab1si);
		if(tamArquivo < 16000 || tamArquivo % 80 != 0) {
			printf("Falha no processamento do arquivo.\n");
			exit(0);
		}
		int totalRegs = (tamArquivo-16000)/80;
		rewind(arquivoTrab1si);
		// começa em 1 pq estou lendo o cabecalho
		int paginas = 1;
		readCabecalho(&cab, arquivoTrab1si);

		int proxReg = ftell(arquivoTrab1si);

		if(n == 2 || n == 3 || n == 4 || n == 5 || n == 6 || n == 7 || n == 8 || n == 13 || n == 14 || n == 15) {
			int repeticoes = 1;
			if(n == 5 || n == 6 || n == 7 || n == 13 || n == 14) {
				scanf("%d", &repeticoes);
			}
			for(int r=0; r<repeticoes; r++) {
				if(n != '5') {
					fseek(arquivoTrab1si, 16000, SEEK_SET);
				}
				char nroInscricao[100];
				char nota[100];
				char data[100];
				char cidade[100];
				char nomeEscola[100];
				if(n == 6 || n == 14) {
					scan_quote_string(nroInscricao);
					scan_quote_string(nota);
					scan_quote_string(data);
					scan_quote_string(cidade);
					scan_quote_string(nomeEscola);
				}
				if(n == 7) {
					scanf("%d",&rrn);
				}
				if(n == 5 || n == 7 || n == 13) {
					scanf("%s", campo);
					scan_quote_string(busca);
				}
				if(n == 6 || n == 14) {
					rrn = cab.topoPilha;
					if(rrn == -1) {
						rrn = totalRegs-1;
					}
				}
				registro reg;
				char encontrado = 0;
				if(n == 6 && totalRegs == 0 || n == 14) {
					// tem q entrar no loop
					totalRegs = 1;
				}
				registro array_registro[totalRegs];
				for(int i=0;i<totalRegs;i++) {
					int posAtual = proxReg;
					fseek(arquivoTrab1si, posAtual, SEEK_SET);
					proxReg = posAtual+80;
					if(n == 5 || n == 13) {
						if(proxReg >= tamArquivo) {
							proxReg = 16000;
						}
					}
					if(posAtual%16000 == 0) {
						// acessei outra página
						paginas++;
					}
					if(n == 4 || n == 6 || n == 7 || n == 14) {
						if(rrn >= totalRegs && (n != 14)) {
							break;
						}
						posAtual = 16000+80*rrn;
						fseek(arquivoTrab1si, posAtual, SEEK_SET);
						paginas = 2;
					}
					memset(&reg, 0, sizeof(registro));
					// lê o registro
					lerRegistro(&reg, &cab);

					if(n == 3 || n == 5 || n == 13 || n == 15) {
						if(strcmp(campo, "data") == 0) {
							if(strcmp(reg.data, busca) != 0) {
								continue;
							}
							encontrado = 1;
						}
						else if(strcmp(campo, "nroInscricao") == 0) {
							if(reg.nroInscricao != atoi(busca)) {
								continue;
							}
							encontrado = 1;
						}
						else if(strcmp(campo, "nota") == 0) {
							if(reg.nota != atof(busca)) {
								continue;
							}
							encontrado = 1;
						}
						else if(strcmp(campo, "cidade") == 0) {
							if(strcmp(reg.cidade, busca) != 0) {
								continue;
							}
							encontrado = 1;
						}
						else if(strcmp(campo, "nomeEscola") == 0) {
							if(strcmp(reg.nomeEscola, busca) != 0) {
								continue;
							}
							encontrado = 1;
						}
						else {
							printf("Cadastrar busca: %s\n", campo);
							exit(0);
						}
					}

					if((n == 2 || n == 3 || n == 4 || n == 15) && reg.removido == '-') {
						printf("%d", reg.nroInscricao);
						if(reg.nota != 0 && reg.nota != -1) {
							printf(" %.1f", reg.nota);
						}
						if(strcmp(reg.data, "") != 0) {
							printf(" %s", reg.data);
						}
						if(reg.indTam4 > 0) {
							printf(" %d", reg.indTam4-2);
							printf(" %s", reg.cidade);
						}
						if(reg.indTam5 > 0) {
							printf(" %d", reg.indTam5-2);
							printf(" %s", reg.nomeEscola);
						}
						printf("\n");
					}
					else if(n == 8) {
						memcpy(&array_registro[i], &reg, sizeof(registro));
					}

					if(n == 5 || n == 13) {
						if(n == 13) {
							int rrn = RRN(posAtual);
							for(int i=0; i<totalIndices; i++) {
								if(indices[i].RRN == rrn) {
									indices[i].RRN = -1;
									indices[i].chaveBusca[0] = 0;
									qsort(indices, totalIndices, sizeof(indice), indiceSort);
									totalIndices--;
									break;
								}
							}
						}
						// deleto ele
						fseek(arquivoTrab1si, posAtual, SEEK_SET);
						int prox = cab.topoPilha;
						cab.topoPilha = (posAtual-16000)/80;
						// informação de deletado
						fputc('*', arquivoTrab1si);
						fwrite(&prox, 4, 1, arquivoTrab1si);
						for(int i=0; i<75; i++) {
							fputc('@', arquivoTrab1si);
						}
					}
					if(n == 6 || n == 14) {
						if(cab.topoPilha == -1) {
							fseek(arquivoTrab1si, 0, SEEK_END);
							posAtual = ftell(arquivoTrab1si);
							novoRegistro(&reg, &cab);
							defineRegistro(&reg, nroInscricao, nota, data, cidade, nomeEscola);
							salvaRegistro(&reg);
							totalRegs++;
						}
						else {
							cab.topoPilha = reg.encadeamento;
							// volta pra escrever
							fseek(arquivoTrab1si, posAtual, SEEK_SET);
							posAtual = ftell(arquivoTrab1si);
							novoRegistro(&reg, &cab);
							defineRegistro(&reg, nroInscricao, nota, data, cidade, nomeEscola);
							salvaRegistro(&reg);
						}
						if(nomeEscola[0] != 0) {
							totalIndices++;
							indices = (indice *) realloc(indices, sizeof(indice) * totalIndices);
							strcpy(indices[totalIndices-1].chaveBusca, nomeEscola);
							indices[totalIndices-1].RRN = RRN(posAtual);
							qsort(indices, totalIndices, sizeof(indice), indiceSort);
						}
						break;
					}
					if(n == 7) {
						if(reg.removido == '-') {
							// atualizo ele
							fseek(arquivoTrab1si, posAtual, SEEK_SET);
							if(strcmp(campo, "nroInscricao") == 0) reg.nroInscricao = atoi(busca);
							if(strcmp(campo, "nota") == 0) reg.nota = atof(busca);
							if(strcmp(campo, "data") == 0) strcpy(reg.data, busca);
							if(strcmp(campo, "cidade") == 0) {
								reg.tagCampo4 = cab.tagCampo4;
								reg.indTam4 = busca[0] == 0 ? 0 : strlen(busca)+2;
								strcpy(reg.cidade, busca);
							}
							if(strcmp(campo, "nomeEscola") == 0) {
								reg.tagCampo5 = cab.tagCampo5;
								reg.indTam5 = busca[0] == 0 ? 0 : strlen(busca)+2;
								strcpy(reg.nomeEscola, busca);
							}
							salvaRegistro(&reg);
						}
						break;
					}

					if((n == 3 || n == 5 || n == 13 || n == 15) && encontrado && strcmp(campo, "nroInscricao") == 0) {
						// se estou buscando pelo número de inscrição
						// e encontrei
						// posso parar
						break;
					}

					if(n == 4) {
						break;
					}
				}

				if(n == 8) {
					// agora eu ordeno
					qsort(array_registro, totalRegs, sizeof(registro), qsort_reg);
					char nome[100];
					scanf("%s", nome);
					FILE *saida = fopen(nome, "w+");
					cab.status = '1';
					salvaCabecalhoArq(&cab, saida);
					cab.status = '0';
					for(int i=0; i<totalRegs; i++) {
						if(array_registro[i].removido == '-') {
							salvaRegistroArq(&array_registro[i], saida);
						}
					}
					binarioNaTela1(saida);
					fclose(saida);
				}

				if(n == 2 || n == 3 || n == 4 || n == 15) {
					if((n == 3 || n == 15) && !encontrado) {
						printf("Registro inexistente.\n");
					}
					else {
						leitura15 = paginas;
						printf("Número de páginas de disco acessadas: %d\n", paginas);
						if(n == 15) {
							printf("\n");
						}
					}
				}
			}
		}

		if(n == 5 || n == 6 || n == 7 || n == 8 || n == 13 || n == 14) {
			// coloca zero no status antes de sair
			rewind(arquivoTrab1si);
			salvaCabecalho(&cab);
			rewind(arquivoTrab1si);
			fputc('1', arquivoTrab1si);
			if(n == 13 || n == 14) {
				fclose(arquivoIndice);
				arquivoIndice = fopen(nome2, "wb+");
				fputc('1', arquivoIndice);
				fwrite(&totalIndices, sizeof(int), 1, arquivoIndice);
				for(int i=0; i<15995; i++) { fputc('@', arquivoIndice); }
				for(int i=0; i<totalIndices; i++) { salvaIndice(indices[i], arquivoIndice); }
				binarioNaTela1(arquivoIndice);
				fclose(arquivoIndice);
			}
			else if(n != 8) {
				binarioNaTela1(arquivoTrab1si);
			}
		}
		fclose(arquivoTrab1si);
	}
	else if(n == 9 || n  == 10) {
		char nome1[100];
		char nome2[100];
		char nome_saida[100];
		scanf("%s ",nome1);
		scanf("%s ",nome2);
		scanf("%s ",nome_saida);
		FILE *arquivo1 = fopen(nome1, "r");
		FILE *arquivo2 = fopen(nome2, "r");

		void arquivoLivre(FILE *arquivo) {
			if(fgetc(arquivo) == '0') {
				printf("Falha no processamento do arquivo.\n");
				exit(0);
			}
			rewind(arquivo);
		}
		arquivoLivre(arquivo1);
		arquivoLivre(arquivo2);
		FILE *saida = fopen(nome_saida, "w+");

		int findTotalRegs(FILE *arq) {
			fseek(arq, 0, SEEK_END);
			int tam = (ftell(arq)-16000)/80;
			rewind(arq);
			return tam;
		}

		int totalRegs1 = findTotalRegs(arquivo1);
		int totalRegs2 = findTotalRegs(arquivo2);
		cabecalho cab1;
		cabecalho cab2;
		readCabecalho(&cab1, arquivo1);
		readCabecalho(&cab2, arquivo2);
		salvaCabecalhoArq(&cab1, saida);

		registro reg1;
		registro reg2;
		int pos1 = 0;
		int pos2 = 0;
		void posComLer(int pos, int totalRegs, registro *reg, cabecalho *cab, FILE *arquivo) {
			if(pos < totalRegs) {
				fseek(arquivo, pos*80+16000, SEEK_SET);
				lerRegistroArq(reg, cab, arquivo);
			}
		}
		posComLer(pos1, totalRegs1, &reg1, &cab1, arquivo1);
		posComLer(pos2, totalRegs2, &reg2, &cab2, arquivo2);
		while(pos1 < totalRegs1 && pos2 < totalRegs2) {
			int cmp = qsort_reg(&reg1, &reg2);

			if(cmp < 0) {
				if(n == 9) {
					salvaRegistroArq(&reg1, saida);
				}
				pos1++;
				posComLer(pos1, totalRegs1, &reg1, &cab1, arquivo1);
			}
			else if(cmp > 0) {
				if(n == 9) {
					salvaRegistroArq(&reg2, saida);
				}
				pos2++;
				posComLer(pos2, totalRegs2, &reg2, &cab2, arquivo2);
			}
			else {
				salvaRegistroArq(&reg1, saida);
				pos1++;
				pos2++;
				posComLer(pos1, totalRegs1, &reg1, &cab1, arquivo1);
				posComLer(pos2, totalRegs2, &reg2, &cab2, arquivo2);
			}
		}
		if(n == 9) {
			while(pos1 < totalRegs1) {
				posComLer(pos1, totalRegs1, &reg1, &cab1, arquivo1);
				if(reg1.removido == '-') salvaRegistroArq(&reg1, saida);
				pos1++;
			}
			while(pos2 < totalRegs2) {
				posComLer(pos2, totalRegs2, &reg2, &cab2, arquivo2);
				if(reg2.removido == '-') salvaRegistroArq(&reg2, saida);
				pos2++;
			}
		}


		fclose(arquivo1);
		fclose(arquivo2);
		binarioNaTela1(saida);
		fclose(saida);
	}
	if(n == 11) {
		char nome1[100];
		char nome2[100];
		scanf("%s ", nome1);
		scanf("%s ", nome2);
		arquivoTrab1si = fopen(nome1, "rb");
		ehValido(arquivoTrab1si);
		fseek(arquivoTrab1si, 0, SEEK_END);
		int fileSize = ftell(arquivoTrab1si);
		int totalRegs = (fileSize-16000)/80;
		rewind(arquivoTrab1si);
		cabecalho c;
		registro r;
		indice indices[totalRegs];
		int totalIndices = 0;
		readCabecalho(&c, arquivoTrab1si);
		fseek(arquivoTrab1si, 16000, SEEK_SET);
		int pos = ftell(arquivoTrab1si);
		while(lerRegistro(&r, &c)) {
			if(r.nomeEscola[0] != '\0') {
				strcpy(indices[totalIndices].chaveBusca, r.nomeEscola);
				indices[totalIndices].RRN = RRN(pos);
				totalIndices++;
			}
			pos = nextReg(pos);
		}
		fclose(arquivoTrab1si);
		FILE *arquivo2 = fopen(nome2, "wb+");
		fputc('1', arquivo2);
		fwrite(&totalIndices, sizeof(int), 1, arquivo2);
		for(int i=0; i<15995; i++) {
			fputc('@', arquivo2);
		}
		qsort(indices, totalIndices, sizeof(indice), indiceSort);
		for(int i=0; i<totalIndices; i++) {
			salvaIndice(indices[i], arquivo2);
		}
		binarioNaTela1(arquivo2);
		fclose(arquivo2);
	}
	if(n == 12 || n == 15) {
		if(n == 15) {
			fseek(stdin, 0, SEEK_SET);
			printf("*** Realizando a busca com o auxílio de um índice secundário fortemente ligado\n");
			scanf("%d", &n);
		}
		char nome1[100];
		char nome2[100];
		char campo[100];
		char busca[100];
		scanf("%s ", nome1);
		scanf("%s ", nome2);
		scanf("%s ", campo);
		scan_quote_string(busca);
		arquivoTrab1si = fopen(nome1, "rb");
		ehValido(arquivoTrab1si);
		fseek(arquivoTrab1si, 0, SEEK_END);
		int fileSize = ftell(arquivoTrab1si);
		int totalRegs = (fileSize-16000)/80;
		rewind(arquivoTrab1si);
		cabecalho c;
		registro r;
		readCabecalho(&c, arquivoTrab1si);
		fseek(arquivoTrab1si, 16000, SEEK_SET);
		FILE *arquivoIndice = fopen(nome2, "rb");
		ehValido(arquivoIndice);
		int totalIndices = lerTotalIndices(arquivoIndice);
		indice indices[totalIndices];
		lerIndices(indices, arquivoIndice);
		int Paginas[1000] = {0};
		for(int i=0; i<totalIndices; i++) {
			if(strcmp(indices[i].chaveBusca, busca) == 0) {
				fseek(arquivoTrab1si, POS(indices[i].RRN), SEEK_SET);
				int pagina = POS(indices[i].RRN) / 16000;
				Paginas[pagina] = 1;
				lerRegistro(&r, &c);
				printf("%d", r.nroInscricao);
				if(r.nota != 0 && r.nota != -1) {
					printf(" %.1f", r.nota);
				}
				if(strcmp(r.data, "") != 0) {
					printf(" %s", r.data);
				}
				if(r.indTam4 > 0) {
					printf(" %d", r.indTam4-2);
					printf(" %s", r.cidade);
				}
				if(r.indTam5 > 0) {
					printf(" %d", r.indTam5-2);
					printf(" %s", r.nomeEscola);
				}
				printf("\n");
			}
		}
		fclose(arquivoIndice);
		fclose(arquivoTrab1si);
		int totalPaginas = 0;
		for(int i=0; i<1000; i++) {
			if(Paginas[i]) {
				totalPaginas++;
			}
		}
		totalPaginas++;
		if(totalPaginas == 1) {
			printf("Registro inexistente.\n");
		}
		else {
			printf("Número de páginas de disco para carregar o arquivo de índice: %d\n", (totalIndices*32+16000)/16000+1);
			printf("Número de páginas de disco para acessar o arquivo de dados: %d\n", totalPaginas);

			if(n == 15) {
				printf("\nDiferença no número de páginas de disco acessadas: %d\n", leitura15 - totalPaginas);
			}
		}
	}

	return 0;
}