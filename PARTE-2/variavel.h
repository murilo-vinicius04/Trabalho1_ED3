#ifndef VARIAVEL
#define VARIAVEL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxiliares.h"

// essa struct representa os campos de tamanho variavel
typedef struct
{
    int tamanho;
    char *valor;
} Variavel;

// le valor variavel presente no arquivo
// versao para valor variavel do fread
void freadvar(Variavel *variavel, FILE *arquivo);

// pretende ler o campo da forma pedida na funcionalidade 3 e 4
// ou seja, precisa ler string variavel cujos separados sao o char de espaco
// e salva seu valor na variavel campo. Depois eh criado uma string variavel e
// salvo o valor encontrado nela
Variavel *readcampo();

// pretende ler o valor de um campo da forma pedida na funcionalidade 3 e 4
// ou seja, precisa ler string variavel cujos separados sao o char de "
// e salva seu valor na variavel campo. Depois eh criado uma string variavel e
// salvo o valor encontrado nela
Variavel *readvalor();

// libera memoria alocada para uma string de tamanho variavel
void free_variavel(Variavel *variavel);

#endif
