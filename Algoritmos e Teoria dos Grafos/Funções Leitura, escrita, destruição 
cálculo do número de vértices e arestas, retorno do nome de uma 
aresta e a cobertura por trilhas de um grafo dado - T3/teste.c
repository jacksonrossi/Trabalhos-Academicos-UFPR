#include <stdio.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void) {

  FILE *stdin = fopen("petersen.txt", "r");	
	if (!stdin){
		perror("Erro ao abrir arquivo .txt\n");
		return 1;
	}

  grafo g = le_grafo(stdin);
  
  if ( !g )

    return 1;
	fclose(stdin);

  //printf ("O coeficiente de agrupamento do grafo é %f\n", coeficiente_agrupamento_grafo(g));

  FILE *stdout = fopen("saida", "w+");
  if (!stdout){
    perror("Erro ao criar arquivo saida\n");
    return 1;
  }

  
//=================================================
  unsigned int vertices = n_vertices(g);

  if(vertices != 0){
    fprintf(stderr, "%d vértices\n",vertices);
  }else{
    fprintf(stderr, "Grafo vasio\n");
  }
//=================================================
  unsigned int arestas = n_arestas(g);
  if(arestas != 0){
    fprintf(stderr, "%d arestas\n",arestas);
  }else{
    fprintf(stderr, "Grafo vasio\n");
  }
//=================================================
  //char name[3] = "k";
  //vertice busca = vertice_nome(g,name);
//=================================================
  /*
  if(busca != NULL){
    char *v = nome(busca);
    printf(": %s\n",v ); 
  }else{
    printf("Nao encontrado\n");
  }
*/
  //vertice **cobertura;
  //printf("aqui fora\n");
//=================================================
  vertice first;
  first = primeiro_vertice(g);
  grafo f;
  f = first->arestaA;
  printf("Primeiro vértice: %s\n",f->string);
  
  g = escreve_grafo(stdout, g);
  fclose(stdout);
  return ! destroi_grafo(g);
}