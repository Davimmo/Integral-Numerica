#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define MAX_ITER 1000      // N�mero m�ximo de itera��es
#define PRECISAO 0.0001    // Toler�ncia para converg�ncia

// Fun��o para verificar o Crit�rio das Linhas
bool criterio_das_linhas(int n, double MATRIZ_COEF[n][n]) {
	int i, j;
    for (i = 0; i < n; i++) {
        double soma = 0.0;
        for (j = 0; j < n; j++) {
            if (j != i) {
                soma += fabs(MATRIZ_COEF[i][j]); // recebe o valor absoluto
            }
        }
        if (fabs(MATRIZ_COEF[i][i]) <= soma) {
            return false;  // N�o atende ao crit�rio das linhas
        }
    }
    return true;  // Atende ao crit�rio das linhas
}

// Fun��o para verificar o Crit�rio de Sassenfeld
bool criterio_sassenfeld(int n, double MATRIZ_COEF[n][n]) {
    double beta[n];
    int i, j;
    
    for (i = 0; i < n; i++) {
        beta[i] = 0.0;
    }

    for (i = 0; i < n; i++) {
        double soma = 0.0;
        for (j = 0; j < n; j++) {
            if (j != i) {
                soma += fabs(MATRIZ_COEF[i][j]) * (j < i ? beta[j] : 1); //verifica se o elemento est� antes ou depois do elemento da diagonal principal
            }
        }
        beta[i] = soma / fabs(MATRIZ_COEF[i][i]);
        if (beta[i] >= 1) {
            return false;  // N�o atende ao crit�rio de Sassenfeld
        }
    }
    return true;  // Atende ao crit�rio de Sassenfeld
}

// Fun��o para resolver o sistema usando o M�todo de Gauss-Seidel
void gauss_seidel(int n, double MATRIZ_COEF[n][n], double VETOR_TERMOS_INDEP[n], double VETOR_VARIAVEIS[n]){
    int iteracao = 0, i, j;
    double erro = 0;
    
    do {
        erro = 0;  // Reseta o erro para a pr�xima itera��o 
        
        for (i = 0; i < n; i++) {
            double soma = 0;

            // Calcula a soma de MATRIZ_COEF[i][j] * VETOR_VARIAVEIS[j] para todos j exceto j == i
            for (j = 0; j < n; j++) {
                if (j != i) {
                    soma += MATRIZ_COEF[i][j] * VETOR_VARIAVEIS[j];
                }
            }   
            
            // Calcula o novo valor das inc�gnitas
			double VETOR_VARIAVEIS_novo;         
			
            if (MATRIZ_COEF[i][i] != 0) {
			    VETOR_VARIAVEIS_novo = (VETOR_TERMOS_INDEP[i] - soma) / MATRIZ_COEF[i][i];
			} else {
			    printf("Erro: Divis�o por zero na linha %d.\n", i);
			}

            // Calcula o erro como a diferen�a m�xima entre os valores antigos e novos
            erro = fmax(erro, fabs(VETOR_VARIAVEIS_novo - VETOR_VARIAVEIS[i]));

            // Atualiza o valor das inc�gnitas com o novo valor calculado para a pr�xima itera��o
            VETOR_VARIAVEIS[i] = VETOR_VARIAVEIS_novo;
        }
        iteracao++;
        
    } while (erro > PRECISAO && iteracao < MAX_ITER);
    
    if (iteracao == MAX_ITER) {
        printf("Metodo nao convergiu apos %d iteracoes.\n", MAX_ITER);
    } else {
        printf("Metodo convergiu em %d iteracoes.\n", iteracao);
        for (i = 0; i < n; i++) {
            printf("Corrente I[%d] = %.2f\n", i + 1, VETOR_VARIAVEIS[i]);
        }
    }    
}

int main() {
    int n, i = 0, j = 0;

    // Define o n�mero de malhas no sistema, uma inc�gnita para cada corrente de malha
    printf("Digite o numero de malhas: ");
    scanf("%d", &n);

    double MATRIZ_COEF[n][n], VETOR_TERMOS_INDEP[n], VETOR_VARIAVEIS[n];

    // Recebe a matriz de coeficientes
    printf("Digite a matriz dos coeficientes:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("MATRIZ_COEF[%d][%d]: ", i + 1, j + 1);
            scanf("%lf", &MATRIZ_COEF[i][j]);
        }
    }

    // Recebe o vetor de termos independentes
    printf("Digite o vetor dos termos independentes:\n");
    for (i = 0; i < n; i++) {
        printf("VETOR_TERMOS_INDEP[%d]: ", i + 1);
        scanf("%lf", &VETOR_TERMOS_INDEP[i]);
    }

    // Verifica o Crit�rio das Linhas
    if (!criterio_das_linhas(n, MATRIZ_COEF)) {
        printf("A matriz nao atende ao criterio das linhas. A convergencia pode nao ser garantida.\n");
    }

    // Verifica o Crit�rio de Sassenfeld
    if (!criterio_sassenfeld(n, MATRIZ_COEF)) {
        printf("A matriz nao atende ao criterio de Sassenfeld. A convergencia pode nao ser garantida.\n");
    }

    // Inicializa o vetor das vari�veis com uma estimativa inicial para cada corrente
    for (i = 0; i < n; i++) {
        VETOR_VARIAVEIS[i] = VETOR_TERMOS_INDEP[i] / MATRIZ_COEF[i][i];  // Aproxima��o inicial
    }

    // Chama a fun��o de resolu��o pelo m�todo de Gauss-Seidel
    gauss_seidel(n, MATRIZ_COEF, VETOR_TERMOS_INDEP, VETOR_VARIAVEIS);

    return 0;
}

