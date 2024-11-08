import numpy as np

# Função para resolver o sistema linear usando eliminação de Gauss
def resolver_meta_producao(A, b):
    A = np.array(A, dtype=float)
    b = np.array(b, dtype=float)
    
    # Número de variáveis (deve ser uma matriz quadrada)
    n = len(b)
    
    # Eliminação de Gauss para transformar A em uma matriz triangular superior
    for i in range(n):
        # Encontra o pivô (elemento máximo na coluna i a partir da linha i)
        max_row = i + np.argmax(abs(A[i:, i]))
        if A[max_row, i] == 0:
            return None  # Sistema não tem solução única ou é indeterminado

        # Troca a linha atual com a linha do pivô
        A[[i, max_row]] = A[[max_row, i]]
        b[i], b[max_row] = b[max_row], b[i]

        # Elimina as variáveis da linha atual abaixo do pivô
        for j in range(i + 1, n):
            fator = A[j, i] / A[i, i]
            A[j] -= fator * A[i]
            b[j] -= fator * b[i]

    # Substituição regressiva para encontrar a solução do sistema
    x = np.zeros(n)
    for i in range(n - 1, -1, -1):
        x[i] = (b[i] - np.dot(A[i, i + 1:], x[i + 1:])) / A[i, i]
    
    return x

# Coeficientes de cada componente (transistores, resistores, chips de computador)
# Cada linha representa a quantidade de cobre, zinco e vidro usada para fabricar um componente
A = [
    [4, 3, 2],  # Quantidade de cobre para cada componente
    [1, 3, 1],  # Quantidade de zinco para cada componente
    [2, 1, 3]   # Quantidade de vidro para cada componente
]

# Entrada do usuário para as quantidades disponíveis semanalmente
cobre = float(input("Digite a quantidade de cobre disponível: "))
zinco = float(input("Digite a quantidade de zinco disponível: "))
vidro = float(input("Digite a quantidade de vidro disponível: "))
b = [cobre, zinco, vidro]  # Quantidade de materiais disponíveis

# Chama a função para resolver o sistema
resultados = resolver_meta_producao(A, b)

if resultados is not None:
    t, r, c = resultados
    print("\nMeta de Produção para a Semana:")
    print(f"Transistores: {int(t)}")
    print(f"Resistores: {int(r)}")
    print(f"Chip de Computador: {int(c)}")
else:
    print("O sistema não possui uma solução única ou é inviável.")

#Aqui um exemplo de que resolver méta de produção serve para qualquer matriz quadrada
# cincoXcinco=[
#     [2,1,-1,3,2],
#     [4,-2,5,1,3],
#     [1,3,-3,2,1],
#     [5,2,2,-1,4],
#     [3,-1,4,3,-2]
# ]

# vetsolução=[10,5,-3,7,2]

# resultado=resolver_meta_producao(cincoXcinco,vetsolução)
# print(resultado)