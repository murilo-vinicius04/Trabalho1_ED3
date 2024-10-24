// Pedro Fuziwara Filho - 13676840
// Murilo Vinicius da Silva - 14600030

#include "arvore_b.h"

// cria cabecalho_indice com tudo inicializado
Cabecalho_indice *cria_cabecalho_indice()
{
    // alocamos um cabecalho e o inicializamos
    Cabecalho_indice *cabecalho = (Cabecalho_indice*)malloc(sizeof(Cabecalho_indice));
    cabecalho->status = '1';
    cabecalho->noRaiz = -1;
    cabecalho->RRNproxNo = 0;

    return cabecalho;
}

// escreve o cabecalho no arquivo
void escreve_cabecalho_indice(FILE *arquivo, Cabecalho_indice *cabecalho)
{
    char lixo = '$'; 
    // vamos escrever o cabecalho no arquivo
    fseek(arquivo, 0, SEEK_SET);
    fwrite(&cabecalho->status, sizeof(char), 1, arquivo);
    fwrite(&cabecalho->noRaiz, sizeof(int), 1, arquivo);
    fwrite(&cabecalho->RRNproxNo, sizeof(int), 1, arquivo);
    for (int i = 0; i < 84; i++)
        fwrite(&lixo, sizeof(char), 1, arquivo);
}

void escreve_no_indice(FILE *arquivo, No_indice *no)
{
    // primeiro calculamos o byte offset
    int RRN = no->RRNdoNo;
    int offset = 93 + RRN*93;   // precisamos pular o cabecalho

    // agora escrevemos no no arquivo
    fseek(arquivo, offset, SEEK_SET);
    fwrite(&no->folha, sizeof(char), 1, arquivo);
    fwrite(&no->nroChavesIndexadas, sizeof(int), 1, arquivo);
    fwrite(&no->RRNdoNo, sizeof(int), 1, arquivo);

    // como todo no tem no maximo quatro indices, entao vamos escrever
    // cada um deles
    for (int i = 0; i < 4; i++)
    {
        fwrite(&no->filho[i], sizeof(int), 1, arquivo);
        fwrite(&no->valor[i], sizeof(long), 1, arquivo);
        fwrite(&no->referencia[i], sizeof(long), 1, arquivo);
    }

    // por fim, escrevemos o endereco do ultimo filho
    fwrite(&no->filho[4], sizeof(int), 1, arquivo);
}

// le no a partir de um rrn
void le_no_indice(FILE *arquivo, int rrn, No_indice *no)
{
    // posiciona cabeca na leitura
    int offset = 93 + rrn*93;
    fseek(arquivo, offset, SEEK_SET);
    // realiza leitura do no
    fread(&no->folha, sizeof(char), 1, arquivo);
    fread(&no->nroChavesIndexadas, sizeof(int), 1, arquivo);
    fread(&no->RRNdoNo, sizeof(int), 1, arquivo);
    for (int i = 0; i < ORDEM - 1; i++)
    {
        fread(&no->filho[i], sizeof(int), 1, arquivo);
        fread(&no->valor[i], sizeof(long), 1, arquivo);
        fread(&no->referencia[i], sizeof(long), 1, arquivo);
    }
    fread(&no->filho[4], sizeof(int), 1, arquivo);
}

// le o cabecalho
void le_cabecalho_indice(FILE *arquivo, Cabecalho_indice *cabecalho)
{
    fseek(arquivo, 0, SEEK_SET);
    fread(&cabecalho->status, sizeof(char), 1, arquivo);
    fread(&cabecalho->noRaiz, sizeof(int), 1, arquivo);
    fread(&cabecalho->RRNproxNo, sizeof(int), 1, arquivo);
}

