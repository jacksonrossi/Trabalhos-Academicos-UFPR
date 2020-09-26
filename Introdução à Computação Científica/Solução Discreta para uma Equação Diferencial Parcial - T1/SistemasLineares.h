#ifndef __SISLINEAR_H__
#define __SISLINEAR_H__

// Parâmetros para teste de convergência
#define MAXIT 100
#define EPS 1.0e-4

#define DIAG 32


typedef double real_t;

typedef struct {
  real_t *A; // coeficientes
  real_t *b; // termos independentes
  real_t *x;
  unsigned int nx; // tamanho nx
  unsigned int ny; //tamanho ny
} SistLinear_t;

// Alocaçao e desalocação de memória
SistLinear_t* alocaSistLinear (unsigned int nx, unsigned int ny);
void liberaSistLinear (SistLinear_t *SL);
void inicializaSistLinear (SistLinear_t *SL);

// Calcula a normaL2 do resíduo
double normaL2Residuo(SistLinear_t *SL);

// Método de Gauss-Seidel
int gaussSeidel (SistLinear_t *SL, real_t erro);

#endif // __SISLINEAR_H__

