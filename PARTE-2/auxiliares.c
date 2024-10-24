#include "auxiliares.h" 

// recebe o ponteiro de um arquivo e le quantos bytes ele possui
int tamanho_bytes(FILE *arquivo)
{
    fseek(arquivo, 0, SEEK_END);
    return ftell(arquivo);
}

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
int int_campo(char *campo)
{
    // soh populacao comeca com p
    if (campo[0] == 'p')
        return 0;
    // soh unidadeMedida comeca com u
    else if (campo[0] == 'u')
        return 2;
    // soh velocidade comeca com v
    else if (campo[0] == 'v')
        return 3;
    // soh nome comeca com n
    else if (campo[0] == 'n')
        return 4;
    // soh especie comeca com e
    else if (campo[0] == 'e')
        return 5;
    // soh habitat comeca com h
    else if (campo[0] == 'h')
        return 6;
    // soh dieta comeca com d
    else if (campo[0] == 'd')
        return 8;
    // soh alimento comeca com a
    else if (campo[0] == 'a')
        return 9;
    // soh faltam tamanho e tipo, o que faz que a segunda letra
    // defina qual eh qual
    // no caso, tamanho possui segunda letra a
    else if (campo[1] == 'a')
        return 1;
    // de resto soh pode ser tipo
    else
        return 7;
}

// a presente funcao recebe um string entre aspas e retorna o mesmo
// string sem aspas
char *sem_aspas(char *com_aspas)
{
    // o tamanho sem aspas sera o tamanho com aspas -2
    int tamanho = strlen(com_aspas) - 2;
    char *_sem_aspas = (char *)malloc(tamanho*sizeof(char));
    strncpy(_sem_aspas, com_aspas+1, tamanho);
    return _sem_aspas;
}
