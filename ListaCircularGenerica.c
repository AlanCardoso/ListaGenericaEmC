/*
Autor: Alan Cardoso
*/

#include "ListaGenerica.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct no *No;

struct lista {
	unsigned int tamanho;
	No inicio;
};

struct no {
	void *elemento;
	No anterior;
	No proximo;
};


/*
Cria uma lista vazia.
*/
Lista criarLista() {
	Lista l = malloc(sizeof(struct lista));
	l->tamanho = 0;
	l->inicio = NULL;
	return l;
}

/*
Verifica se a lista está vazia. 
Retorna um valor diferente de 0 se a lista estiver vazia ou 0 caso contrário.
*/
int listaEstaVazia(Lista l) {
	return l->tamanho == 0;
}

/*
Remove todos os elementos da lista e a libera da memória.
A função liberarElemento é responsável por desalocar corretamente os elementos da lista da memória.
*/
void destruirLista(Lista l, void (*liberarElemento)(void *)) {
	void *elementoRemovido;

	while(!listaEstaVazia(l)) {	
		removerDaLista(l, 0, liberarElemento);
	}
	free(l);
	l = NULL;
}

/*
Retorna o tamanho atual da lista.
*/
int obterTamanhoDaLista(Lista l) {
	return l->tamanho;
}

/*
Insere um novo nó(contendo o elemento passado como argumento) na lista na posicao indicada.
Posições válidas são entre 0 e o tamanho da lista.
Retorna um valor diferente de 0 se o elemento foi inserido com sucesso ou 0 caso contrário.
*/
int inserirNaLista(Lista l, void *elemento, unsigned int posicao) {
	No novoNo = malloc(sizeof(struct no));
	novoNo->anterior = novoNo->proximo = NULL;
	novoNo->elemento = elemento;
	No noSeguinte;
	int indice;

	if (posicao > l->tamanho) {
		return 0;
	}
	if(listaEstaVazia(l)) {
		l->inicio = novoNo;
		l->inicio->anterior = l->inicio->proximo = l->inicio;
	}
	else if(posicao == 0) {
		novoNo->anterior = l->inicio->anterior;
		novoNo->proximo = l->inicio;
		l->inicio->anterior->proximo = novoNo;
		l->inicio->anterior = novoNo;
		l->inicio = novoNo;
	}
	else {
		for(indice = 0, noSeguinte = l->inicio; indice < posicao; indice++, noSeguinte = noSeguinte->proximo);
		noSeguinte->anterior->proximo = novoNo;
		novoNo->anterior = noSeguinte->anterior;
		novoNo->proximo = noSeguinte;
		noSeguinte->anterior = novoNo;
	}
	l->tamanho++;
	return 1;
}

/*
Remove o nó da lista localizado na posição indicada.
Posições válidas são entre 0 e o tamanho da lista.
Retorna um valor diferente de 0 caso a remoção seja bem sucedida ou o valor 0 caso contrário.
A função liberarElemento é responsável por desalocar corretamente um elemento da memória.
*/
int removerDaLista(Lista l, unsigned int posicao, void (*liberarElemento)(void *)) {
	void *elemento;
	No noRemovido;
	int indice;

	if(listaEstaVazia(l) || posicao >= l->tamanho) {
		return 0;
	}
	if(l->tamanho == 1) {
		noRemovido = l->inicio;
		l->inicio = NULL;
	}
	else {
		for(indice = 0, noRemovido = l->inicio; indice < posicao; indice++, noRemovido = noRemovido->proximo);
		noRemovido->anterior->proximo = noRemovido->proximo;
		noRemovido->proximo->anterior = noRemovido->anterior;
		if(noRemovido == l->inicio) {
			l->inicio = l->inicio->proximo;
		}
	}
	liberarElemento(noRemovido->elemento);
	free(noRemovido);
	l->tamanho--;
	return 1;
}

