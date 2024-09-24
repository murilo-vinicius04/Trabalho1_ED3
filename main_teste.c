#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "variavel.h"
#include "registro.h"
#include "cabecalho.h"

void binarioNaTela(char *nomeArquivoBinario) { /* Código dado no enunciado */
	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
}

int pularCabecalho(FILE *arquivo_csv) {
    char buffer[1000];  // Buffer temporário para armazenar o cabeçalho
    if (fgets(buffer, sizeof(buffer), arquivo_csv) != NULL) {
        return 1;  // Cabeçalho lido e pulado com sucesso
    }
    return 0;  // Erro ao ler o cabeçalho
}

void lerRegistroCSV(FILE *arquivo_csv, Registro *registro) {
    char buffer[1000];  // Buffer temporário para strings

    // Leitura do campo 'nome'
    fscanf(arquivo_csv, "%[^,]", buffer);
    registro->nome.tamanho = strlen(buffer);
    registro->nome.valor = (char *)malloc(registro->nome.tamanho + 1);
    strcpy(registro->nome.valor, buffer);

    // Leitura do campo 'dieta'
    fscanf(arquivo_csv, ", %[^,]", buffer);
    registro->dieta.tamanho = strlen(buffer);
    registro->dieta.valor = (char *)malloc(registro->dieta.tamanho + 1);
    strcpy(registro->dieta.valor, buffer);

    // Leitura do campo 'habitat'
    fscanf(arquivo_csv, ", %[^,]", buffer);
    registro->habitat.tamanho = strlen(buffer);
    registro->habitat.valor = (char *)malloc(registro->habitat.tamanho + 1);
    strcpy(registro->habitat.valor, buffer);

    // Leitura do campo 'populacao'
    fscanf(arquivo_csv, ", %d", &registro->populacao);

    // Leitura do campo 'tipo'
    fscanf(arquivo_csv, ", %[^,]", buffer);
    registro->tipo.tamanho = strlen(buffer);
    registro->tipo.valor = (char *)malloc(registro->tipo.tamanho + 1);
    strcpy(registro->tipo.valor, buffer);

    // Leitura do campo 'velocidade'
    fscanf(arquivo_csv, ", %d", &registro->velocidade);

    // Leitura do campo 'unidadeMedida'
    fscanf(arquivo_csv, ", %c", &registro->unidadeMedida);

    // Leitura do campo 'tamanho'
    fscanf(arquivo_csv, ", %f", &registro->tamanho);

    // Leitura do campo 'especie'
    fscanf(arquivo_csv, ", %[^,]", buffer);
    registro->especie.tamanho = strlen(buffer);
    registro->especie.valor = (char *)malloc(registro->especie.tamanho + 1);
    strcpy(registro->especie.valor, buffer);

    // Leitura do campo 'alimento' sem capturar '\r' ou '\n'
    fscanf(arquivo_csv, ", %[^\r\n]", buffer);
    registro->alimento.tamanho = strlen(buffer);
    registro->alimento.valor = (char *)malloc(registro->alimento.tamanho + 1);
    strcpy(registro->alimento.valor, buffer);

    // Consumir o caractere de nova linha após o último campo
    fscanf(arquivo_csv, "%*[\r\n]");
}



