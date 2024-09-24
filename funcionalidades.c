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

void lerRegistroCSV(FILE *arquivo_csv, Registro *registro) {
    char buffer[1000];  // Buffer temporário para strings

    // Leitura do campo 'nome'
    fscanf(arquivo_csv, "%[^,]", buffer);
    registro->nome.tamanho = strlen(buffer);
    registro->nome.valor = (char *)malloc(registro->nome.tamanho + 1);
    strcpy(registro->nome.valor, buffer);

    // Leitura do campo 'dieta'
    fscanf(arquivo_csv, ", %[^,]", buffer);
    registro->dieta.tamanho = strlen(buffer);
    registro->dieta.valor = (char *)malloc(registro->dieta.tamanho + 1);
    strcpy(registro->dieta.valor, buffer);

    // Leitura do campo 'habitat'
    fscanf(arquivo_csv, ", %[^,]", buffer);
    registro->habitat.tamanho = strlen(buffer);
    registro->habitat.valor = (char *)malloc(registro->habitat.tamanho + 1);
    strcpy(registro->habitat.valor, buffer);

    // Leitura do campo 'populacao'
    fscanf(arquivo_csv, ", %d", &registro->populacao);

    // Leitura do campo 'tipo'
    fscanf(arquivo_csv, ", %[^,]", buffer);
    registro->tipo.tamanho = strlen(buffer);
    registro->tipo.valor = (char *)malloc(registro->tipo.tamanho + 1);
    strcpy(registro->tipo.valor, buffer);

    // Leitura do campo 'velocidade'
    fscanf(arquivo_csv, ", %d", &registro->velocidade);

    // Leitura do campo 'unidadeMedida'
    fscanf(arquivo_csv, ", %c", &registro->unidadeMedida);

    // Leitura do campo 'tamanho'
    fscanf(arquivo_csv, ", %f", &registro->tamanho);

    // Leitura do campo 'especie'
    fscanf(arquivo_csv, ", %[^,]", buffer);
    registro->especie.tamanho = strlen(buffer);
    registro->especie.valor = (char *)malloc(registro->especie.tamanho + 1);
    strcpy(registro->especie.valor, buffer);

    // Leitura do campo 'alimento' sem capturar '\r' ou '\n'
    fscanf(arquivo_csv, ", %[^\r\n]", buffer);
    registro->alimento.tamanho = strlen(buffer);
    registro->alimento.valor = (char *)malloc(registro->alimento.tamanho + 1);
    strcpy(registro->alimento.valor, buffer);

    // Consumir o caractere de nova linha após o último campo
    fscanf(arquivo_csv, "%*[\r\n]");
}


void gravarRegistroBinario(FILE *arquivo_binario, Registro *registro) {
    char delimitador = '#';
    char preenchimento = '$';

    registro->removido = '0';
    registro->encadenamento = -1;

    fwrite(&registro->removido, sizeof(char), 1, arquivo_binario);
    fwrite(&registro->encadenamento, sizeof(int), 1, arquivo_binario);
    fwrite(&registro->populacao, sizeof(int), 1, arquivo_binario);
    fwrite(&registro->tamanho, sizeof(float), 1, arquivo_binario);
    fwrite(&registro->unidadeMedida, sizeof(char), 1, arquivo_binario);
    fwrite(&registro->velocidade, sizeof(int), 1, arquivo_binario);

    fwrite(registro->nome.valor, sizeof(char), registro->nome.tamanho, arquivo_binario);
    fwrite(&delimitador, sizeof(char), 1, arquivo_binario);

    fwrite(registro->especie.valor, sizeof(char), registro->especie.tamanho, arquivo_binario);
    fwrite(&delimitador, sizeof(char), 1, arquivo_binario);

    fwrite(registro->habitat.valor, sizeof(char), registro->habitat.tamanho, arquivo_binario);
    fwrite(&delimitador, sizeof(char), 1, arquivo_binario);

    fwrite(registro->tipo.valor, sizeof(char), registro->tipo.tamanho, arquivo_binario);
    fwrite(&delimitador, sizeof(char), 1, arquivo_binario);

    fwrite(registro->dieta.valor, sizeof(char), registro->dieta.tamanho, arquivo_binario);
    fwrite(&delimitador, sizeof(char), 1, arquivo_binario);

    fwrite(registro->alimento.valor, sizeof(char), registro->alimento.tamanho, arquivo_binario);

    fwrite(&delimitador, sizeof(char), 1, arquivo_binario);

    int bytesUsados = sizeof(char) + sizeof(int) * 3 + sizeof(float) + sizeof(int) +
                      registro->nome.tamanho + 1 + 
                      registro->especie.tamanho + 1 +
                      registro->habitat.tamanho + 1 +
                      registro->tipo.tamanho + 
                      registro->dieta.tamanho + 
                      registro->alimento.tamanho ;

    for (int i = 0; i < (160 - bytesUsados); i++) {
        fwrite(&preenchimento, sizeof(char), 1, arquivo_binario);
    }
}

void create_table(FILE *arquivo_binario, FILE *arquivo_csv) {
        if (!pularCabecalho(arquivo_csv)) {
        printf("Erro ao pular o cabeçalho.\n");
        return 1;
    }

    Registro registro;
    Cabecalho cabecalho;

    inicia_cabecalho(arquivo_binario, &cabecalho);

    while (!feof(arquivo_csv)) {
        lerRegistroCSV(arquivo_csv, &registro);
        gravarRegistroBinario(arquivo_binario, &registro);
        liberarRegistro(&registro);  // Libera a memória alocada para cada registro
    }

    fclose(arquivo_csv);
    fclose(arquivo_binario);

    // Exibe o tamanho do arquivo binário e o conteúdo para comparação
    binarioNaTela("saida.bin");
}