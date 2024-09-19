#include "auxiliares.h"
#include "cabecalho.h"
#include "registro.h"

// a funcao recebe ponteiro de arquivo e printa suas informacoes da forma formatada
void select_from(FILE *arquivo)
{
    // alocamos a memoria do registro temporario e do cabecalho
    Registro *registro_temporario = (Registro *)malloc(sizeof(Registro));
    Cabecalho *cabecalho = (Cabecalho *)malloc(sizeof(Cabecalho));

    // primeiro abrimos o arquivo e contamos o numero de registros
    int tamanho = tamanho_bytes(arquivo);

    // lemos o cabecalho do arquivo
    le_cabecalho(cabecalho, arquivo);

    // pegamos as informacoes e printamos
    for (int offset = 1600; offset < tamanho; offset += 160)
    {
        le_registro(registro_temporario, arquivo, offset);
        if (!removido(registro_temporario))
        {
            printa_formatado(registro_temporario);
            printf("\n");
        }
    }

    // printamos numero de paginas
    printf("Numero de paginas de disco: %d\n", cabecalho->nroPagDisco);

    // por fim libera o registro temporario
    libera_registro(registro_temporario);
    free(cabecalho);
}
