#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void printarValores(double *vetor, int tam,double margem) {
	int i;
	printf("\nValores de f(x): { ");
	for (i=0;i<tam;i++) {
		printf("%.2lf ",vetor[i]);
	}
	printf("} m \n");
	printf("Distância da margem: %.2lf m\n",margem);
}

void Trapezio(double *vetor, int tam, double x) {
	double h, somafxs;
	int i;
	system("cls");
	printf("---------------- Integração Numérica - Q4 - Determinar a área da seção reta de um rio com 11 pontos ----------------\n");
	printf("\nRegra dos Trapézios Composta:\n");
	h = (x/(tam-1));
	somafxs = 0;
	for(i=1;i<tam-1;i++) {
		somafxs += vetor[i];
	}
	somafxs *= 2;
	somafxs += vetor[0];
	somafxs += vetor[tam-1];
	somafxs *= (h/2);
	printf("\nA área da seção reta é de: %.2lf m²\n", somafxs);
}

void Simpson(double *vetor, int tam, double x) {
	double h, somafxs, somafxsp, somafxsi;
	int i;
	system("cls");
	printf("---------------- Integração Numérica - Q4 - Determinar a área da seção reta de um rio com 11 pontos ----------------\n");
	printf("\nRegra de 1/3 de Simpson Repetida:\n");
	h = (x/(tam-1));
	somafxs = (vetor[0] + vetor[tam-1]);
	somafxsi = 0;
	for(i=1;i<tam-1;i+=2) {
		somafxsi += vetor[i];
	}
	somafxsp = 0;
	for(i=2;i<tam-2;i+=2) {
		somafxsp += vetor[i];
	}
	somafxs += (4*somafxsi);
	somafxs += (2*somafxsp);
	somafxs *= (h/3);
	printf("\nA área da seção reta é de: %.2lf m²\n", somafxs);
}

int main(void) {
	
	int i, pos;
	char c;
	double vetorfx[] = {0,1.8,2,4,4,6,4,3.6,3.4,2.8,0};
	double margem = 20;
	int tam = sizeof(vetorfx)/sizeof(double);
	
	setlocale(LC_ALL, "Portuguese");
	printf("---------------- Integração Numérica - Q4 - Determinar a área da seção reta de um rio com 11 pontos ----------------\n");
	
	i=1;
	while(i) {
		c = 0;
		printarValores(vetorfx,tam,margem);
		printf("\nDeseja modificar algum valor? (s/n): ");
		scanf("%c",&c);
		setbuf(stdin, NULL);
		if( (c == 'N') || (c == 'n') ) {
			i=0;
		}
		else {
			if( (c == 'S') || (c == 's') ) {
				printf("\nDigite a posição do valor:\n(1-11) - Valores de f(x)\n(12) - Distância da margem\n\nDigite: ");
				scanf("%d", &pos);
				setbuf(stdin, NULL);
				if(pos>=1 && pos<=11) {
					printf("\nDigite o novo valor: ");
					scanf("%lf",&vetorfx[pos-1]);
					setbuf(stdin, NULL);
				}else {
					if(pos==12) {
						printf("\nDigite o novo valor: ");
						scanf("%lf",&margem);
						setbuf(stdin, NULL);					
					}	
				}
			}
		}
		system("cls");
		printf("---------------- Integração Numérica - Q4 - Determinar a área da seção reta de um rio com 11 pontos ----------------\n");	
	}
	
	i=1;
	while(i) {
		system("cls");
		printf("---------------- Integração Numérica - Q4 - Determinar a área da seção reta de um rio com 11 pontos ----------------\n");	
		printf("\nEscolha o método de integração numérica (1-2):\n 1 - Trapézios Composta\n 2 - 1/3 de Simpson Repetida\n\nDigite: ");
		scanf("%c",&c);
		setbuf(stdin, NULL);
		if(c == '1') {
			i=0;
			Trapezio(vetorfx,tam,margem);
		}else {
			if(c == '2') {
				i=0;
				Simpson(vetorfx,tam,margem);
			}
		}
	}
	printf("\nPressione qualquer tecla para fechar...\n");
	getchar();
	return 0;
}
