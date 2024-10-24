#include "fila.h"

///////////////////////////////////////////////////////////////////////////////////
// PRIVADO ///////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

// a presente funcao adiciona o no na fila
void poe_na_fila(Fila *fila, No *no)
{
    if (fila->cabeca == NULL)
    {
        fila->cabeca = no;
        fila->rabo = no;
    }
    else
    {
        // proximo na fila agora esta atras do antigo ultimo
        fila->rabo->proximo = no;
        // na frente do ultimo esta o velho ultimo
        no->frente = fila->rabo;
        // o novo ultimo toma o lugar do velho
        fila->rabo = no;
    }
}

// cria um no vazio
No *cria_no()
{
    No *no = (No *)malloc(sizeof(No));
    no->proximo = NULL;
    no->frente = NULL;
    no->campo = NULL;
    no->valor = NULL;

    return no;
}

// a presente funcao cria uma fila
Fila *cria_fila()
{
    Fila *fila = (Fila *)malloc(sizeof(Fila));
    fila->cabeca = NULL;
    fila->rabo = NULL;
    return fila;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
// PUBLICO ///////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////////

// essa funcao recebe uma fila e libera sua cabeca e vai pro proximo
void proximo_na_fila(Fila *fila)
{
    // se soh tem um elemento, a fila fica vazia
    if (fila->cabeca->proximo == NULL)
    {
        free(fila->cabeca);
        fila->cabeca = NULL;
        fila->rabo = NULL;
    }
    // caso contrario, liberamos a cabeca e a nova cabeca eh o proximo
    else
    {
        // novo proximo na fila eh o proximo do antigo proximo
        fila->cabeca = fila->cabeca->proximo;
        // liberamos quem estava na frente do novo proximo
        free(fila->cabeca->frente);
        // nao tem mais ninguem na frente do proximo na fila
        fila->cabeca->frente = NULL;
    }
}
/////////////////////////////////////////////////////////////////////////////////////
