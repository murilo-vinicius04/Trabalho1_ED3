#include <stdio.h>

// recebe o ponteiro de um arquivo e le quantos bytes ele possui
int tamanho_bytes(FILE *arquivo)
{
    fseek(arquivo, 0, SEEK_END);
    return ftell(arquivo);
}
