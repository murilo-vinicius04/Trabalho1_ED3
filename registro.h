#ifndef REGISTRO
#define REGISTRO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// essa struct representa os campos de tamanho variavel
typedef struct
{
    int tamanho;
    char *valor;
} Variavel;

// le valor variavel presente no arquivo
// versao para valor variavel do fread
void freadvar(Variavel string, FILE *arquivo)
{
    // comeca contando quantidade de char q tem o string
    int i = 0;
    while (fgetc(arquivo) != '#')
        i++;
    string.tamanho = i;
    // volta para onde estava inicialmente
    arquivo -= i;
    fread(string.valor, 1, i, arquivo);
}

// essa struct representa o registro
typedef struct
{
    int populacao;
    float tamanho;
    char unidadeMedida;
    int velocidade;
    Variavel nome;
    Variavel especie;
    Variavel habitat;
    Variavel tipo;
    Variavel dieta;
    Variavel alimento;
    char removido;
    int encadenamento;
} Registro;

// essa funcao recebe o ponteiro de um arquivo, o byte offset do registro,
// e o ponteiro do registro que salvara os dados
// a seguinte funcao le o registro com byteoffset do arquivo
void le_registro(Registro *registro, FILE *arquivo, int offset)
{
    // arruma o ponteiro para o inicio do registro e le os valores
    fseek(arquivo, offset, SEEK_SET);
    fread(&registro->especie, 4, 1, arquivo);
    fread(&registro->tamanho, 4, 1, arquivo);
    fread(&registro->unidadeMedida, 1, 1, arquivo);
    fread(&registro->velocidade, 4, 1, arquivo);
    freadvar(registro->nome, arquivo);
    freadvar(registro->especie, arquivo);
    freadvar(registro->habitat, arquivo);
    freadvar(registro->tipo, arquivo);
    freadvar(registro->dieta, arquivo);
    freadvar(registro->alimento, arquivo);
    fread(&registro->removido, 1, 1, arquivo);
    fread(&registro->encadenamento, 4, 1, arquivo);
}

// a seguinte funcao recebe um registro e printa suas informacoes de forma formatada
void printa_formatado(Registro *registro)
{
    printf("Nome: %d\n", registro->especie);
    printf("Especie: %s\n", registro->nome);
    printf("Tipo: %s\n", registro->nome_cientifico);
    printf("Dieta: %d\n", registro->populacao);
    printf("Lugar que habitava: %s\n", registro->status);
    printf("Tamanho: %.1f m\n", registro->localizacao[0], registro->localizacao[1]);
    printf("Velocidade: %d %cm/h\n", registro->impacto_humano);
}

#endif
