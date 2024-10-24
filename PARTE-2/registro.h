#ifndef REGISTRO
#define REGISTRO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "variavel.h"
#include "cabecalho.h"

// essa struct representa o registro
typedef struct
{
    int populacao;          // campo 0
    float tamanho;          // campo 1
    char unidadeMedida;     // campo 2
    int velocidade;         // campo 3
    Variavel nome;          // campo 4
    Variavel especie;       // campo 5
    Variavel habitat;       // campo 6
    Variavel tipo;          // campo 7
    Variavel dieta;         // campo 8
    Variavel alimento;      // campo 9
    char removido;          // campo 10
    int encadeamento;      // campo 11
} Registro;


///////////////////////////////////////////////////////////////////////////////////
// PRIVADO /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

// A funcao removido recebe um registro e retorna true (1) se ele tiver sido logicamente
// removido ou false (0) caso contrario
int removido(Registro *registro);

// A funcao nao_nulo retorna true (1) se campo estiver nulo e false caso contrario
// cada campo sera refenciado pelo seu numero, como se fosse uma lista. Entao o campo 0
// eh a populacao, 1 o tamanho etc. Um resumo dos numeros de cada campo esta na propria struct
// acima
int nao_nulo(Registro *registro, int campo);

// a funcao busca_int_printa vai buscar o int valor do respectivo int campo no FILE *arquivo
// printar os registros encontrados
// Se encontrar algum registro retorna 1, senao retorna 0
int busca_int_printa(FILE *arquivo, int campo, int valor);

// a funcao busca_float_printa vai buscar o float valor do cmpo tamanho (unico que tem float)
// int campo no FILE *arquivo e printar os registros encontrados
// Retorna 1 se encontrou algum arquivo, senao retorna 0
int busca_float_printa(FILE *arquivo, float valor);

// a funcao busca_str_printa vai buscar o string valor do respectivo int campo no FILE *arquivo
// printar os registros encontrados
// retorna 1 se encontrou algum registro e 0 caso contrario
int busca_str_printa(FILE *arquivo, int campo, char *valor);

// o codigo realmente novo eh o remove()
// ele vai receber o arquivo e o byte offset do registro a ser removido, a partir
// disso vamos realizar a remocao logica desse arquivo
void remove_especie(FILE *arquivo, Cabecalho *cabeca, int offset);

// eh o equivalente ao busca_int_printa mas ao inves de printar, remove ele logicamente
void busca_int_retira(FILE *arquivo, Cabecalho *cabeca, int campo, int valor);   

// eh o equivalente ao busca_float_printa mas ao inves de printar, remove ele logicamente
void busca_float_retira(FILE *arquivo, Cabecalho *cabeca, float valor);   

// eh o equivalente ao busca_str_printa mas ao inves de printar, remove ele logicamente
void busca_str_retira(FILE *arquivo, Cabecalho *cabeca, int campo, char *valor);   

///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
// PUBLICO /////////////////////////////////////////////////////////////

// essa funcao recebe o ponteiro de um arquivo, o byte offset do registro,
// e o ponteiro do registro que salvara os dados
// a seguinte funcao le o registro com byteoffset do arquivo
void le_registro(Registro *registro, FILE *arquivo, int offset);

// a seguinte funcao recebe um registro e printa suas informacoes de forma formatada
void printa_formatado(Registro *registro);

// essa funcao recebe o ponteiro desse registro e libera ele
void libera_registro(Registro *registro);

// a seguinte funcao vai buscar no arquivo o registro que possui o campo com o valor
// especificado e vai printar todos os registros cujos valores baterem
void busca_e_printa(FILE *arquivo, int campo, char *valor);

// a seguinte funcao vai buscar no arquivo o registro que possui o campo com o valor
// especificado e vai remove-los logicamente, ou seja, vai marca-lo como logicamente
// removivel e o rrn do proximo na pilha e vai marcar com lixo '$' em todo o resto
void busca_e_retira(FILE *arquivo, Cabecalho *cabeca, int campo, char *valor);

void escreve_registro(FILE *arquivo_binario, Registro *registro);
///////////////////////////////////////////////////////////////////////////////////

#endif
