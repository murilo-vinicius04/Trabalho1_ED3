#include <stdio.h>
#include "registro.h"
#include "funcionalidades.h"

int main()
{
    // primeiro recebemos as informacoes que precisamos
    int n;
    char nome[20];
    scanf("%d %s", &n, nome);

    // busca o arquivo
    FILE *arquivo = fopen(nome, "r+");
    if (arquivo == NULL)
    {
        printf("Falha no processamento do arquivo\n");
        return 1;
    }

    // executa funcionalidade desejada
    switch (n)
    {
        case 1:
            break;
        case 2:
            select_from(arquivo);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
    }

    // fecha o arquivo
    fclose(arquivo);

    return 0;
}