/*
Retorna o elemento contido no nó da lista localizado na posição indicada.
Posições válidas são entre 0 e o tamanho da lista.
Caso a posição seja inválida retorna null.
*/
void *obterElementoDaLista(Lista l, unsigned int posicao) {
	if(posicao < l->tamanho) {
		int indice;
		No noProcurado;
		for(indice = 0, noProcurado = l->inicio; indice < posicao; indice++, noProcurado = noProcurado->proximo);
		return noProcurado->elemento;
	}
	return NULL;
}

/*
Retorna o nó da lista localizado na posição indicada.
Posições válidas são entre 0 e o tamanho da lista.
Caso a posição seja inválida retorna null.
*/
No hiddenFunction(Lista l, unsigned int posicao) {
	if(posicao < l->tamanho) {
		int indice;
		No noProcurado;
		for(indice = 0, noProcurado = l->inicio; indice < posicao; indice++, noProcurado = noProcurado->proximo);
		return noProcurado;
	}
	return NULL;
}

/*
Retorna um valor diferente de 0 se o elemento está contido na lista ou 0 caso contrário
Recebe como terceiro parâmetro uma função responsável por comparar dois elementos.
A função comparar deve retornar o valor 0(zero) caso os elementos sejam iguais, um valor negativo se o primeiro elemento for menor que o segundo elemento ou um valor positivo caso o primeiro elemento seja maior que o segundo elemento
*/
int contidoNaLista(Lista l, void *elemento, int (*comparar)(void *, void *)) {
	int tamanhoDaLista = l->tamanho;
	int indice;
	No noAtual;

	for(indice = 0, noAtual = l->inicio; indice < tamanhoDaLista; indice++, noAtual = noAtual->proximo)
		if (comparar(elemento, noAtual->elemento) == 0)
			return 1;
	return 0;
}

/*
Função de ordenação: Quicksort
*/
void awesomeSorting(Lista l, int posicaoInicio, int posicaoFim, int (*comparar)(void *, void *)) {
	int posicaoInferior = posicaoInicio;
	int posicaoSuperior = posicaoFim;
	void *elementoPivo = obterElementoDaLista(l, (posicaoInicio + posicaoFim)/2);
	void *variavelDeTransicaoDeElemento;
	No noDaPosicaoInferior;
	No noDaPosicaoSuperior;
	void *elementoDaPosicaoInferior;
	void *elementoDaPosicaoSuperior;

	if(!listaEstaVazia(l)) {
		while(posicaoInferior < posicaoSuperior) {
			while(comparar(obterElementoDaLista(l, posicaoInferior), elementoPivo) < 0) {
				posicaoInferior++;
			}
			while(comparar(obterElementoDaLista(l, posicaoSuperior), elementoPivo) > 0) {
				posicaoSuperior--;
			}
			if(posicaoInferior <= posicaoSuperior) {
				noDaPosicaoInferior = hiddenFunction(l, posicaoInferior);
				noDaPosicaoSuperior = hiddenFunction(l, posicaoSuperior);
				variavelDeTransicaoDeElemento = noDaPosicaoInferior->elemento;
				noDaPosicaoInferior->elemento = noDaPosicaoSuperior->elemento;
				noDaPosicaoSuperior->elemento = variavelDeTransicaoDeElemento;
				posicaoInferior++;
				posicaoSuperior--;
			}
		}
		if(posicaoSuperior > posicaoInicio) {
			awesomeSorting(l, posicaoInicio, posicaoSuperior, comparar);
		}
		if(posicaoInferior < posicaoFim) {
			awesomeSorting(l, posicaoInferior, posicaoFim, comparar);
		}
	}
}


/*
Ordena uma lista recebendo como segundo parâmetro uma função responsável por comparar dois elementos
A função comparar deve retornar o valor 0(zero) caso os elementos sejam iguais, um valor negativo se o primeiro elemento for menor que o segundo elemento ou um valor positivo caso o primeiro elemento seja maior que o segundo elemento
*/
void ordenarLista(Lista l, int (*comparar)(void *, void *)) {;
	awesomeSorting(l, 0, l->tamanho-1, comparar);
}
