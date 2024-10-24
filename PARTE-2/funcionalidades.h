#ifndef FUNCIONALIDADES
#define FUNCIONALIDADES

#include "auxiliares.h"
#include "cabecalho.h"
#include "registro.h"
#include "fila.h"
#include "arvore_b.h"
#include "funcoes_fornecidas.h"

// representa a funcionalidade (2) do trabalho
void select_from(FILE *arquivo);
// representa a funcionalidade (3) do trabalho
void select_where(FILE* arquivo);
// representa a funcionalidade (4) do trabalho
void remocao_logica(FILE *arquivo);
// representa a funcionalidade (7) do trabalho
void create_index(FILE *arquivo);
// representa a funcionalidade (8) do trabalho

void insercao(FILE *arquivo_binario, int n);

void insert_into(FILE *arquivo_binario);

void busca_nome(FILE *dados);

#endif
