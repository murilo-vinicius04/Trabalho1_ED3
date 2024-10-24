#include "funcionalidades.h"


// a funcao recebe ponteiro de arquivo e printa suas informacoes da forma formatada
// representa a funcionalidade (2) do trabalho
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
            printf("numero de %s eh %ld\n", registro_temporario->nome.valor, converteNome(registro_temporario->nome.valor));
            printf("\n");
        }
    }

    // printamos numero de paginas
    printf("Numero de paginas de disco: %d\n\n", cabecalho->nroPagDisco);

    // por fim libera o registro temporario
    libera_registro(registro_temporario);
    free(cabecalho);
}

// a funcao recebe um arquivo e pede o comando "where" do SQL com o numero n de
// criterios e depois o nome do campo e seu valor, que devem vir do usuario.
// A funcao printa na tela os registros que conterem os campos com os valores
// pedidos.
// select_where representa a funcionalidade (3) do trabalho
void select_where(FILE* arquivo)
{
    // vamos primeiro receber a fila
    // precisamos receber o n para saber quantos criterios de selecao vao ter
    int n;
    scanf(" %d", &n);
    // depois precisamos receber a entrada e separar a string nos espacos
    char entrada[25*n];
    fgets(entrada, sizeof(entrada), stdin);
    // vamos criar uma fila
    Fila *fila = cria_fila();
    // vamos tokenizar separando pelos espacos " "
    No *no = (No *)malloc(sizeof(No));
    no->campo = strtok(entrada, " ");
    no->valor = strtok(NULL, " ");
    poe_na_fila(fila, no);
    for (int i = 1; i < n; i++)
    {
        No *no = (No *)malloc(sizeof(No));
        no->campo = strtok(NULL, " ");
        no->valor = strtok(NULL, " ");
        poe_na_fila(fila, no);
    }

    // agora vamos nos preparar para ler os dados do arquivo
    // alocamos a memoria do cabecalho
    Cabecalho *cabecalho = (Cabecalho *)malloc(sizeof(Cabecalho));
    // lemos o cabecalho do arquivo
    le_cabecalho(cabecalho, arquivo);
  
    // iteramos sobre cada busca 
    int campo;
    for (int i = 0; i < n; i++)
    {
        printf("Busca %d\n", i+1);
        // vamos receber o numero do campo para conseguir fazer a busca
        campo = int_campo(fila->cabeca->campo);
        // se encontramos algo printamos
        busca_e_printa(arquivo, campo, fila->cabeca->valor);
        // a cabeca da fila se torna o proximo da antiga cabeca e liberamos aquele
        // no
        proximo_na_fila(fila);
        // printamos numero de paginas
        printf("\nNumero de paginas de disco: %d\n\n", cabecalho->nroPagDisco);
    }

    // precisamos liberar o cabecalho
    free(cabecalho);
}

