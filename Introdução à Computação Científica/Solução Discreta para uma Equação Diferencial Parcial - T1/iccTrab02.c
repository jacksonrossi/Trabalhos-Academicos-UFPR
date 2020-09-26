#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include "utils.h"
#include "SistemasLineares.h"
#include <getopt.h>

#define M_PI 3.14159265358979323846

// Inicializa SL
void inicializaSistLinear (SistLinear_t *SL)
{
  //static double invRandMax = 1.0 / (double)RAND_MAX;
  // inicializa a matriz A
  int tam = (SL->nx - 1 )*(SL->ny - 1);
  for (unsigned int i=0; i<tam; ++i){
     for (unsigned int j=0; j<tam; ++j)
     {
        SL->A[i*tam+j] = 0.0;
        //printf("%.2f  ",SL->A[i*tam+j] );
     }
     //printf("\n\n");
  }
  // inicializa vetores b e x
  for (unsigned int i=0; i<tam; ++i)
  {
     SL->b[i] = 0.0;
     SL->x[i] = 0.0;
  }
}



int main (int argc, char *argv[]) 
{
  
  double norma;

  /*=========================== Le os parametros ===========================*/
  int opt;
  char *arqOut = NULL;
  char *teste = NULL;
  int flagArq = 0, x, y, maxIt;

  const struct option stopcoes[] = {
    {"nx", required_argument, 0, 'x'},
    {"ny", required_argument, 0, 'y'},
    {"maxIt", required_argument, 0, 'i'},
    {"arqOut", optional_argument, 0, 'o'},
    {0, 0, 0, 0},
  };

  while((opt = getopt_long(argc, argv, "nx:ny:i:o:", stopcoes, NULL)) > 0){
    switch(opt){
      case 'n':
        break;
      case 'x': /* opção -nx */
        x = atoi(optarg);
        break;
      case 'y': /* opção -ny */
        y = atoi(optarg);
        break;
      case 'i':  /* opção -i */
        maxIt = atoi(optarg);
        break;
      case 'o':  /* opção -o */
        arqOut = optarg;
        
        flagArq = 1;
        break;
      default:
        fprintf(stderr, "Opção inválida ou faltando argumento\n");
        return -1;
    }
  } 
  /*printf("Suas opções: \n\
      nx  : %s\n\
      ny  : %d\n\
      i   : %d\n", x,y,maxIt);
  printf("Aqruivo de saída: ");
  if(flagArq == 1) printf("Sim: %s\n",arqOut);
  else printf("Não\n");
  */
  /*=====================================================================*/

  /*
  unsigned int nx, ny, i;
  nx = atoi(argv[2]);
  ny = atoi(argv[4]);
  i = atoi(argv[6]);
  */

  SistLinear_t *SL;
  unsigned iteracoes;

  SL = alocaSistLinear(x, y);
  SL->nx = x;
  SL->ny = y;

  //*srand(20191);
  
  inicializaSistLinear(SL);

  /*=====================================================================*/
  int i, j, k;
  real_t hx, hy;

  hx = M_PI / x;
  hy = M_PI / y;

  int tamLin = (x-1)*(y-1);
  int tamMat = tamLin*tamLin;
  int n = x-1;

  int pLinha = y-1;
  int pColuna = x-1;

  //printf("---------------- Principal ----------------\n");
  for(k = 0; k < tamLin; k++) // Diagonal Principal
    SL->A[k*tamLin + k] = 4*hy*hy+4*hx*hx+8*M_PI*M_PI*hx*hx*hy*hy;
 /*
  for(j = 0; j < tamLin; j++){
    for(i = 0; i < tamLin; i++){
      printf("%.2f\t ", SL->A[j*tamLin+i]);
    }
    printf("\n");
  }
  printf("\n\n" );
*/
  //printf("---------------- Superior ----------------\n");
  for(k = 0; k < tamLin-1; k++) // Diagonal Superior
    SL->A[k*tamLin + k + 1] = hx*hy*hy-2*hy*hy;
 /* for(j = 0; j < tamLin; j++){
    for(i = 0; i < tamLin; i++){
      printf("%.2f\t ", SL->A[j*tamLin+i]);
    }
    printf("\n");
  }
  printf("\n\n" );
*/
  //printf("---------------- Inferior ----------------\n");
  for(k = 1; k < tamLin; k++) // Diagonal Inferior
    SL->A[k*tamLin + k - 1] = -2*hy*hy-hx*hy*hy;
 /* for(j = 0; j < tamLin; j++){
    for(i = 0; i < tamLin; i++){
      printf("%.2f\t ", SL->A[j*tamLin+i]);
    }
    printf("\n");
  }
  printf("\n\n" );
*/
  printf("------------- Superior Afastada -------------\n");
  for(k = 0; k < (pLinha - 1)* pColuna; ++k){   // Diagonal Superior Afastada
  	int m1 = pColuna*k;
  	int m2 = (pColuna*k)+1;
  	int m3 = pColuna*m2;
    SL->A[(k*pLinha) + (pColuna*((pColuna*k)+1))] = hx*hx*hy-2*hx*hx;
    printf("Posição %d : %f\n",(k*pLinha) + (pColuna*((pColuna*k)+1)), SL->A[(k*pLinha) + (pColuna*((pColuna*k)+1))]);
    printf("M1: %d, M2: %d, M3: %d\n\n",m1,m2,m3 );
  }
/*  for(j = 0; j < tamLin; j++){
    for(i = 0; i < tamLin; i++){
      printf("%.2f\t ", SL->A[j*tamLin+i]);
    }
    printf("\n");
  }
*/
  printf("\n\n" );


  printf("------------- Inferior Afastada -------------\n");
  for(k = tamLin*3; k < tamLin; k+= n+1) // Diagonal Inferior Afastada
    SL->A[k] = -2*hx*hx+hx*hx*hy;
  for(j = 0; j < tamLin; j++){
    for(i = 0; i < tamLin; i++){
      printf("%.2f\t  ", SL->A[j*tamLin+i]);
    }
    printf("\n");
  }
  printf("\n" );



/*
  for(j = 0; j < x-1; j++){
    for(i = 0; i < y-1; i++){
      printf("%.2f ", SL->A[i*tamMat+j]);
    }
    printf("\n");
  }
  printf("\n\n" );
*/
  /*=====================================================================*/




/*

  double tempo_inicial, tempo_final;
  printf("#-----------------------------------------\n# Ordem: %d\n", n );
  printf("# Metodo    , ret, norma    ,  iteracoes, tempo\n#-----------------------------------------\n");

  tempo_inicial = timestamp();
  //inicializaSistLinear(sistema);
  ret = gaussSeidel (sistema, x, erro);
  tempo_final = timestamp();
  norma = normaL2Residuo(sistema);
  printf("Gauss Seidel, Norma: %.6g,Tempo: %.5g\n", norma, tempo_final-tempo_inicial);

  // tempo_inicial = timestamp();
  // normaL2Residuo (sistema);
  // tempo_final = timestamp();
  // printf("%d %g\n",n,tempo_final - tempo_inicial);
*/

  liberaSistLinear(SL);

  return 0;
}

