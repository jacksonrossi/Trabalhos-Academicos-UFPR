/**
 * \file SistemasLineares.c
 * \author Jackson Rossi Borguezani
 * \mainpage Métodos para achar a solução de um sistema linear
 * \section introSec ReadMe
 * Trabalho 1 | ICC - Prof. Daniel W. |
 * Aluno: Jackson Rossi Borguezani GRR20176573.
 * Métodos para encontrar uma solução para um sistema linear utilizando Guass-Jordan, Gauss-Jacobi e Gauss-Saidel.
 * \brief Arquivo que define os métodos de calcular uma solução para um sistema linear e calcular a norma do resíduo L2.
 *
 * \brief ** OBS: Adicionar -lm no makefile para compilar utilizando a biblioteca math.h **
 * \date 20 abr 2019
 *
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "utils.h"
#include "SistemasLineares.h"

//-------------------------------------------------------------------
//
//  Não alterar esta parte do código.
//
/// Alocaçãoo de memória
SistLinear_t* alocaSistLinear (unsigned int nx, unsigned int ny)
{
	SistLinear_t *SL = (SistLinear_t *) malloc(sizeof(SistLinear_t));
	int tam = (nx-1)*(ny-1)*(nx-1)*(ny-1);
	int t = (nx-1)*(ny-1);
	if ( SL ) 
	{
		SL->A = (real_t *) malloc(tam* sizeof(real_t));
		SL->b = (real_t *) malloc((tam+1) * sizeof(real_t));
		SL->x = (real_t *) malloc((tam+1) * sizeof(real_t));
		if (!(SL->A) || !(SL->b) || !(SL->x))
			liberaSistLinear(SL);
	}

	return (SL);
}

/// Liberação de memória
void liberaSistLinear (SistLinear_t *SL)
{
	free(SL->A);
	free(SL->b);
	free(SL->x);
	free(SL);
}
//-------------------------------------------------------------------

/*!
	\brief Cálculo da norma L2 do resíduo da solução encontrada
	*
	\param SL: Sistema Linear passado como parâmetro
	*
	\details A função utiliza a possível solução encontrada para calcular um erro e comparar a tolerância do erro EPS definido.
	*
*/
// Calcula a normaL2 do resíduo
double normaL2Residuo(SistLinear_t *SL)
{
	real_t *R, *Ai, *Bi, *Xi, aux, soma, modR, tam;
	int nx, ny, i,j;
	Ai = SL->A;
	Bi = SL->b;
	Xi = SL->x;
	nx = SL->nx;
	ny = SL->ny;
	tam = (nx-1)*(ny-1);

	R = (real_t *) malloc (tam * sizeof(real_t));

	//---- Calcula o resíduo ----
	for (i=1; i<tam; i++){
		aux = 0.0;
		for (j=1; j<tam; j++){
			aux += Ai[i*tam+j]*Xi[i];
		}
		R[i] = Bi[i] - aux;
	}
	//---- Calcula a soma dos termos ao quadrado do resíduo ----
	soma = 0.0;
	for(i=0; i<tam; i++){
		soma += fabs(R[i]*R[i]); 
	}
	free(R);
	//---- Retorna a raíz quadrada ----
	return sqrt(soma);
}

/*!
	\brief Método de Gauss-Seidel
	*
	\param SL: Sitema linear passado como parâmetro
	*
	\param eps: Erro máximo da norma em x
	*
	\param normaL2: Norma L2 do resíduo da solução encontrada
	*
	\param iter: Número de iterações
	*
	\details  Esse método faz uso da ideia de que, no método de Jacobi, cada novo valor obtido é melhor do que seu antecessor. Assim, ele utiliza os valores já calculados na iteração atual.
	*
	\details Erros possíveis no método: 
	*
	erro (-1) DIVISÃO POR ZERO: Ocorre caso o termo que divide o somatório seja zero.
	*	
	erro (-2) NÃO CONVERGÊNCIA / ATINGIR MÁAXIMO DE ITERAÇÕES: Esse erro ocorre quando atinge o número máximo de interações, caso tenha chegado no numero maximo de interações e não retornou 0, o erro da solução estimada esta maior que o erro permitido.
	*
*/
// Método de Gauss-Seidel
int gaussSeidel (SistLinear_t *SL, double eps)
{
	int i, j, k, l, n, status = 0;
	real_t *Xk1, somatorio, erro, maior, aux;
	real_t *Ai, *Bi, *Xi;
	
	//*iter = 0;
	double normaL2 = 0.0;
	Ai = SL->A;
	Bi = SL->b;
	Xi = SL->x;
	n = SL->nx;
	Xk1 = (real_t *) malloc (n * sizeof(real_t));

	for(k = 0; k < MAXIT; k++){
	// 	printf("\n\n----- Iteracao %d -----\n", k);
		for(i = 0; i < n; i++){
			somatorio = 0.0;
			// cálculo dos somatórios
			for(j = 0; j < i; j++)
				somatorio += Ai[i*n+j] * Xk1[j];
			for(j = i+1; j < n; j++)
				somatorio += Ai[i*n+j] * Xi[j];
			// ------	
			if(Ai[i*n+i] == 0){
				fprintf(stderr, "Erro (-1)\n");
				free(Xk1);
				status = -1;
				return (status);
			}
			Xk1[i] = (Bi[i] - somatorio)/Ai[i*n+i];
		}
		//----Cálculo do Erro ----
		maior = fabs(Xk1[0] - Xi[0]);
		for(l = 1; l < n; l++){
			aux = fabs(Xk1[l] - Xi[l]);
			if(aux > maior)
				maior = aux;
		}
		erro = maior;
		//memcpy(Xi, Xk1, n * sizeof(double)); // X = Xk1;
		for (int y = 0; y < n; y++){
			Xi[y] = Xk1[y];
		}
		//*iter++;
		if(erro < EPS){
			normaL2 = normaL2Residuo(SL);
			free(Xk1);
			return status;
		}
	}
	if(k >= MAXIT){
		fprintf(stderr, "Erro (-2)\n" );
		status = -2;
	}
	normaL2 = normaL2Residuo(SL);
	free(Xk1);
	return status;
}