#include "cabecalho.h"

// essa funcao recebe um cabecalho e um arquivo e retorna o
// cabecalho do arquivo lido da struct cabecalho 
void le_cabecalho(Cabecalho *cabecalho, FILE *arquivo)
{
    fseek(arquivo, 0, SEEK_SET);
    fread(&cabecalho->status, 1, 1, arquivo);
    fread(&cabecalho->topo, 4, 1, arquivo);
    fread(&cabecalho->proxRRN, 4, 1, arquivo);
    fread(&cabecalho->nroRegRem, 4, 1, arquivo);
    fread(&cabecalho->nroPagDisco, 4, 1, arquivo);
    fread(&cabecalho->qttCompacta, 4, 1, arquivo);
}

void printa_cabecalho(Cabecalho *cabecalho)
{
    printf("status: %c\n", cabecalho->status);
    printf("topo: %d\n", cabecalho->topo);
    printf("proxRRN: %d\n", cabecalho->proxRRN);
    printf("nroRegRem: %d\n", cabecalho->nroRegRem);
    printf("nroPagDisco: %d\n", cabecalho->nroPagDisco);
    printf("qttCompacta: %d\n", cabecalho->qttCompacta);
}

void escrever_cabecalho(Cabecalho *cabecalho, FILE *arquivo_binario) {
    fseek(arquivo_binario, 0, SEEK_SET);
    fwrite(&cabecalho->status, sizeof(char), 1, arquivo_binario);
    fwrite(&cabecalho->topo, sizeof(int), 1, arquivo_binario);
    fwrite(&cabecalho->proxRRN, sizeof(int), 1, arquivo_binario);
    fwrite(&cabecalho->nroRegRem, sizeof(int), 1, arquivo_binario);
    fwrite(&cabecalho->nroPagDisco, sizeof(int), 1, arquivo_binario);
    fwrite(&cabecalho->qttCompacta, sizeof(int), 1, arquivo_binario);
}

void calcularNumeroPaginasDisco(Cabecalho *cabecalho) {
    int totalBytes = 1600 + (cabecalho->proxRRN * 160); // 1600 bytes do cabeçalho + registros
    cabecalho->nroPagDisco = totalBytes / 1600;
    if (totalBytes % 1600 != 0) {
        cabecalho->nroPagDisco++; // Se houver bytes sobrando, conta como mais uma página
    }
}