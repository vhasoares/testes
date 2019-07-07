/**
 * Bruno Barrios Trench
 * 8656201
 *
 * Tiago Lascala Aude
 * 8936742
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "registro.h"
#include "SCC0215012019escreverTela2.h"

FILE *arquivoTrab1si = NULL;
int paginasAcessadas = 0;

FILE *abrirArquivo(char *nome,char *modo){
  FILE *retorno = fopen(nome,modo);
  if(retorno == NULL) {
    printf("Falha no carregamento do arquivo.\n");
    exit(0);
  }
  return retorno;
}

int main() {
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
  else if(n == 2 || n == 3 || n == 15 || n == 4 || n == 5||n == 13 || n == 6 || n == 14 || n == 7 || n == 8 || n == 11) {
    char nome[100];
    char indiceNome[100];
    char campo[100];
    char busca[100];
    int rrn;
    scanf("%s ",nome);
    if(n == 13 || n == 14 || n == 15) {
      scanf("%s ", indiceNome);
      if(n == 15) {
        FILE *indice = fopen(indiceNome, "rb");
        if(fgetc(indice) != '1') {
          printf("Falha no processamento do arquivo.\n");
          exit(0);
        }
        fclose(indice);
      }
    }
    if(n == 3 || n == 15) {
      scanf("%s ",campo);
      scan_quote_string(busca);
    }
    else if(n == 4) {
      scanf("%d",&rrn);
    }
    // faz a leitura do arquivo
    cabecalho cab;
    if(n == 2 || n == 3 || n == 15 || n == 4) {
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

    int totalIndices;
    int novoTotalIndices;
    indice_registro *indices;
    if(n == 13 || n == 14) {
      FILE *indice = fopen(indiceNome, "rb+");
      if(fgetc(indice) != '1') {
        // tem que ser igual a 1
        printf("Falha no processamento do arquivo.\n");
        exit(0);
      }
      rewind(indice);
      fputc('0', indice);

      fread(&totalIndices, sizeof(int), 1, indice);
      novoTotalIndices = totalIndices;
      fseek(indice, 16000, SEEK_SET);
      indices = (indice_registro *) malloc(sizeof(indice_registro) * totalIndices);
      for(int i=0; i<totalIndices; i++) {
        fread(indices[i].chaveBusca, 1, 28, indice);
        fread(&indices[i].RRN, sizeof(int), 1, indice);
      }
      fclose(indice);
    }

    if(n == 2||n == 3 || n == 15||n == 4||n == 5||n == 13||n == 6 || n == 14||n == 7||n==8 || n == 11) {
      int repeticoes = 1;
      if(n == 5||n == 13||n == 6 || n == 14||n == 7) {
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
        if(n == 5||n == 13||n == 7) {
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
        if(n == 6 || n == 14 && totalRegs == 0) {
          // tem q entrar no loop
          totalRegs = 1;
        }
        registro array_registro[totalRegs];
        indice_registro array_indice[totalRegs];
        memset(array_indice, 0, sizeof(array_indice));
        for(int i=0;i<totalRegs;i++) {
          int posAtual = proxReg;
          fseek(arquivoTrab1si, posAtual, SEEK_SET);
          proxReg = posAtual+80;
          if(n == 5||n == 13) {
            if(proxReg >= tamArquivo) {
              proxReg = 16000;
            }
          }
          if(posAtual%16000 == 0) {
            // acessei outra página
            paginas++;
          }
          if(n == 4 || n == 6 || n == 14 || n == 7) {
            if(rrn >= totalRegs) {
              break;
            }
            posAtual = 16000+80*rrn;
            fseek(arquivoTrab1si, posAtual, SEEK_SET);
            paginas = 2;
          }
          memset(&reg, 0, sizeof(registro));
          // lê o registro
          lerRegistro(&reg, &cab);

          if(n == 3 || n == 15||n == 5||n == 13) {
            if(strcmp(campo, "data") == 0) {
              if(strcmp(reg.data, busca) != 0) {
                continue;
              }
              if(!encontrado) {
                if(n == 15) printf("*** Realizando a busca sem o auxílio de índice\n");
              }
              encontrado = 1;
            }
            else if(strcmp(campo, "nroInscricao") == 0) {
              if(reg.nroInscricao != atoi(busca)) {
                continue;
              }
              if(!encontrado) {
                if(n == 15) printf("*** Realizando a busca sem o auxílio de índice\n");
              }
              encontrado = 1;
            }
            else if(strcmp(campo, "nota") == 0) {
              if(reg.nota != atof(busca)) {
                continue;
              }
              if(!encontrado) {
                if(n == 15) printf("*** Realizando a busca sem o auxílio de índice\n");
              }
              encontrado = 1;
            }
            else if(strcmp(campo, "cidade") == 0) {
              if(strcmp(reg.cidade, busca) != 0) {
                continue;
              }
              if(!encontrado) {
                if(n == 15) printf("*** Realizando a busca sem o auxílio de índice\n");
              }
              encontrado = 1;
            }
            else if(strcmp(campo, "nomeEscola") == 0) {
              if(strcmp(reg.nomeEscola, busca) != 0) {
                continue;
              }
              if(!encontrado) {
                if(n == 15) printf("*** Realizando a busca sem o auxílio de índice\n");
              }
              encontrado = 1;
            }
            else {
              printf("Cadastrar busca: %s\n", campo);
              exit(0);
            }
          }

          if((n == 2 || n == 3 || n == 15 || n == 4) && reg.removido == '-') {
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
          else if((n == 11) && reg.removido == '-') {
            array_indice[i].RRN = (posAtual - 16000) / 80;
            strcpy(array_indice[i].chaveBusca, reg.nomeEscola);
          }

          if(n == 5||n == 13) {
            if(n == 13) {
              int RRN = (posAtual-16000)/80;
              for(int i=0; i<totalIndices; i++) {
                if(indices[i].RRN == RRN) {
                  indices[i].chaveBusca[0] = 0;
                  indices[i].RRN = -1;
                  novoTotalIndices--;
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
            // deleto ele
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
              novoRegistro(&reg, &cab);
              defineRegistro(&reg, nroInscricao, nota, data, cidade, nomeEscola);
              salvaRegistro(&reg);
            }
            if(n == 14) {
              if(reg.nomeEscola[0]) {
                novoTotalIndices++;
                int i = novoTotalIndices-1;
                indices = (indice_registro *) realloc(indices, sizeof(indice_registro) * novoTotalIndices);
                strcpy(indices[i].chaveBusca, reg.nomeEscola);
                indices[i].RRN = (posAtual-16000)/80;
              }
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

          if((n == 3 || n == 15 || n == 5||n == 13) && encontrado && strcmp(campo, "nroInscricao") == 0) {
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

        if(n == 11) {
          char nome[100];
          scanf("%s", nome);
          FILE *arquivo = fopen(nome, "wb+");
          for(int i=0; i<16000; i++) {
            fputc('@', arquivo);
          }
          qsort(array_indice, totalRegs, sizeof(indice_registro), qsort_indice);
          int totalIndices = 0;
          for(int i=0; i<totalRegs; i++) {
            if(array_indice[i].chaveBusca[0]) {
              int totalChars = fwrite(array_indice[i].chaveBusca, 1, strlen(array_indice[i].chaveBusca), arquivo);
              fputc(0, arquivo);
              totalChars++;
              for(int i=totalChars; i<28; i++) {
                fputc('@', arquivo);
              }
              fwrite(&(array_indice[i].RRN), sizeof(int), 1, arquivo);
              totalIndices++;
            }
          }
          rewind(arquivo);
          fputc('1', arquivo);
          fwrite(&totalIndices, sizeof(int), 1, arquivo);
          binarioNaTela1(arquivo);
          fclose(arquivo);
        }
        else if(n == 2 || n == 3 || n == 15 || n == 4) {
          if(n == 3 || n == 15 && !encontrado) {
            printf("Registro inexistente.\n");
          }
          else {
            paginasAcessadas = paginas;
            printf("Número de páginas de disco acessadas: %d\n", paginas);
          }
        }
      }
    }

    if(n == 5||n == 13 || n == 6 || n == 14 || n == 7 || n == 8) {
      // coloca zero no status antes de sair
      rewind(arquivoTrab1si);
      salvaCabecalho(&cab);
      rewind(arquivoTrab1si);
      fputc('1', arquivoTrab1si);
      if(n == 13 || n == 14) {
        qsort(indices, totalIndices > novoTotalIndices ? totalIndices : novoTotalIndices, sizeof(indice_registro), qsort_indice);

        FILE *indice = fopen(indiceNome, "wb+");
        fputc('1', indice);
        fwrite(&novoTotalIndices, sizeof(novoTotalIndices), 1, indice);
        for(int i=0; i<16000-5; i++) {
          fputc('@', indice);
        }
        for(int i=0; i<novoTotalIndices; i++) {
          int totalChars = fwrite(indices[i].chaveBusca, 1, strlen(indices[i].chaveBusca), indice);
          fputc(0, indice);
          totalChars++;
          for(int i=totalChars; i<28; i++) {
            fputc('@', indice);
          }
          fwrite(&(indices[i].RRN), sizeof(int), 1, indice);
        }
        binarioNaTela1(indice);
        fclose(indice);
      }
      else if(n != 8) {
        binarioNaTela1(arquivoTrab1si);
      }
    }
    fclose(arquivoTrab1si);
  }
  else if(n == 9 || n ==10) {
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
  if(n == 12 || n == 15) {
    if(n == 15) {
      rewind(stdin);
      scanf("%d", &n);
      printf("\n");
    }
    char nome[100];
    char indiceNome[100];
    char campo[100];
    char busca[100];
    scanf("%s ", nome);
    scanf("%s ", indiceNome);
    scanf("%s ", campo);
    scan_quote_string(busca);

    // modo escrita
    arquivoTrab1si = abrirArquivo(nome,"rb+");
    if(fgetc(arquivoTrab1si) != '1') {
      // tem que ser igual a 1
      printf("Falha no processamento do arquivo.\n");
      exit(0);
    }
    rewind(arquivoTrab1si);
    fputc('0', arquivoTrab1si);
    
    FILE *indice = fopen(indiceNome,"rb+");

    fseek(arquivoTrab1si,0,SEEK_END);
    int tamArquivo = ftell(arquivoTrab1si);
    if(tamArquivo < 16000 || tamArquivo % 80 != 0) {
      printf("Falha no processamento do arquivo.\n");
      exit(0);
    }
    int totalRegs = (tamArquivo-16000)/80;

    if(fgetc(indice) != '1') {
      // tem que ser igual a 1
      printf("Falha no processamento do arquivo.\n");
      exit(0);
    }
    rewind(indice);
    fputc('0', indice);

    int totalIndices;
    fread(&totalIndices, sizeof(int), 1, indice);
    int totalPaginas = tamArquivo/16000 + 1;
    int paginas[totalPaginas];
    memset(paginas, 0, sizeof(paginas));

    indice_registro array_indice[totalIndices];
    fseek(indice, 16000, SEEK_SET);
    for(int i=0; i<totalIndices; i++) {
      fread(array_indice[i].chaveBusca, 1, 28, indice);
      fread(&array_indice[i].RRN, sizeof(int), 1, indice);
    }

    cabecalho cab;
    rewind(arquivoTrab1si);
    readCabecalho(&cab, arquivoTrab1si);

    registro reg;
    if(n == 15) {
      printf("*** Realizando a busca com o auxílio de um índice secundário fortemente ligado\n");
    }
    for(int i=0; i<totalIndices; i++) {
      if(strcmp(array_indice[i].chaveBusca, busca) == 0) {
        fseek(arquivoTrab1si, array_indice[i].RRN*80+16000, SEEK_SET);
        int pagina = (array_indice[i].RRN*80+16000)/16000;
        paginas[pagina] = 1;
        lerRegistro(&reg, &cab);
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
    }

    int sum = 1;
    for(int i=0; i<totalPaginas; i++) {
      sum += paginas[i];
    }
    if(sum == 1) {
      printf("Registro inexistente.\n");
    }
    else {
      printf("Número de páginas de disco para carregar o arquivo de índice: %d\n", ((totalIndices*32) / 16000)+2);
      printf("Número de páginas de disco para acessar o arquivo de dados: %d\n", sum);
    }
    if(n == 15) {
      printf("\nDiferença no número de páginas de disco acessadas: %d\n", paginasAcessadas-sum);
    }
  }

  return 0;
}
