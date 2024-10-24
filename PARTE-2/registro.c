#include "registro.h"

/////////////////////////////////////////////////////////////////////////////////////////////
// PRIVADO ///////////////////////////////////////////////////////////////////////

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


// a funcao busca_int_printa vai buscar o int valor do respectivo int campo no FILE *arquivo
// printar os registros encontrados
// Se encontrar algum registro retorna 1, senao retorna 0
int busca_int_printa(FILE *arquivo, int campo, int valor)
{
    // primeiro aloca registro temporario
    Registro *registro = (Registro *)malloc(sizeof(Registro));
    // pegamos tamanho para saber quando terminar a leitura
    int tamanho = tamanho_bytes(arquivo);
    // declaramos a variavel achou_algo inicializada em 0 (false), 
    // ja que no comeco da busca nao achamos nada
    int achou_algo = 0;
    // nao podemos pular linha no primeiro registro buscado
    int primeiro = 1;
    // pegamos as informacoes e printamos se o campo estivar com o int certo
    for (int offset = 1600; offset < tamanho; offset += 160)
    {
        le_registro(registro, arquivo, offset);
        if (!removido(registro))
            switch (campo)
            {
                case 0:
                    if (registro->populacao == valor)
                    {
                        if (!primeiro)
                            printf("\n");   // pulamos linha no primeiro registro
                        achou_algo = 1;
                        primeiro = 0;
                        printa_formatado(registro);
                    }
                    break;
                case 3:
                    if (registro->velocidade == valor)
                    {
                        if (!primeiro)
                            printf("\n");   // pulamos linha no primeiro registro
                        achou_algo = 1;
                        primeiro = 0;
                        printa_formatado(registro);
                    }
                    break;
            }
    }
    // por fim, liberamos o registro temporario
    libera_registro(registro);

    return achou_algo;
}

// a funcao busca_float_printa vai buscar o float valor do cmpo tamanho (unico que tem float)
// int campo no FILE *arquivo e printar os registros encontrados
// Retorna 1 se encontrou algum arquivo, senao retorna 0
int busca_float_printa(FILE *arquivo, float valor)
{
    // primeiro aloca registro temporario
    Registro *registro = (Registro *)malloc(sizeof(Registro));
    int tamanho = tamanho_bytes(arquivo);
    int achou_algo = 0;
    int primeiro = 1;
    // pegamos as informacoes e printamos se o campo estivar com o int certo
    for (int offset = 1600; offset < tamanho; offset += 160)
    {
        le_registro(registro, arquivo, offset);
        if (!removido(registro) && registro->tamanho == valor)
        {
            if (!primeiro)
                printf("\n");
            primeiro = 0;
            achou_algo = 1;
            printa_formatado(registro);
        }
    }
    // por fim, liberamos o registro temporario
    libera_registro(registro);

    return achou_algo;
}


