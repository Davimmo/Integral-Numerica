import numpy as np

# Função para resolver o sistema de equações
def resolver_meta_producao(cobre, zinco, vidro):
    # Coeficientes do sistema de equações
    A = np.array([[4, 3, 2],    # Coeficientes de cobre
                  [1, 3, 1],    # Coeficientes de zinco
                  [2, 1, 3]])   # Coeficientes de vidro

    # Vetor de constantes (quantidade de materiais disponíveis)
    b = np.array([cobre, zinco, vidro])

    # Usando a função linalg.solve para resolver o sistema
    try:
        solucoes = np.linalg.solve(A, b)
        t, r, c = solucoes  # Soluções para transistor, resistor e chip de computador
        return t, r, c
    except np.linalg.LinAlgError:
        return None  # Retorna None se o sistema não tiver solução única

# Entrada do usuário para os materiais disponíveis
cobre = float(input("Digite a quantidade de cobre disponível: "))
zinco = float(input("Digite a quantidade de zinco disponível: "))
vidro = float(input("Digite a quantidade de vidro disponível: "))

# Chama a função para resolver o sistema
resultados = resolver_meta_producao(cobre, zinco, vidro)

if resultados:
    t, r, c = resultados
    print(f"\nMeta de Produção para a Semana:")
    print(f"Transistores: {int(t)}")
    print(f"Resistores: {int(r)}")
    print(f"Chip de Computador: {int(c)}")
else:
    print("O sistema não possui uma solução única ou é inviável.")

