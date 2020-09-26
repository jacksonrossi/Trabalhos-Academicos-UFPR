#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

/******************************************************************
Este arquivo contém as funções de leitura, escrita, destruição 
cálculo do número de vértices e arestas, retorno do nome de uma 
aresta e a cobertura por trilhas de um grafo dado.

Autor: Jackson
Data: 17/05/2019
******************************************************************/

//==========================================================================
/*
struct _vertice;
	
struct _grafo{
	char string[1025];
	struct _vertice *arestaG;
	struct _grafo *prox_vertice;
	//int marca;
};

struct _vertice{
	struct _grafo *arestaA;
	struct _vertice *prox_aresta;
};
*/
//==========================================================================

#define BRANCO 2
#define CINZA  0
#define PRETO  1

//==========================================================================

grafo escreve_grafo(FILE *output, grafo g){
	grafo atual_g = g->prox_vertice, aux_a;
	vertice atual_a;
	int nao_impresso;

	while (atual_g != NULL){						//Percorre todos vertices
		atual_a = atual_g->arestaG;
		if(atual_a == NULL){						//Se vertice eh isolado, imprime apenas o vertice e busca proximp
			fprintf(output, "%s\n", atual_g->string);
			atual_g = atual_g->prox_vertice;
			continue;
		}
		while(atual_a != NULL){						//Se nao, percorre todas as arestas
			aux_a = atual_g->prox_vertice;
			nao_impresso = 0;
			while( aux_a != NULL){					//Busca se aresta em comum ja foi impressa
				if(atual_a->arestaA == aux_a){
					nao_impresso = 1;
					break;
				}
				aux_a = aux_a->prox_vertice;
			}
			if (nao_impresso != 0){					//Faz a impressao do vertice e sua respectiva aresta se não foi impressa
				fprintf(output, "%s %s\n", atual_g->string, atual_a->arestaA->string);
			}
			atual_a = atual_a->prox_aresta;
		}
		atual_g = atual_g->prox_vertice;
	}
	return g;
}

//==========================================================================

int destroi_grafo(grafo g){
	grafo atual_g = g, prox_g;
	vertice atual_a, prox_a;

	if(g != NULL){									//Verifica se existe um grafo
		while(atual_g != NULL){						//Percorre todos os vertices do grafo e libera ponteiro
			atual_a = atual_g->arestaG;
			while(atual_a != NULL){					//Percorre as arestas do vertice atual e libera ponteiro
				prox_a = atual_a->prox_aresta;
				free(atual_a);
				atual_a = prox_a;
			}
			prox_g = atual_g->prox_vertice;
			free(atual_g);
			atual_g = prox_g;
		}
		return 1;									//Retorna 1 se grafo foi destruido
	} else {
		return 0;									//Retorna 0 caso não exista grafo a ser destruido
	}
}

//==========================================================================