// a funcao busca_str_printa vai buscar o string valor do respectivo int campo no FILE *arquivo
// printar os registros encontrados
// retorna 1 se encontrou algum registro e 0 caso contrario
int busca_str_printa(FILE *arquivo, int campo, char *valor)
{
    // primeiro aloca registro temporario
    Registro *registro = (Registro *)malloc(sizeof(Registro));
    int tamanho = tamanho_bytes(arquivo);
    int achou_algo = 0;
    int primeiro = 1;
    // pegamos as informacoes e printamos se o campo estivar com o int certo
    for (int offset = 1600; offset < tamanho; offset += 160)
    {
        le_registro(registro, arquivo, offset);
        if (!removido(registro))
            switch (campo)
            {
                case 4:
                    if (strcmp(registro->nome.valor, valor) == 0)
                    {
                        if (!primeiro)
                            printf("\n");   // pulamos linha no primeiro registro
                        primeiro = 0;
                        achou_algo = 1;
                        printa_formatado(registro);
                    }
                    break;
                case 5:
                    if (strcmp(registro->especie.valor, valor) == 0)
                    {
                        if (!primeiro)
                            printf("\n");   // pulamos linha no primeiro registro
                        primeiro = 0;
                        achou_algo = 1;
                        printa_formatado(registro);
                    }
                    break;
                case 6:
                    if (strcmp(registro->habitat.valor, valor) == 0)
                    {
                        if (!primeiro)
                            printf("\n");   // pulamos linha no primeiro registro
                        primeiro = 0;
                        achou_algo = 1;
                        printa_formatado(registro);
                    }
                    break;
                case 7:
                    if (strcmp(registro->tipo.valor, valor) == 0)
                    {
                        if (!primeiro)
                            printf("\n");   // pulamos linha no primeiro registro
                        primeiro = 0;
                        achou_algo = 1;
                        printa_formatado(registro);
                    }
                    break;
                case 8:
                    if (strcmp(registro->dieta.valor, valor) == 0)
                    {
                        if (!primeiro)
                            printf("\n");   // pulamos linha no primeiro registro
                        primeiro = 0;
                        achou_algo = 1;
                        printa_formatado(registro);
                    }
                    break;
                case 9:
                    if (strcmp(registro->alimento.valor, valor) == 0)
                    {
                        if (!primeiro)
                            printf("\n");   // pulamos linha no primeiro registro
                        primeiro = 0;
                        achou_algo = 1;
                        printa_formatado(registro);
                    }
                    break;
            }
    }

    free(registro);
    return achou_algo;
}

// o codigo realmente novo eh o remove()
// ele vai receber o arquivo e o byte offset do registro a ser removido, a partir
// disso vamos realizar a remocao logica desse arquivo
void remove_especie(FILE *arquivo, Cabecalho *cabeca, int offset)
{
    // primeiro precisamos calcular o rrn do registro que estamos tirando
    // no caso 1600 eh da primeira pagina, que eh cabecalho, e o 160 eh 
    // o tamanho do registro
    int rrn = (offset - 1600)/160;
    int nroRegRem;
    // marcamos ele como removido e guardamos no encadenamento o antigo topo
    char sim = '1';
    char lixo = '$';
    // arruma o ponteiro para o campo "topo" do cabecalho e salva o novo rrn nele
    fseek(arquivo, 1, SEEK_SET);
    fwrite(&rrn, 4, 1, arquivo);
    // vamos ler o numero de vezes que algum registro foi removido e incrementamos
    fseek(arquivo, 9, SEEK_SET);
    fread(&nroRegRem, 4, 1, arquivo);
    nroRegRem++;
    fseek(arquivo, 9, SEEK_SET);
    fwrite(&nroRegRem, 4, 1, arquivo);
    // agora vamos para o registro a ser eliminado
    fseek(arquivo, offset, SEEK_SET);
    fwrite(&sim, 1, 1, arquivo);
    fwrite(&cabeca->topo, 4, 1, arquivo);
    // lembrando que o resto do registro tem 160 - 1 - 4 = 155 bytes
    for (int i = 0; i < 155; i++)
        fwrite(&lixo, 1, 1, arquivo);
    cabeca->topo = rrn;
}

// eh o equivalente ao busca_int_printa mas ao inves de printar, remove ele logicamente
void busca_int_retira(FILE *arquivo, Cabecalho *cabeca, int campo, int valor)
{   
    // como vamos apenas fazer a leitura buscando o valor desejado, essa funcao
    // eh semelhante a busca_int_printa, mudando o printa_formatado por remove
    // alem das questoes de formatacao que nao sao mais necessarias

    // primeiro aloca registro temporario
    Registro *registro = (Registro *)malloc(sizeof(Registro));
    // pegamos tamanho para saber quando terminar a leitura
    int tamanho = tamanho_bytes(arquivo);
    // pegamos as informacoes e printamos se o campo estivar com o int certo
    for (int offset = 1600; offset < tamanho; offset += 160)
    {
        le_registro(registro, arquivo, offset);
        if (!removido(registro))
            switch (campo)
            {
                case 0:
                    if (registro->populacao == valor)
                        remove_especie(arquivo, cabeca, offset); 
                    break;
                case 3:
                    if (registro->velocidade == valor)
                        remove_especie(arquivo, cabeca, offset); 
                    break;
            }
    }
    // por fim, liberamos o registro temporario
    libera_registro(registro);
}