// a funcao recebe um arquivo e executa a funcionalidade (4) do trabalho, que eh
// a remocao logica de registros
// Para isso, a funcao vai perguntar quantas buscas e remocoes serao feitas e
// depois os campos e valores como especificado pelo trabalho
void remocao_logica(FILE *arquivo)
{
    // perceba que aqui, no fundamental, apenas recebemos os criterios de remocao
    // o que faz o codigo ser igual ao do select_where porque a forma como estamos
    // recebendo eh igual, a unica mudanca eh o busca_e_ que passa a ser retira 
    // ao inves de printa, o que tambem faz a formatacao da saida ser diferente

    // vamos primeiro receber a fila
    // precisamos receber o n para saber quantos criterios de selecao vao ter
    int n;
    scanf(" %d", &n);
    // depois precisamos receber a entrada e separar a string nos espacos
    char entrada[25*n];
    fgets(entrada, sizeof(entrada), stdin);
    // vamos criar uma fila
    Fila *fila = cria_fila();
    // vamos tokenizar separando pelos espacos " "
    No *no = (No *)malloc(sizeof(No));
    no->campo = strtok(entrada, " ");   // trocar por strsep dps, da pau por causa do csv
    no->valor = strtok(NULL, " ");
    poe_na_fila(fila, no);
    for (int i = 1; i < n; i++)
    {
        No *no = (No *)malloc(sizeof(No));
        no->campo = strtok(NULL, " ");
        no->valor = strtok(NULL, " ");
        poe_na_fila(fila, no);
    }

    // agora vamos nos preparar para ler os dados do arquivo
    // alocamos a memoria do cabecalho
    Cabecalho *cabecalho = (Cabecalho *)malloc(sizeof(Cabecalho));
    // lemos o cabecalho do arquivo
    le_cabecalho(cabecalho, arquivo);
  
    // iteramos sobre cada busca 
    int campo;
    for (int i = 0; i < n; i++)
    {
        // vamos receber o numero do campo para conseguir fazer a busca
        campo = int_campo(fila->cabeca->campo);
        // AQUI QUE O CODIGO DEIXA DE SER IGUAL AO DO SELECT_WHERE
        busca_e_retira(arquivo, cabecalho, campo, fila->cabeca->valor);
        // a cabeca da fila se torna o proximo da antiga cabeca e liberamos aquele
        // no
        proximo_na_fila(fila);
    }

    // precisamos liberar o cabecalho
    free(cabecalho);
}
void insercao(FILE *arquivo, int qtd){
    // inicializa o status para '0'
    char status = '0';
    if(status != '0' && status != '1'){     // validação do status
        printf("Falha no processamento do arquivo.\n");
        // fecha o arquivo antes de retornar
        return;               // mudança não realizada
    }

    // lê o cabeçalho inicialmente
    Cabecalho cabecalho;
    le_cabecalho(&cabecalho, arquivo);

    // verifica se o arquivo já está inconsistente
    if(status == '0' && cabecalho.status == '0'){ 
        printf("Falha no processamento do arquivo.\n");
        // fecha o arquivo antes de retornar
        return;               // mudança não realizada
    }

    // atualiza o status no cabeçalho
    cabecalho.status = status;
    escrever_cabecalho(&cabecalho, arquivo); 
    // fim da desmodularização de atualiza_status

    Registro registro;
    char str[50];

    for(int i = 0; i < qtd; i++){
        // leitura dos campos do novo registro

        // leitura e alocação de registro.nome
        scan_quote_string(str);
        if (strcmp(str, "") == 0) {
            registro.nome.tamanho = 0;
            registro.nome.valor = NULL;
        } else {
            registro.nome.tamanho = strlen(str);
            registro.nome.valor = malloc((registro.nome.tamanho + 1) * sizeof(char));
            if (registro.nome.valor == NULL) {
                fprintf(stderr, "Erro de alocação de memória.\n");
                // fecha o arquivo antes de sair
                exit(1);
            }
            strcpy(registro.nome.valor, str);
        }

        // leitura e alocação de registro.dieta
        scan_quote_string(str);
        if (strcmp(str, "") == 0) {
            registro.dieta.tamanho = 0;
            registro.dieta.valor = NULL;
        } else {
            registro.dieta.tamanho = strlen(str);
            registro.dieta.valor = malloc((registro.dieta.tamanho + 1) * sizeof(char));
            if (registro.dieta.valor == NULL) {
                fprintf(stderr, "Erro de alocação de memória.\n");
                // fecha o arquivo antes de sair
                exit(1);
            }
            strcpy(registro.dieta.valor, str);
        }

        // leitura e alocação de registro.habitat
        scan_quote_string(str);
        if (strcmp(str, "") == 0) {
            registro.habitat.tamanho = 0;
            registro.habitat.valor = NULL;
        } else {
            registro.habitat.tamanho = strlen(str);
            registro.habitat.valor = malloc((registro.habitat.tamanho + 1) * sizeof(char));
            if (registro.habitat.valor == NULL) {
                fprintf(stderr, "Erro de alocação de memória.\n");
                // fecha o arquivo antes de sair
                exit(1);
            }
            strcpy(registro.habitat.valor, str);
        }

        // leitura de registro.populacao
        scan_quote_string(str);
        if (strcmp(str, "") == 0) {
            registro.populacao = -1; // valor nulo
        } else {
            registro.populacao = atoi(str);
        }

        // leitura e alocação de registro.tipo
        scan_quote_string(str);
        if (strcmp(str, "") == 0) {
            registro.tipo.tamanho = 0;
            registro.tipo.valor = NULL;
        } else {
            registro.tipo.tamanho = strlen(str);
            registro.tipo.valor = malloc((registro.tipo.tamanho + 1) * sizeof(char));
            if (registro.tipo.valor == NULL) {
                fprintf(stderr, "Erro de alocação de memória.\n");
                // fecha o arquivo antes de sair
                exit(1);
            }
            strcpy(registro.tipo.valor, str);
        }

        // leitura de registro.velocidade
        scan_quote_string(str);
        if (strcmp(str, "") == 0) {
            registro.velocidade = -1; // valor nulo
        } else {
            registro.velocidade = atoi(str);
        }

        // leitura de registro.unidadeMedida
        scan_quote_string(str);
        if (strcmp(str, "") == 0) {
            registro.unidadeMedida = '$'; // valor nulo
        } else {
            registro.unidadeMedida = str[0];
        }

        // leitura de registro.tamanho (campo float)
        scan_quote_string(str);
        if (strcmp(str, "") == 0) {
            registro.tamanho = -1.0; // valor nulo
        } else {
            registro.tamanho = atof(str); // converte para float
        }

        // leitura e alocação de registro.especie
        scan_quote_string(str);
        if (strcmp(str, "") == 0) {
            registro.especie.tamanho = 0;
            registro.especie.valor = NULL;
        } else {
            registro.especie.tamanho = strlen(str);
            registro.especie.valor = malloc((registro.especie.tamanho + 1) * sizeof(char));
            if (registro.especie.valor == NULL) {
                fprintf(stderr, "Erro de alocação de memória.\n");
                // fecha o arquivo antes de sair
                exit(1);
            }
            strcpy(registro.especie.valor, str);
        }

        // leitura e alocação de registro.alimento
        scan_quote_string(str);
        if (strcmp(str, "") == 0) {
            registro.alimento.tamanho = 0;
            registro.alimento.valor = NULL;
        } else {
            registro.alimento.tamanho = strlen(str);
            registro.alimento.valor = malloc((registro.alimento.tamanho + 1) * sizeof(char));
            if (registro.alimento.valor == NULL) {
                fprintf(stderr, "Erro de alocação de memória.\n");
                // fecha o arquivo antes de sair
                exit(1);
            }
            strcpy(registro.alimento.valor, str);
        }

        // verifica se há registros removidos para reutilização
        if(cabecalho.nroRegRem == 0 && cabecalho.topo == -1){           // não há registros removidos
            fseek(arquivo, 0, SEEK_END);
            registro.removido = '0';                             // registro ativo
            registro.encadeamento = -1;                          // não faz parte da pilha
            escreve_registro(arquivo, &registro);

            // atualiza o próximo RRN
            cabecalho.proxRRN += 1;

            // atualiza o número de páginas de disco
            int qtd_paginas;
            // calcula a quantidade de páginas
            fseek(arquivo, 0, SEEK_END);
            qtd_paginas = ftell(arquivo) / 1600;   
            if (ftell(arquivo) % 1600 > 0) {
                qtd_paginas += 1; // adiciona uma página se houver resto na divisão
            }

            // atualiza nroPagDisco se necessário
            if(qtd_paginas != cabecalho.nroPagDisco){     // se houver mudança
                cabecalho.nroPagDisco = qtd_paginas;
            }

            // atualiza o cabeçalho após todas as modificações
            escrever_cabecalho(&cabecalho, arquivo);
        } else { // reutiliza um registro removido
            // busca o último registro removido
            int ultimoRRNrem = cabecalho.topo;                    // último registro removido
            fseek(arquivo, 1600 + (ultimoRRNrem * 160), SEEK_SET);

            // leitura dos campos fixos do registro removido
            Registro registro_temp;
            int tam_fixo = sizeof(char) + sizeof(int) + sizeof(int) + sizeof(float) + sizeof(char) + sizeof(int);
            fread(&(registro_temp.removido), sizeof(char), 1, arquivo);
            fread(&(registro_temp.encadeamento), sizeof(int), 1, arquivo);
            fread(&(registro_temp.populacao), sizeof(int), 1, arquivo);
            fread(&(registro_temp.tamanho), sizeof(float), 1, arquivo);
            fread(&(registro_temp.unidadeMedida), sizeof(char), 1, arquivo);
            fread(&(registro_temp.velocidade), sizeof(int), 1, arquivo);

            // atualiza o registro a ser inserido
            registro.removido = '0';
            registro.encadeamento = -1;
            fseek(arquivo, -tam_fixo, SEEK_CUR);                // retorna ao início do registro
            escreve_registro(arquivo, &registro);

            // atualiza o topo da pilha de removidos
            cabecalho.topo = registro_temp.encadeamento;

            // atualiza o número de registros removidos
            cabecalho.nroRegRem -= 1; // decrementa o número de registros removidos

            // atualiza o cabeçalho após todas as modificações
            escrever_cabecalho(&cabecalho, arquivo);
        }

        // liberação da memória alocada dinamicamente
        if(registro.nome.valor != NULL) free(registro.nome.valor);
        if(registro.dieta.valor != NULL) free(registro.dieta.valor);
        if(registro.habitat.valor != NULL) free(registro.habitat.valor);
        if(registro.alimento.valor != NULL) free(registro.alimento.valor);
        if(registro.tipo.valor != NULL) free(registro.tipo.valor);
        if(registro.especie.valor != NULL) free(registro.especie.valor);
    }

    // atualiza o status para '1' após a operação
    status = '1';
    if(status != '0' && status != '1'){     // validação do status
        printf("Falha no processamento do arquivo.\n");
        // fecha o arquivo antes de retornar
        return;               // mudança não realizada
    }

    // atualiza o status no cabeçalho
    cabecalho.status = status;
    escrever_cabecalho(&cabecalho, arquivo);					// exibe a quantidade de bytes do arquivo
}