grafo le_grafo(FILE *input){
	char v[1025] = {0};
	int c;
	int i = 0;
	vertice aux;
	grafo g, v1, v2;

	//Cria nodo cabeca
	g = malloc(sizeof(struct _grafo));
	g->string[0] = '\0';
	g->arestaG = NULL;
	g->prox_vertice = NULL;
	v1 = g->prox_vertice;
	c = getc(input);

	while ( c != EOF){								//Le caracter por caracter
		if ((c == ' ') || (c == '\t') || (c == '\n')){		//Ignora todos os whitespaces antes do vertice
			c = getc(input);
			continue;
		}
		/*================================================================
			Encontra o primeiro vertice v1 da linha*/
		v[i++] = (char)c;
		c = getc(input);
		while ((c != EOF) && (c != ' ') && (c != '\t') && (c != '\n')){
			v[i++] = (char)c;
			c = getc(input);
		}
		v[i] = '\0';
		//================================================================

		/*================================================================
			Ignora todos os whitespaces depois do vertice*/
		v1 = NULL;
		while(c == ' ' || c == '\t')				 
			{ c = getc(input); 
		}
		//================================================================

		/*================================================================
			Verifica se o vertice v1 ja foi inserido no grafo*/
		v1 = g;
		while((v1->prox_vertice != NULL) && (strcmp(v1->string, v))){
			v1 = v1->prox_vertice;
		}
		//================================================================

		/*================================================================
			Insere v1*/
		if (strcmp(v1->string, v) && v1->prox_vertice == NULL){				
			v1->prox_vertice = malloc(sizeof(struct _grafo));
			v1 = v1->prox_vertice;
			strcpy(v1->string, v);
			v1->arestaG = NULL;
			v1->prox_vertice = NULL;
		}
		//================================================================

		/*================================================================
			Verifica se possui +um vertice v2 na linha do arquivo*/
		i = 0;
		if(c == '\n'){ 
			c = getc(input);
			continue;
		}
		// Se encontra, guarda segundo vertice v2
		while ((c != EOF) && (c != ' ') && (c != '\t') && (c != '\n')){
			v[i++] =(char) c;
			c = getc(input);
		}
		v[i] = '\0';
		//================================================================

		/*================================================================
			Verifica se segundo vertice da linha ja foi inserido */
		v2 = g;
		while((v2->prox_vertice != NULL) && (strcmp(v2->string, v)!=0)){
			v2 = v2->prox_vertice;
		}
		//Insere vertice v2 inexistente no grafo 
		if ((strcmp(v2->string, v)!=0) && v2->prox_vertice == NULL){				
			v2->prox_vertice = malloc(sizeof(struct _grafo));
			v2 = v2->prox_vertice;
			strcpy(v2->string, v);
			v2->arestaG =  NULL;
			v2->prox_vertice = NULL;
		}

		aux = v1->arestaG;
		vertice anterior = aux;
		while((aux != NULL) && (aux->arestaA != v2)){
			anterior = aux;
			aux = aux->prox_aresta;
		}
		if (aux == NULL){
			if(v1->arestaG == NULL){
				v1->arestaG = malloc(sizeof(struct _grafo));
				aux = v1->arestaG;
			} else {
				anterior->prox_aresta = malloc(sizeof(struct _grafo));
				aux = anterior->prox_aresta;
			}

			aux->arestaA = v2;
			aux->prox_aresta = NULL;
			
			aux = v2->arestaG;
			v2->arestaG = malloc(sizeof(vertice));
			v2->arestaG->arestaA = v1;
			v2->arestaG->prox_aresta = aux;
		}
		//================================================================

		//Ignora whitespaces depois do vertice
		while(c == ' ' || c == '\t'){ c = getc(input); }

		//Verifica se possui um terceiro vertice na linha do arquivo
		if (c != '\n'){
			fprintf(stderr, "Formato de entrada incorreto\n");
			return NULL;
		}

		i = 0;
		c = getc(input);
	}
	return g;
}

//==========================================================================

unsigned int n_vertices(grafo g){
	grafo atual_g = g;
	unsigned int cont = 0;

	if(g != NULL){	
		atual_g = atual_g->prox_vertice;								
		while(atual_g != NULL){						
			cont++;
			atual_g = atual_g->prox_vertice;
		}
		return cont;									
	} else {
		return 0;									
	}
}

//==========================================================================

unsigned int n_arestas(grafo g){
	unsigned int cont = 0;
	grafo l1; 
	vertice l2;

	if(g != NULL){									
		for(l1 = g->prox_vertice; l1 != NULL; l1 = l1->prox_vertice){
			for(l2 = l1->arestaG; l2 != NULL; l2 = l2->prox_aresta){		
				cont++;
			}
		}
		return cont/2;									
	} else {
		return 0;									
	}
}

//==========================================================================

vertice primeiro_vertice(grafo g){
	grafo aux = g->prox_vertice;
	vertice v = aux->prox_vertice->arestaG;
	return v;
}

//==========================================================================

//vertice proximo_vertice(vertice v, grafo g){

//}