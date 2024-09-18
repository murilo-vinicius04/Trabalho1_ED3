#ifndef ESTRUTURAS
#define ESTRUTURAS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// essa struct representa os campos de tamanho variavel
typedef struct
{
    int tamanho;
    char *valor;
} Variavel;

// essa struct representa o registro
typedef struct
{
    int populacao;
    float tamanho;
    char unidadeMedida;
    int velocidade;
    Variavel nome;
    Variavel especie;
    Variavel habitat;
    Variavel tipo;
    Variavel dieta;
    Variavel alimento;
    char removido;
    int encadenamento;
} Registro;

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

#endif