// vai separar no em dois 
void separa_no_indice(FILE *arquivo, long chave_nova, long referencia_nova, int filho_novo, No_indice *no, long *chave, long *referencia, int *filho, No_indice *novo_no, Cabecalho_indice *cabecalho)
{
    // criamos vetores temporarios com um espaco a mais
    long chaves_temporario[MAX_CHAVE+1];
    long referencias_temporario[MAX_CHAVE+1];
    int filhos_temporario[MAX_CHAVE+2];
  
    // vamos encontrar onde inserir a chave nova
    int pos = 0;
    while (pos < no->nroChavesIndexadas && chave_nova > no->valor[pos])
        pos++;
    // vamos construir a nova pagina temporaria
    for (int i = 0; i < 5; i++)
    {
        // antes da posicao onde sera inserido, tudo fica igual
        if (i < pos)
        {
            chaves_temporario[i] = no->valor[i];
            referencias_temporario[i] = no->referencia[i];
            filhos_temporario[i] = no->filho[i];
        }
        // na posicao de insercao, inserimos
        else if (i == pos)
        {
            chaves_temporario[i] = chave_nova;
            referencias_temporario[i] = referencia_nova;
            // filho novo entra na direita
            filhos_temporario[i+1] = filho_novo;
            // no caso de pos ser o ultimo disponivel, nao caimos no else de volta, dai precisamos ja
            // salvar o filho da esquerda junto
            if (i == 4)
                filhos_temporario[i] = no->filho[i];
        }
        // se ta na frente da posicao que tem que inserir, entao precisamos jogar todo mundo 
        // para frente em um
        else
        {
            chaves_temporario[i] = no->valor[i-1];
            referencias_temporario[i] = no->referencia[i-1];
            // quando acabamos de inserir nova chave, precisamos voltar 1 para colocar o filho da
            // esquerda
            if (i == pos + 1)
                filhos_temporario[i-1] = no->filho[i-1];
            else
                filhos_temporario[i] = no->filho[i-1];
        }
    }
    // eh preciso colocar o ultimo filho, caso o ultimo filho nao seja justamente da promocao, ou seja, na posicao 4
    if (pos != 4)
        filhos_temporario[5] = no->filho[4]; 
    
    // o valor do meio sera promovido
    *chave = chaves_temporario[2];
    *referencia = referencias_temporario[2];
    *filho = novo_no->RRNdoNo;
 
    // atualiza no
    no->nroChavesIndexadas = 2;
    for (int i = 0; i < 4; i++)
    {
        if (i < 2)
        {
            no->valor[i] = chaves_temporario[i];
            no->referencia[i] = referencias_temporario[i];
            no->filho[i] = filhos_temporario[i];
        }
        else
        {
            no->valor[i] = -1;
            no->referencia[i] = -1;
            no->filho[i] = -1;
        }
    }
    // precisamos colocar o filho na direita
    no->filho[2] = filhos_temporario[2];
    no->filho[4] = -1;

    // atualiza novo_no
    novo_no->folha = no->folha;
    novo_no->nroChavesIndexadas = 2;
    for (int i = 0; i < 4; i++)
    {
        if (i < 2)
        {
            novo_no->valor[i] = chaves_temporario[i+3];
            novo_no->referencia[i] = referencias_temporario[i+3];
            novo_no->filho[i] = filhos_temporario[i+3];
        }
        else if (i > 2)
        {
            novo_no->valor[i] = -1;
            novo_no->referencia[i] = -1;
            novo_no->filho[i] = -1;
        }
        else
        {
            novo_no->valor[i] = -1;
            novo_no->referencia[i] = -1;
            novo_no->filho[i] = filhos_temporario[5];
        }
    }
    novo_no->filho[4] = -1;
}

int insere_chave(FILE *arquivo, int RRNatual, long chave, long offset, long *chave_promovida, long *referencia_promovida, int *filho_direito, Cabecalho_indice *cabecalho)
{
    if (RRNatual == NIL)
    {
        // chegamos na folha e inserimos valor nela
        *chave_promovida = chave;
        *referencia_promovida = offset;
        *filho_direito = NIL;
        return PROMOCAO;
    }
    // caso nao seja no folha, entao precisamos chamar a funcao recursivamente
    else
    {
        // essa eh a fase de pesquisa do algoritmo
        No_indice no;
        le_no_indice(arquivo, RRNatual, &no);
        // pos eh a posicao que a chave deve entrar
        int pos = 0;
        while (pos < no.nroChavesIndexadas && chave > no.valor[pos])
            pos++;
        // nao pode ter duplicatas
        if (pos != 4 && no.valor[pos] == chave)
        {
            printf("Falha no processamento do arquivo.\n");
            return ERRO;
        }
        // chave de busca nao foi encontrada, portanto vamos pro seu filho
        long nova_chave_promovida;
        long nova_referencia_promovida;
        int novo_filho_promovido;
        int retorno = insere_chave(arquivo, no.filho[pos], chave, offset, &nova_chave_promovida, &nova_referencia_promovida, &novo_filho_promovido, cabecalho);
        
        // a partir daqui eh a fase de volta da recursao
        // caso mais simples, nao ha nada que precisa ser feito
        if (retorno == SEM_PROMOCAO || retorno == ERRO)
        {
            return retorno;
        }
        // caso em que faz insercao sem particionamento
        else if (no.nroChavesIndexadas < MAX_CHAVE)
        {
            // insere a chave promovida
            // primeiro, joga todo mundo pra frente
            for (int i = no.nroChavesIndexadas; i > pos; i--)
            {
                no.valor[i] = no.valor[i-1];
                no.referencia[i] = no.referencia[i-1];
                no.filho[i+1] = no.filho[i];
            }
            // depois insere chave
            no.valor[pos] = nova_chave_promovida;
            no.referencia[pos] = nova_referencia_promovida;
            no.filho[pos+1] = novo_filho_promovido;
            no.nroChavesIndexadas++;
            // escreve pagina atualizada
            escreve_no_indice(arquivo, &no);
            // como nao tem particionamento, nao tem promocao
            return SEM_PROMOCAO;
        }
        // por fim, caso em que precisa fazer particionamento
        else
        {
            // cria novo no para a divisao
            No_indice novo_no;
            novo_no.RRNdoNo = cabecalho->RRNproxNo;
            cabecalho->RRNproxNo++;
            // caso o no seja folha, o filho vai ser -1
            if (no.folha == '1')
                novo_filho_promovido = -1;
            separa_no_indice(arquivo, nova_chave_promovida, nova_referencia_promovida, novo_filho_promovido, &no, chave_promovida, referencia_promovida, filho_direito, &novo_no, cabecalho);
            // escreve paginas atualizadas
            escreve_no_indice(arquivo, &no);
            escreve_no_indice(arquivo, &novo_no);

            // precisamos escrever tudo nas chaves promovidas
            chave_promovida = &nova_chave_promovida;
            referencia_promovida = &nova_referencia_promovida;
            filho_direito = &novo_filho_promovido;

            // como teve divisao, precisa de promocao
            return PROMOCAO; 
        }
    }
}

