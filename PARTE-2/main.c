// Pedro Fuziwara Filho - 13676840 - Função 7 (100% do esperado)
// Murilo Vinicius da Silva - 14600030 - Função 8 (50% do esperado)

#include <stdio.h>
#include "funcionalidades.h"
#include "funcoes_fornecidas.h"

int main()
{
    // primeiro recebemos as informações que precisamos
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
            select_where(arquivo);
            break;
        case 4:
            remocao_logica(arquivo);
            binarioNaTela(nome);
            break;
        case 5:
            insert_into(arquivo);
            binarioNaTela(nome);
            break;
        case 6:
            break;
        case 7:
            create_index(arquivo);
            break;
        case 8:
            // Chama a função de busca (modularizada)
            busca_nome(arquivo);  // Aqui pode usar os arquivos de dados e índice
            break;
        default:
            printf("Funcionalidade inválida.\n");
            break;
    }

    // fecha o arquivo
    fclose(arquivo);

    return 0;
}