void gravarRegistroBinario(FILE *arquivo_binario, Registro *registro) {
    char delimitador = '#';
    char preenchimento = '$';

    registro->removido = '0';
    registro->encadenamento = -1;

    fwrite(&registro->removido, sizeof(char), 1, arquivo_binario);
    fwrite(&registro->encadenamento, sizeof(int), 1, arquivo_binario);
    fwrite(&registro->populacao, sizeof(int), 1, arquivo_binario);
    fwrite(&registro->tamanho, sizeof(float), 1, arquivo_binario);
    fwrite(&registro->unidadeMedida, sizeof(char), 1, arquivo_binario);
    fwrite(&registro->velocidade, sizeof(int), 1, arquivo_binario);

    fwrite(registro->nome.valor, sizeof(char), registro->nome.tamanho, arquivo_binario);
    fwrite(&delimitador, sizeof(char), 1, arquivo_binario);

    fwrite(registro->especie.valor, sizeof(char), registro->especie.tamanho, arquivo_binario);
    fwrite(&delimitador, sizeof(char), 1, arquivo_binario);

    fwrite(registro->habitat.valor, sizeof(char), registro->habitat.tamanho, arquivo_binario);
    fwrite(&delimitador, sizeof(char), 1, arquivo_binario);

    fwrite(registro->tipo.valor, sizeof(char), registro->tipo.tamanho, arquivo_binario);
    fwrite(&delimitador, sizeof(char), 1, arquivo_binario);

    fwrite(registro->dieta.valor, sizeof(char), registro->dieta.tamanho, arquivo_binario);
    fwrite(&delimitador, sizeof(char), 1, arquivo_binario);

    fwrite(registro->alimento.valor, sizeof(char), registro->alimento.tamanho, arquivo_binario);

    fwrite(&delimitador, sizeof(char), 1, arquivo_binario);

    int bytesUsados = sizeof(char) + sizeof(int) * 3 + sizeof(float) + sizeof(int) +
                      registro->nome.tamanho + 1 + 
                      registro->especie.tamanho + 1 +
                      registro->habitat.tamanho + 1 +
                      registro->tipo.tamanho + 
                      registro->dieta.tamanho + 
                      registro->alimento.tamanho ;

    for (int i = 0; i < (160 - bytesUsados); i++) {
        fwrite(&preenchimento, sizeof(char), 1, arquivo_binario);
    }
}

void inicia_cabecalho(FILE *arquivo_binario, Cabecalho *cabecalho){
    cabecalho->status = '1';
    cabecalho->topo = -1;
    cabecalho->proxRRN = 0;
    cabecalho->nroRegRem = 0;
    cabecalho->nroPagDisco = 0;
    cabecalho->qttCompacta = 0;

    // Escrever os campos do cabeçalho
    fwrite(&cabecalho->status, sizeof(char), 1, arquivo_binario);
    fwrite(&cabecalho->topo, sizeof(int), 1, arquivo_binario);
    fwrite(&cabecalho->proxRRN, sizeof(int), 1, arquivo_binario);
    fwrite(&cabecalho->nroRegRem, sizeof(int), 1, arquivo_binario);
    fwrite(&cabecalho->nroPagDisco, sizeof(int), 1, arquivo_binario);
    fwrite(&cabecalho->qttCompacta, sizeof(int), 1, arquivo_binario);

    // Preencher o restante da página de disco (1600 bytes) com '$'
    char preenchimento = '$';

    for (int i = 21; i < 1600; i++) {
        fwrite(&preenchimento, sizeof(char), 1, arquivo_binario);
    }
}

void liberarRegistro(Registro *registro) {
    free(registro->nome.valor);
    free(registro->especie.valor);
    free(registro->habitat.valor);
    free(registro->tipo.valor);
    free(registro->dieta.valor);
    free(registro->alimento.valor);
}

int main() {
    FILE *arquivo_csv = fopen("dados1.csv", "r");
    FILE *arquivo_binario = fopen("saida.bin", "wb");

    if (!arquivo_csv || !arquivo_binario) {
        printf("Erro ao abrir arquivos.\n");
        return 1;
    }

    // Pular o cabeçalho do CSV
    if (!pularCabecalho(arquivo_csv)) {
        printf("Erro ao pular o cabeçalho.\n");
        return 1;
    }

    Registro registro;
    Cabecalho cabecalho;

    inicia_cabecalho(arquivo_binario, &cabecalho);

    while (!feof(arquivo_csv)) {
        lerRegistroCSV(arquivo_csv, &registro);
        gravarRegistroBinario(arquivo_binario, &registro);
        liberarRegistro(&registro);  // Libera a memória alocada para cada registro
    }

    fclose(arquivo_csv);
    fclose(arquivo_binario);

    // Exibe o tamanho do arquivo binário e o conteúdo para comparação
    binarioNaTela("saida.bin");

    return 0;
}