void insert_into(FILE *arquivo_binario) {
    int n;
    scanf("%d", &n);
    insercao(arquivo_binario, n);

}

void create_index(FILE *arquivo_dados)
{
    // recebemos o nome do arquivo de indice
    char nome_indice[20];
    scanf(" %s", nome_indice);
    // vamos abrir o arquivo de indice e criar um cabecalho
    // como o cabecalho vai ser alterado a medida que inserimos
    // novos nos, ele vai ser escrito apenas no final da 
    // funcionalidade
    FILE *arquivo_indice = fopen(nome_indice, "w+");
    Cabecalho_indice *cabecalho = cria_cabecalho_indice();

    // primeiro abrimos o arquivo e contamos o numero de registros
    int tamanho = tamanho_bytes(arquivo_dados);
    // alocamos a memoria do registro temporario e do cabecalho
    Registro *registro_temporario = (Registro *)malloc(sizeof(Registro));
    // iteramos sobre o arquivo de dados, inserindo os indices
    for (long offset = 1600; offset < tamanho; offset += 160)
    {
        //insere_arvore_b(arquivo_indice, cabecalho, teste[i], -1);
        le_registro(registro_temporario, arquivo_dados, offset);
        if (!removido(registro_temporario))
        {
            // depois tem que inserir o nome do dinossauro no lugar de teste de novo
            insere_arvore_b(arquivo_indice, cabecalho, converteNome(registro_temporario->nome.valor), offset);
        }
    }
    // apos escrever os nos, escrevemos o cabecalho
    escreve_cabecalho_indice(arquivo_indice, cabecalho);

    // por fim, liberamos cabecalho e fechamos arquivo
    free(cabecalho);
    fclose(arquivo_indice);

    // por fim, chamamos o binario na tela
    binarioNaTela(nome_indice);
}
void busca_nome(FILE *dados) {
    // declara uma variável para armazenar o nome a ser buscado e o nome do arquivo de índice.
    char nome[50];
    char nome_arquivo_indice[50];

    // lê o nome do arquivo de índice que será usado.
    scanf("%s", nome_arquivo_indice);

    // abre o arquivo de índice em modo de leitura binária.
    FILE *indice = fopen(nome_arquivo_indice, "rb");
    if (indice == NULL) {
        // se o arquivo não puder ser aberto, imprime uma mensagem de erro e encerra a função.
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // lê o nome a ser buscado.
    scanf("%s", nome);
    // ajusta o nome retirando possíveis aspas.
    scan_quote_string(nome);

    // converte o nome em uma chave numérica para a busca.
    long chaveBusca = converteNome(nome);

    // se a chave convertida for inválida, exibe uma mensagem e encerra.
    if (chaveBusca == -1) {
        printf("Registro inexistente.\n");
        fclose(indice);
        return;
    }

    // lê o cabeçalho do arquivo de índice para obter o RRN da raiz da árvore B.
    Cabecalho_indice cabecalho;
    le_cabecalho_indice(indice, &cabecalho);
    int rrnRaiz = cabecalho.noRaiz;

    // realiza a busca pela chave na árvore B.
    int PR = buscarIndiceArvore(indice, rrnRaiz, chaveBusca);

    // se o registro não for encontrado, exibe uma mensagem.
    if (PR == -1) {
        printf("Registro inexistente.\n");
    } else {
        // caso contrário, lê o registro correspondente no arquivo de dados.
        Registro registro;
        le_registro(&registro, dados, PR);
        // verifica se o registro foi removido.
        if (registro.removido == '1') {
            printf("Registro inexistente.\n");
        } else {
            // se o registro não foi removido, imprime-o de forma formatada.
            printa_formatado(&registro);
        }
    }

    // fecha o arquivo de índice após a busca.
    fclose(indice);
}