// eh o equivalente ao busca_float_printa mas ao inves de printar, remove ele logicamente
void busca_float_retira(FILE *arquivo, Cabecalho *cabeca, float valor)
{   
    // como vamos apenas fazer a leitura buscando o valor desejado, essa funcao
    // eh semelhante a busca_float_printa, mudando o printa_formatado por remove
    // alem das questoes de formatacao que nao sao mais necessarias
    
    // primeiro aloca registro temporario
    Registro *registro = (Registro *)malloc(sizeof(Registro));
    int tamanho = tamanho_bytes(arquivo);
    // pegamos as informacoes e printamos se o campo estivar com o int certo
    for (int offset = 1600; offset < tamanho; offset += 160)
    {
        le_registro(registro, arquivo, offset);
        if (!removido(registro) && registro->tamanho == valor)
            remove_especie(arquivo, cabeca, offset); 
    }
    // por fim, liberamos o registro temporario
    libera_registro(registro);
}

// eh o equivalente ao busca_str_printa mas ao inves de printar, remove ele logicamente
void busca_str_retira(FILE *arquivo, Cabecalho *cabeca, int campo, char *valor)
{   
    // como vamos apenas fazer a leitura buscando o valor desejado, essa funcao
    // eh semelhante a busca_float_printa, mudando o printa_formatado por remove
    // alem das questoes de formatacao que nao sao mais necessarias
    
    // primeiro aloca registro temporario
    Registro *registro = (Registro *)malloc(sizeof(Registro));
    int tamanho = tamanho_bytes(arquivo);
    // pegamos as informacoes e printamos se o campo estivar com o int certo
    for (int offset = 1600; offset < tamanho; offset += 160)
    {
        le_registro(registro, arquivo, offset);
        if (!removido(registro))
            switch (campo)
            {
                case 4:
                    if (strcmp(registro->nome.valor, valor) == 0)
                        remove_especie(arquivo, cabeca, offset); 
                    break;
                case 5:
                    if (strcmp(registro->especie.valor, valor) == 0)
                        remove_especie(arquivo, cabeca, offset); 
                    break;
                case 6:
                    if (strcmp(registro->habitat.valor, valor) == 0)
                        remove_especie(arquivo, cabeca, offset); 
                    break;
                case 7:
                    if (strcmp(registro->tipo.valor, valor) == 0)
                        remove_especie(arquivo, cabeca, offset); 
                    break;
                case 8:
                    if (strcmp(registro->dieta.valor, valor) == 0)
                        remove_especie(arquivo, cabeca, offset); 
                    break;
                case 9:
                    if (strcmp(registro->alimento.valor, valor) == 0)
                        remove_especie(arquivo, cabeca, offset); 
                    break;
            }
    }
}

///////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
// PUBLICO ///////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////////

// essa funcao recebe o ponteiro de um arquivo, o byte offset do registro,
// e o ponteiro do registro que salvara os dados
// a seguinte funcao le o registro com byteoffset do arquivo
void le_registro(Registro *registro, FILE *arquivo, int offset)
{
    // arruma o ponteiro para o inicio do registro e le os valores
    fseek(arquivo, offset, SEEK_SET);
    fread(&registro->removido, 1, 1, arquivo);
    fread(&registro->encadeamento, 4, 1, arquivo);
    // toda especie precisa ter um nome valido, salvamos posicao e vemos se especie comeca com $
    int temporario = ftell(arquivo);
    fseek(arquivo, temporario + 13, SEEK_SET);
    if (fgetc(arquivo) == '$')
        return;
    // volta a ler o registro
    fseek(arquivo, temporario, SEEK_SET); 
    fread(&registro->populacao, 4, 1, arquivo);
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
    if (nao_nulo(registro, 6))
        printf("Lugar que habitava: %s\n", registro->habitat.valor);
    if (nao_nulo(registro, 1))
        printf("Tamanho: %.1f m\n", registro->tamanho);
    if (nao_nulo(registro, 2) && nao_nulo(registro, 3))
        printf("Velocidade: %d %cm/h\n", registro->velocidade, registro->unidadeMedida);
    printf("\n");
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
}

