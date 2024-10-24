// Pedro Fuziwara Filho - 13676840
// Murilo Vinicius da Silva - 14600030

#ifndef ARVORE_B
#define ARBORE_B

#include <stdio.h>
#include <stdlib.h>

// algumas contantes para deixar o codigo mais legivel
#define ORDEM 5
#define MAX_CHAVE (ORDEM - 1)
#define MIN_CHAVE (ORDEM/2 - 1)
#define TAMANHO_REGISTRO 93
#define NIL -1
#define PROMOCAO 1
#define SEM_PROMOCAO 0
#define ERRO -1

// representa o cabecalho do arquivo com o indice arvore b
typedef struct 
{
    char status;
    int noRaiz;
    int RRNproxNo;
} Cabecalho_indice;

// representa cada no da arvore b
typedef struct
{
    char folha;
    int nroChavesIndexadas;
    int RRNdoNo;
    int filho[ORDEM];      // o ponteiro dos filhos sao seus RRNs
    long valor[MAX_CHAVE];
    long referencia[MAX_CHAVE];   // a referencia ao arquivo de dados eh atraves dos seus byte offset no arquivo de dados
} No_indice;

// cria cabecalho_indice com tudo inicializado
Cabecalho_indice *cria_cabecalho_indice();

// escreve o cabecalho no arquivo
void escreve_cabecalho_indice(FILE *arquivo, Cabecalho_indice *cabecalho);

// escreve o no no arquivo
void escreve_no_indice(FILE *arquivo, No_indice *no);

// le no a partir de um rrn
void le_no_indice(FILE *arquivo, int rrn, No_indice *no);

// cria no ja inicializado
No_indice *cria_no_indice(Cabecalho_indice *cabecalho);

// vai separar no em dois void separa_no_indice(FILE *arquivo, long chave_nova, long referencia_nova, int filho_novo, No_indice *no, long *chave, long *referencia, int *filho, No_indice *novo_no, Cabecalho_indice *cabecalho);
void separa_no_indice(FILE *arquivo, long chave_nova, long referencia_nova, int filho_novo, No_indice *no, long *chave, long *referencia, int *filho, No_indice *novo_no, Cabecalho_indice *cabecalho);

// caso a arvore b nao tenha sua raiz cheia, vamos inserir a chave
int insere_chave(FILE *arquivo, int RRNatual, long chave, long offset, long *chave_promovida, long *referencia_promovida, int *filho_direito, Cabecalho_indice *cabecalho);

// insere chave e referencia na arvore b
void insere_arvore_b(FILE *arquivo, Cabecalho_indice *cabecalho, long chave, long offset);
long buscarIndiceArvore(FILE *arquivo, int rrnAtual, long chaveBusca);
void le_cabecalho_indice(FILE *arquivoIndice, Cabecalho_indice *cabecalho);

#endif
