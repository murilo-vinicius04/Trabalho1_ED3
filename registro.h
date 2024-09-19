#ifndef REGISTRO
#define REGISTRO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "variavel.h"

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
    int encadenamento;      // campo 11
} Registro;

// PRIVADO
//
// A funcao removido recebe um registro e retorna true (1) se ele tiver sido logicamente
// removido ou false (0) caso contrario
int removido(Registro *registro)
{
    if (registro->removido == '1')
        return 1;
    else
        return 0;
}

// A funcao nao_nulo retorna true (1) se campo estiver nulo e false caso contrario
// cada campo sera refenciado pelo seu numero, como se fosse uma lista. Entao o campo 0
// eh a populacao, 1 o tamanho etc. Um resumo dos numeros de cada campo esta na propria struct
// acima
int nao_nulo(Registro *registro, int campo)
{
    switch (campo)
    {
        case 0:
            if (registro->populacao == -1 || registro->populacao == 0)
                return 0;
            else
                break;
        case 1:
            if (registro->tamanho == -1)
                return 0;
            else
                break;
        case 2:
            if (registro->unidadeMedida == '$')
                return 0;
            else
                break;
        case 3:
            if (registro->velocidade == -1)
                return 0;
            else
                break;
        case 4:
            if (registro->nome.tamanho == 0)
                return 0;
            else
                break;
        case 5:
            if (registro->especie.tamanho == 0)
                return 0;
            else
                break;
        case 6:
            if (registro->habitat.tamanho == 0)
                return 0;
            else
                break;
        case 7:
            if (registro->tipo.tamanho == 0)
                return 0;
            else
                break;
        case 8:
            if (registro->dieta.tamanho == 0)
                return 0;
            else
                break;
        case 9:
            if (registro->alimento.tamanho == 0)
                return 0;
            else
                break;
    }

    return 1;
}

// PUBLICO
// essa funcao recebe o ponteiro de um arquivo, o byte offset do registro,
// e o ponteiro do registro que salvara os dados
// a seguinte funcao le o registro com byteoffset do arquivo
void le_registro(Registro *registro, FILE *arquivo, int offset)
{
    // arruma o ponteiro para o inicio do registro e le os valores
    fseek(arquivo, offset, SEEK_SET);
    fread(&registro->removido, 1, 1, arquivo);
    fread(&registro->encadenamento, 4, 1, arquivo);
    // toda especie precisa ter um nome valido, salvamos posicao e vemos se especie comeca com $
    offset = ftell(arquivo);
    if (fgetc(arquivo) == '$')
        return;
    fseek(arquivo, offset, SEEK_SET); 
    fread(&registro->especie, 4, 1, arquivo);
    fread(&registro->tamanho, 4, 1, arquivo);
    fread(&registro->unidadeMedida, 1, 1, arquivo);
    fread(&registro->velocidade, 4, 1, arquivo);
    freadvar(&registro->nome, arquivo);
    freadvar(&registro->especie, arquivo);
    freadvar(&registro->habitat, arquivo);        
    freadvar(&registro->tipo, arquivo);
    freadvar(&registro->dieta, arquivo);
    freadvar(&registro->alimento, arquivo);
}

// a seguinte funcao recebe um registro e printa suas informacoes de forma formatada
void printa_formatado(Registro *registro)
{
    if (nao_nulo(registro, 4))
        printf("Nome: %s\n", registro->nome.valor);
    if (nao_nulo(registro, 5))
        printf("Especie: %s\n", registro->especie.valor);
    if (nao_nulo(registro, 7))
        printf("Tipo: %s\n", registro->tipo.valor);
    if (nao_nulo(registro, 8))
        printf("Dieta: %s\n", registro->dieta.valor);
    if (nao_nulo(registro, 9))
        printf("Alimento: %s\n", registro->alimento.valor);
    if (nao_nulo(registro, 6))
        printf("Lugar que habitava: %s\n", registro->habitat.valor);
    if (nao_nulo(registro, 0))
        printf("Populacao: %d\n", registro->populacao);
    if (nao_nulo(registro, 1))
        printf("Tamanho: %.1f m\n", registro->tamanho);
    if (nao_nulo(registro, 2) && nao_nulo(registro, 3))
        printf("Velocidade: %d %cm/h\n", registro->velocidade, registro->unidadeMedida);
}

// essa funcao recebe o ponteiro desse registro e libera ele
void libera_registro(Registro *registro)
{
    free(registro->nome.valor);
    free(registro->especie.valor);
    free(registro->habitat.valor);
    free(registro->tipo.valor);
    free(registro->dieta.valor);
    free(registro->alimento.valor);
    free(registro);
}

#endif
