#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <getopt.h>
#include <math.h>

int main( int argc, char **argv){
	int opt;
	char *arqOut = NULL, *x = NULL;
	char *teste = NULL;
	int flagArq = 0, y, maxIt;

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
				x = optarg;
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
			nx	: %s\n\
			ny	: %d\n\
			i 	: %d\n", x,y,maxIt);
	printf("Aqruivo de saída: ");
	if(flagArq == 1) printf("Sim: %s\n",arqOut);
	else printf("Não\n");
	*/
	float hy, hx;
	//hx = M_PI / x;
	//hy = M_PI / y; 

	return 0;
}