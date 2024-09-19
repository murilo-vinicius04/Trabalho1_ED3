#include "registro.h"
#include "auxiliares.h"

// a funcao recebe ponteiro de arquivo e printa suas informacoes da forma formatada
void select_from(FILE *arquivo)
{
    // Primeiro abrimos o arquivo e lemos primeiro registro
    Registro *registro_temporario = (Registro *)malloc(sizeof(Registro));

    // primeiro abrimos o arquivo e contamos o numero de registros
    int tamanho = tamanho_bytes(arquivo);

    // por fim, pegamos as informacoes e printamos
    for (int offset = 0; offset < tamanho; offset += 160)
    {
        le_registro(registro_temporario, arquivo, offset);
        printa_formatado(registro_temporario);
    }

    // por fim libera o registro temporario
    free(registro_temporario);
}
