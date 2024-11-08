#include <stdio.h> //funções de entrada e saída padrões
#include <stdlib.h> //funções diversas padrões como o system("cls");
#include <locale.h> //biblioteca para usar caracteres especiais

void printarValores(double *vetor, int tam,double margem) { //função para printar o vetor e a distância da margem
	int i;
	printf("\nValores de f(x): { ");
	for (i=0;i<tam;i++) { 
		printf("%.2lf ",vetor[i]); //loop para printar o vetor
	}
	printf("} m \n");
	printf("Distância da margem: %.2lf m\n",margem); //printar a margem
}

void Trapezio(double *vetor, int tam, double x) { //executar trapézios
	double h, somafxs; //"altura" de cada subintervalo e soma dos f(x) para colocar na formula
	int i; //variavél de controle
	system("cls"); //limpar a tela
	printf("---------------- Integração Numérica - Q4 - Determinar a área da seção reta de um rio com 11 pontos ----------------\n");
	printf("\nRegra dos Trapézios Composta:\n");
	h = (x/(tam-1)); //"altura" de cada subintervalo (distância da margem/número de subintervalos)
	somafxs = 0; //preparando o somador
	for(i=1;i<tam-1;i++) {
		somafxs += vetor[i]; //somando todos os elementos do vetor, menos o primeiro e o ultimo
	}
	somafxs *= 2; //multiplicando os elementos somados por 2
	somafxs += vetor[0]; //adicionando o primeiro elemento
	somafxs += vetor[tam-1]; //adicionando o ultimo elemento
	somafxs *= (h/2); //multiplicando tudo por h/2
	printf("\nA área da seção reta é de: %.2lf m²\n", somafxs); //printando o resultado
}

void Simpson(double *vetor, int tam, double x) { //executar simpson
	double h, somafxs, somafxsp, somafxsi; //"altura" do subintervalo, somador total, somador de termos pares, somador de termos impares
	int i; //variável de controle
	system("cls"); //limpar a tela
	printf("---------------- Integração Numérica - Q4 - Determinar a área da seção reta de um rio com 11 pontos ----------------\n");
	printf("\nRegra de 1/3 de Simpson Repetida:\n");
	h = (x/(tam-1)); //"altura" de cada subintervalo (distância da margem/número de subintervalos)
	somafxs = (vetor[0] + vetor[tam-1]); //iniciando o somador total com a soma do primeiro e do ultimo elemento do vetor
	somafxsi = 0; //preparando o somador de impares
	for(i=1;i<tam-1;i+=2) {
		somafxsi += vetor[i]; //loop para somar todos os termos impares do vetor
	}
	somafxsp = 0; //preparando o somador de pares
	for(i=2;i<tam-2;i+=2) {
		somafxsp += vetor[i]; //loop para somar todos os termos pares do vetor
	}
	somafxs += (4*somafxsi); //adicionando no somador total os termos impares vezes 4
	somafxs += (2*somafxsp); //adicionando no somador total os termos pares vezes 2
	somafxs *= (h/3); //multiplicando tudo por h/3
	printf("\nA área da seção reta é de: %.2lf m²\n", somafxs); //printando o resultado
}

int main(void) {
	
	int i, pos; //variáveis auxiliares
	char c; //variável auxilar
	double vetorfx[] = {0,1.8,2,4,4,6,4,3.6,3.4,2.8,0}; //pontos da questão em vetor
	double margem = 20; //margem da questão
	int tam = sizeof(vetorfx)/sizeof(double); //tamanho do vetor
	
	setlocale(LC_ALL, "Portuguese"); //para usar acentos e ç
	printf("---------------- Integração Numérica - Q4 - Determinar a área da seção reta de um rio com 11 pontos ----------------\n");
	
	i=1; //primeiro loop para permitir a modificação dos pontos e da distância da margem
	while(i) {
		c = 0;
		printarValores(vetorfx,tam,margem); //printar os dados do vetor e margem
		printf("\nDeseja modificar algum valor? (s/n): ");
		scanf("%c",&c);
		setbuf(stdin, NULL); //limpar buffer do teclado
		if( (c == 'N') || (c == 'n') ) {
			i=0;
		}
		else {
			if( (c == 'S') || (c == 's') ) {
				printf("\nDigite a posição do valor:\n(1-11) - Valores de f(x)\n(12) - Distância da margem\n\nDigite: ");
				scanf("%d", &pos); //escolher a posição do valor que vai ser modificado
				setbuf(stdin, NULL); //limpar buffer do teclado
				if(pos>=1 && pos<=11) {
					printf("\nDigite o novo valor: ");
					scanf("%lf",&vetorfx[pos-1]); //modificar valor do vetor
					setbuf(stdin, NULL); //limpar buffer do teclado
				}else {
					if(pos==12) {
						printf("\nDigite o novo valor: ");
						scanf("%lf",&margem); //modificar valor distância da margem
						setbuf(stdin, NULL); //limpar buffer do teclado			
					}	
				}
			}
		}
		system("cls"); //limpar a tela
		printf("---------------- Integração Numérica - Q4 - Determinar a área da seção reta de um rio com 11 pontos ----------------\n");	
	}
	
	i=1; //segundo loop para escolher o método de integração
	while(i) {
		system("cls"); //limpar a tela
		printf("---------------- Integração Numérica - Q4 - Determinar a área da seção reta de um rio com 11 pontos ----------------\n");	
		printf("\nEscolha o método de integração numérica (1-2):\n 1 - Trapézios Composta\n 2 - 1/3 de Simpson Repetida\n\nDigite: ");
		scanf("%c",&c); //escolha do método
		setbuf(stdin, NULL); //limpar buffer do teclado
		if(c == '1') {
			i=0;
			Trapezio(vetorfx,tam,margem); //chamada da integração por trapézios
		}else {
			if(c == '2') {
				i=0;
				Simpson(vetorfx,tam,margem); //chamada da integração por simpson
			}
		}
	}
	printf("\nPressione qualquer tecla para fechar...\n");
	getchar(); //manter a tela do prompt aberta até pressionar alguma tecla
	return 0;
}
