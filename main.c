#include <stdio.h>
#include "registro.h"
#include "funcionalidades.h"

int main()
{
    // primeiro recebemos as informacoes que precisamos
    int n;
    char binario[20], csv[20];
    scanf("%d %s %s", &n, binario, csv);

    // busca o arquivo
    FILE *arquivo_csv = fopen(csv, "r");
    FILE *arquivo_binario = fopen(binario, "wb");

    // executa funcionalidade desejada
    switch (n)
    {
        case 1:
            create_table(arquivo_binario, arquivo_csv);
            break;
        case 2:
            select_from(arquivo_binario);
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
    fclose(arquivo_binario);

    return 0;
}
