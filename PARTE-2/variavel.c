#include "variavel.h"

// le valor variavel presente no arquivo
// versao para valor variavel do fread
void freadvar(Variavel *variavel, FILE *arquivo)
{
    // salva posicao original
    long inicio = ftell(arquivo);
    // comeca contando quantidade de char q tem o string
    int i = 0;
    while (fgetc(arquivo) != '#')
        i++;
    variavel->tamanho = i;
    variavel->valor = (char *)malloc(i*sizeof(char));
    // volta para onde estava inicialmente e le string
    fseek(arquivo, inicio, SEEK_SET);
    fread(variavel->valor, 1, i, arquivo);
    fgetc(arquivo);     // recebe o caracter # delimitador
}

// libera o espaco alocado a uma string de tamanho variavel
void free_variavel(Variavel *variavel)
{
    free(variavel->valor);
    free(variavel);
}
