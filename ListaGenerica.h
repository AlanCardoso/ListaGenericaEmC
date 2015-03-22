/*
Autor: Alan Cardoso
*/

#ifndef LISTA_GENERICA_H
#define LISTA_GENERICA_H

typedef struct lista *Lista;

/*
Cria uma lista vazia.
*/
Lista criarLista();

/*
Remove todos os elementos da lista e a libera da memória.
A função liberarElemento é responsável por desalocar corretamente os elementos da lista da memória.
*/
void destruirLista(Lista l, void (*)(void *));

/*
Verifica se a lista está vazia. 
Retorna um valor diferente de 0 se a lista estiver vazia ou 0 caso contrário.
*/
int listaEstaVazia(Lista l);

/*
Retorna o tamanho atual da lista
*/
int obterTamanhoDaLista(Lista l);

/*
Insere um novo nó(contendo o elemento passado como argumento) na lista na posicao indicada.
Posições válidas são entre 0 e o tamanho da lista.
Retorna um valor diferente de 0 se o elemento foi inserido com sucesso ou 0 caso contrário.
*/
int inserirNaLista(Lista l, void *elemento, unsigned int posicao);

/*
Remove o nó da lista localizado na posição indicada.
Posições válidas são entre 0 e o tamanho da lista.
Retorna um valor diferente de 0 caso a remoção seja bem sucedida ou o valor 0 caso contrário.
A função liberarElemento é responsável por desalocar corretamente um elemento da memória.
*/
int removerDaLista(Lista l, unsigned int posicao, void (*)(void *));

/*
Retorna o elemento contido no nó da lista localizado na posição indicada.
Posições válidas são entre 0 e o tamanho da lista.
Caso a posição seja inválida retorna null.
*/
void *obterElementoDaLista(Lista l, unsigned int posicao);

/*
Retorna um valor diferente de 0 se elemento está contido na lista ou 0 caso contrário.
Recebe como terceiro parâmetro uma função responsável por comparar dois elementos.
*/
int contidoNaLista(Lista l, void *elemento, int (*)(void *, void *));

/*
Ordena a lista recebendo como segundo parâmetro uma função responsável por comparar dois elementos.
*/
void ordenarLista(Lista l, int (*)(void *, void *));

#endif