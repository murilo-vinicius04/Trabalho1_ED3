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

#endif
