#ifndef CABECALHO
#define CABECALHO

#include <stdio.h>

// essa estrutura representa o registro de cabecalho
typedef struct
{
    char status;
    int topo;
    int proxRRN;
    int nroRegRem;
    int nroPagDisco;
    int qttCompacta;
} Cabecalho;

// essa funcao recebe um cabecalho e um arquivo e retorna o
// cabecalho do arquivo lido da struct cabecalho 
void le_cabecalho(Cabecalho *cabecalho, FILE *arquivo);

void printa_cabecalho(Cabecalho *cabecalho);

void escrever_cabecalho(Cabecalho *cabecalho, FILE *arquivo_binario);

void calcularNumeroPaginasDisco(Cabecalho *cabecalho);


#endif
