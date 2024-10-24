#ifndef AUXILIARES
#define AUXILIARES

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// recebe o ponteiro de um arquivo e le quantos bytes ele possui
int tamanho_bytes(FILE *arquivo);

// recebe o endereco de uma string que representa um campo
// e retornamos o inteiro correspondente a esse campo da seguinte forma
// campo 0: populacao (int)
// campo 1: tamanho (float)
// campo 2: unidadeMedida (char)
// campo 3: velocidade (int)
// campo 4: nome (variavel)
// campo 5: especie (variavel)
// campo 6: habitat (variavel)
// campo 7: tipo (variavel)
// campo 8: dieta (variavel)
// campo 9: alimento (variavel)
int int_campo(char *campo);

// a presente funcao recebe um string entre aspas e retorna o mesmo
// string sem aspas
char *sem_aspas(char *com_aspas);

#endif
