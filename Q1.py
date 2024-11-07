import numpy as np

# Dados dos pontos (x, y)
x = np.array([0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20])
y = np.array([0, 1.8, 2, 4, 4, 6, 4, 3.6, 3.4, 2.8, 0])

# Calculando a área usando a Regra do Trapézio
def trapezoidal_rule(x, y):
    h = x[1] - x[0]  # Espaçamento entre os pontos
    area = 0.5 * h * (y[0] + 2 * sum(y[1:-1]) + y[-1])
    return area

# Calculando a área usando a Regra de Simpson
def simpsons_rule(x, y):
    if len(x) % 2 == 0:
        raise ValueError("Simpson's rule requires an odd number of intervals (even number of segments).")
    
    h = x[1] - x[0]  # Espaçamento entre os pontos
    n = len(x) - 1
    area = h / 3 * (y[0] + 2 * sum(y[2:n-1:2]) + 4 * sum(y[1:n:2]) + y[-1])
    return area

# Calculando as áreas
area_trapezoidal = trapezoidal_rule(x, y)
area_simpson = simpsons_rule(x, y)

print(f"Área usando a Regra do Trapézio: {area_trapezoidal:.2f} m²")
print(f"Área usando a Regra de Simpson: {area_simpson:.2f} m²")