// a seguinte funcao vai buscar no arquivo o registro que possui o campo com o valor
// especificado e vai printar todos os registros cujos valores baterem
void busca_e_printa(FILE *arquivo, int campo, char *valor)
{
    int achou_algo;
    // dependendo do tipo de valor que queremos buscar, chamamos uma funcao que realiza
    // essa busca especificamente para esse tipo 
    if (campo == 0 || campo == 3)
        achou_algo = busca_int_printa(arquivo, campo, atoi(valor));   // atoi(char *) transforma string em int
    else if (campo == 1)
        achou_algo = busca_float_printa(arquivo, atof(valor));        // afor(char *) transform string em float
    else
        achou_algo = busca_str_printa(arquivo, campo, sem_aspas(valor));

    // avisa caso nao tenha encontrado registro
    if (!achou_algo)
        printf("Registro inexistente.\n");
}

// a seguinte funcao vai buscar no arquivo o registro que possui o campo com o valor
// especificado e vai remove-los logicamente, ou seja, vai marca-lo como logicamente
// removivel e o rrn do proximo na pilha e vai marcar com lixo '$' em todo o resto
void busca_e_retira(FILE *arquivo, Cabecalho *cabeca, int campo, char *valor)
{
    // perceba que a implementacao dessa parte eh quase igual ao do busca_e_printa
    // mudando apenas as funcoes busca_x_printa porque vamos apenas ver qual campo
    // estamos selecionando para fazer a correta transformacao do str
    // claro, outra mudanca eh o int achou_algo que era importante para a formatacao
    // mas nao eh mais agora

    // dependendo do tipo de valor que queremos buscar, chamamos uma funcao que realiza
    // essa busca especificamente para esse tipo
    fseek(arquivo, 1600, SEEK_SET); 
    if ((campo == 0) || (campo == 3))
        busca_int_retira(arquivo, cabeca, campo, atoi(valor));   // atoi(char *) transforma string em int
    else if (campo == 1)
        busca_float_retira(arquivo, cabeca, atof(valor));        // afor(char *) transform string em float
    else 
        busca_str_retira(arquivo, cabeca, campo, sem_aspas(valor));
}


void escreve_registro(FILE *arquivo_binario, Registro *registro) {
    char delimitador = '#';      // separador entre campos variáveis
    char preenchimento = '$';    // caractere para preencher espaço vazio

    // escrevendo os campos fixos no arquivo binário
    fwrite(&registro->removido, sizeof(char), 1, arquivo_binario);
    fwrite(&registro->encadeamento, sizeof(int), 1, arquivo_binario);
    fwrite(&registro->populacao, sizeof(int), 1, arquivo_binario);
    fwrite(&registro->tamanho, sizeof(float), 1, arquivo_binario);
    fwrite(&registro->unidadeMedida, sizeof(char), 1, arquivo_binario);
    fwrite(&registro->velocidade, sizeof(int), 1, arquivo_binario);

    // escrevendo os campos variáveis com delimitadores
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

    // calculando espaço usado e preenchendo o restante com '$'
    int bytesUsados = sizeof(char) + sizeof(int) * 3 + sizeof(float) + sizeof(int) +
                      registro->nome.tamanho + 1 + 
                      registro->especie.tamanho + 1 +
                      registro->habitat.tamanho + 1 +
                      registro->tipo.tamanho + 
                      registro->dieta.tamanho + 
                      registro->alimento.tamanho;

    for (int i = 0; i < (160 - bytesUsados); i++) {
        fwrite(&preenchimento, sizeof(char), 1, arquivo_binario);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////
