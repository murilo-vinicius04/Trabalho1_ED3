#ifndef FUNCIONALIDADES
#define FUNCIONALIDADES

#include <stdio.h>
#include "funcionalidades.c"

void select_from(FILE *arquivo);
void lerRegistroCSV(FILE *arquivo_csv, Registro *registro);
void gravarRegistroBinario(FILE *arquivo_binario, Registro *registro);

#endif
