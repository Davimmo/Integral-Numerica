#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MAX_ITER 1000      // Número máximo de iterações
#define PRECISAO 0.0001    // Tolerância para convergência

// Função para verificar o Critério das Linhas
bool criterio_das_linhas(int n, double **MATRIZ_COEF) {
    int i, j;
    for (i = 0; i < n; i++) {
        double soma = 0.0;
        for (j = 0; j < n; j++) {
            if (j != i) {
                soma += fabs(MATRIZ_COEF[i][j]); // recebe o valor absoluto
            }
        }
        if (fabs(MATRIZ_COEF[i][i]) <= soma) {
            return false;  // Não atende ao critério das linhas
        }
    }
    return true;  // Atende ao critério das linhas
}

// Função para verificar o Critério de Sassenfeld
bool criterio_sassenfeld(int n, double **MATRIZ_COEF) {
    double *beta = (double *)malloc(n * sizeof(double));  // Aloca dinamicamente
    int i, j;
    
    if (beta == NULL) {  // Verifica se a alocação foi bem-sucedida
        printf("Erro: Falha na alocacao de memoria.\n");
        return false;
    }

    for (i = 0; i < n; i++) {
        beta[i] = 0.0;
    }

    for (i = 0; i < n; i++) {
        double soma = 0.0;
        for (j = 0; j < n; j++) {
            if (j != i) {
                soma += fabs(MATRIZ_COEF[i][j]) * (j < i ? beta[j] : 1);
            }
        }
        beta[i] = soma / fabs(MATRIZ_COEF[i][i]);
        if (beta[i] >= 1) {
            free(beta);  // Libera memória antes de sair
            return false;
        }
    }
    
    free(beta);  // Libera memória após uso
    return true;
}

 
// Função para resolver o sistema usando o Método de Gauss-Seidel
void gauss_seidel(int n, double **MATRIZ_COEF, double *VETOR_TERMOS_INDEP, double *VETOR_VARIAVEIS) {
    int iteracao = 0, i, j;
    double erro = 0;
    
    do {
        erro = 0;  // Reseta o erro para a próxima iteração 
        
        for (i = 0; i < n; i++) {
            double soma = 0;

            // Calcula a soma de MATRIZ_COEF[i][j] * VETOR_VARIAVEIS[j] para todos j exceto j == i
            for (j = 0; j < n; j++) {
                if (j != i) {
                    soma += MATRIZ_COEF[i][j] * VETOR_VARIAVEIS[j];
                }
            }   
            
            // Calcula o novo valor das incógnitas
            double VETOR_VARIAVEIS_novo;         
            
            if (MATRIZ_COEF[i][i] != 0) {
                VETOR_VARIAVEIS_novo = (VETOR_TERMOS_INDEP[i] - soma) / MATRIZ_COEF[i][i];
            } else {
                printf("Erro: Divisão por zero na linha %d.\n", i);
                return;
            }

            // Calcula o erro como a diferença máxima entre os valores antigos e novos
            erro = fmax(erro, fabs(VETOR_VARIAVEIS_novo - VETOR_VARIAVEIS[i]));

            // Atualiza o valor das incógnitas com o novo valor calculado para a próxima iteração
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
    int n, i, j;

    // Define o número de malhas no sistema, uma incógnita para cada corrente de malha
    printf("Digite o numero de malhas: ");
    scanf("%d", &n);

    // Aloca a matriz de coeficientes e os vetores
    double **MATRIZ_COEF = (double **)malloc(n * sizeof(double *));
    for (i = 0; i < n; i++) {
        MATRIZ_COEF[i] = (double *)malloc(n * sizeof(double));
    }
    double *VETOR_TERMOS_INDEP = (double *)malloc(n * sizeof(double));
    double *VETOR_VARIAVEIS = (double *)malloc(n * sizeof(double));

    // Recebe a matriz de coeficientes
    printf("Digite a matriz dos coeficientes:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("Elemento na posicao [%d][%d]: ", i + 1, j + 1);
            scanf("%lf", &MATRIZ_COEF[i][j]);
        }
    }

    // Recebe o vetor de termos independentes
    printf("Digite o vetor dos termos independentes:\n");
    for (i = 0; i < n; i++) {
        printf("VETOR_TERMOS_INDEP[%d]: ", i + 1);
        scanf("%lf", &VETOR_TERMOS_INDEP[i]);
    }

    // Verifica o Critério das Linhas
    if (!criterio_das_linhas(n, MATRIZ_COEF)) {
        printf("A matriz nao atende ao criterio das linhas. A convergencia pode nao ser garantida.\n");
    }

    // Verifica o Critério de Sassenfeld
    if (!criterio_sassenfeld(n, MATRIZ_COEF)) {
        printf("A matriz nao atende ao criterio de Sassenfeld. A convergencia pode nao ser garantida.\n");
    }

    // Inicializa o vetor das variáveis com uma estimativa inicial para cada corrente
    for (i = 0; i < n; i++) {
        VETOR_VARIAVEIS[i] = VETOR_TERMOS_INDEP[i] / MATRIZ_COEF[i][i];  // Aproximação inicial
    }

    // Chama a função de resolução pelo método de Gauss-Seidel
    gauss_seidel(n, MATRIZ_COEF, VETOR_TERMOS_INDEP, VETOR_VARIAVEIS);

    // Libera a memória alocada
    for (i = 0; i < n; i++) {
        free(MATRIZ_COEF[i]);
    }
    free(MATRIZ_COEF);
    free(VETOR_TERMOS_INDEP);
    free(VETOR_VARIAVEIS);

    return 0;
}