// insere chave e referencia na arvore b
void insere_arvore_b(FILE *arquivo, Cabecalho_indice *cabecalho, long chave, long offset)
{
    // valores auxiliares
    long chave_promovida;
    long referencia_promovida;
    int filho_direito_promovido;

    int retorno = insere_chave(arquivo, cabecalho->noRaiz, chave, offset, &chave_promovida, &referencia_promovida, &filho_direito_promovido, cabecalho);
    // caso em que a recursao chega ao fim precisano criar nova raiz
    if (retorno == PROMOCAO)
    {
        No_indice nova_raiz;
        // inicializamos a nova raiz
        for (int i = 0;  i < 5; i++)
            nova_raiz.filho[i] = -1;
        for (int i = 0; i < 4; i++)
        {
            nova_raiz.valor[i] = -1;
            nova_raiz.referencia[i] = -1;
        }

        // se nao tem raiz, entao criamos arvore
        if (cabecalho->noRaiz == -1)
        {
            cabecalho->noRaiz = 0;
            nova_raiz.folha = '1';
        }
        else
        {
            nova_raiz.folha = '0';
            nova_raiz.filho[0] = cabecalho->noRaiz;
            nova_raiz.filho[1] = filho_direito_promovido;
        }
        nova_raiz.nroChavesIndexadas = 1;
        nova_raiz.RRNdoNo = cabecalho->RRNproxNo;
        cabecalho->RRNproxNo++;
        nova_raiz.valor[0] = chave_promovida;
        nova_raiz.referencia[0] = referencia_promovida;
        cabecalho->noRaiz = nova_raiz.RRNdoNo;

        //escreve nova raiz
        escreve_no_indice(arquivo, &nova_raiz);

    }
}

long buscarIndiceArvore(FILE *arquivo, int rrnAtual, long chaveBusca) {
    // se o rrn atual for igual a NIL, significa que chegamos ao final da árvore sem encontrar a chave.
    if (rrnAtual == NIL) {
        // retorna -1 para indicar que a chave não foi encontrada.
        return -1;
    }

    // ler o nó atual a partir do RRN (localização no arquivo).
    No_indice no;
    le_no_indice(arquivo, rrnAtual, &no);

    // procurar a chave dentro do nó atual.
    int i = 0;
    while (i < no.nroChavesIndexadas && chaveBusca > no.valor[i]) {
        // incrementa o índice i até encontrar a posição onde a chave pode estar ou passar dela.
        i++;
    }

    // verifica se a chave foi encontrada no nó.
    if (i < no.nroChavesIndexadas && chaveBusca == no.valor[i]) {
        // se a chave foi encontrada, retorna a referência associada a essa chave.
        return no.referencia[i];
    }

    // se não encontrou a chave, chama recursivamente a função para buscar no filho apropriado.
    return buscarIndiceArvore(arquivo, no.filho[i], chaveBusca);
}

