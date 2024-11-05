import sympy
from sympy import N #Para conseguir arredondar as casas decimais das expressões em string
import os #Limpar a tela

vetori = [0.25,0.75,1.25,1.5,2.0]
vetorv = [-0.45,-0.6,0.7,1.88,6.0]
estim = 1.15
vetorx = []
vetorfx = []

def Lagrange(vetorx,vetorfx,estim):
    n = len(vetorx)
    x = sympy.symbols('x')
    str = '' #Definindo a base da string que vai receber a função completa (Pn(x))
    for j in range(n): #Loops aninhados para montar as strings dos Ln(x)
        str_lx = '(1' #Definindo a base da string que recebe os Ln(x)
        for k in range(n):
            if (j != k): 
                str_lx += f'*(x-{vetorx[k]})' #Adicionando o númerador
                str_lx += f'*(1/({vetorx[j]}-{vetorx[k]}))' #Adicionando o denominador
        str_lx += ')' #Fechando a string que recebe os Ln(x)
        print(f'L{j}(x) = {N(sympy.simplify(str_lx),5)}') #Printando as strings de Ln(x) que o sympy simplificou e arredondou e arredondou em 5 casas
        str += f'+({vetorfx[j]}*{str_lx})' #Multiplicando os Ln(x) pelos fn(x) e guardando na string completa
    print(f'\nP{n-1}(x) = {N(sympy.simplify(str),5)}\n') #Printando a string do Pn(x) que o sympy simplificou e arredondou em 5 casas
    func_py = sympy.sympify(str) #Transformando a string em uma expressão simbólica do sympy
    fx = sympy.lambdify(x, func_py) #Transformando a expressão simbólica em uma função utilizável
    print(f'Para o valor estimado de {estim} A, a queda da voltagem é de {fx(estim):.5f} V!\n') #Printando o resultado

def Newton(vetorx,vetorfx,estim):
    n = len(vetorx)
    tabela = [[0.0 for _ in range(n)] for _ in range(n)] #Cria uma tabela n por n zerada
    for j in range(n):
        tabela[j][0] = vetorfx[j]  #Preenche a primeira linha com os valores de f(x)
    for k in range(1, n):
        for j in range(n - k):
            tabela[j][k] = (tabela[j + 1][k - 1] - tabela[j][k - 1])/(vetorx[j + k] - vetorx[j]) #Preenche a tabela com os operadores diferenças divididas

    str_produto = '(1' #Base da string que vai receber os produtos que compoem o polinômio
    str = f'{tabela[0][0]}' #Base da string do polinômio (a0 + a1*produto1 + a2*produto2 ...)
    for l in range(n-1):
        str_produto += f'*(x-{vetorx[l]})' #Produto em string que vai se incrementando (x-x0) -> (x-x0)*(x-x1) -> ...
        str += f'+({tabela[0][l+1]}*{str_produto}))' #Adicionando os termos vezes os produtos na string do polinômio
        print(f'a{l} = {tabela[0][l]:.5f}') #Printando a0,a1,a2,...
    print(f'a{l+1} = {tabela[0][l+1]:.5f}') #Printando o ultimo a
    print(f'\nP{n-1}(x) = {N(sympy.simplify(str),5)}\n') #Printando a string do Pn(x) que o sympy simplificou e arredondou em 5 casas
    x = sympy.symbols('x')
    func_py = sympy.sympify(str) #Transformando a string em uma expressão simbólica do sympy
    fx = sympy.lambdify(x, func_py) #Transformando a expressão simbólica em uma função utilizável
    print(f'Para o valor estimado de {estim} A, a queda da voltagem é de {fx(estim):.5f} V!\n') #Printando o resultado

i = True #Escolher método
while(i):
    os.system('cls')
    print('---------------- Interpolação Polinomial - Q3 - Queda de voltagem através de um resistor ----------------\n')
    print('Escolha o método a ser utilizado: ')
    print('1 - Forma de Lagrange')
    print('2 - Forma de Newton')
    escolha = input('\nDigite (1-2): ')
    if( (escolha == '1') or (escolha == '2') ):
        i = False

i = True #Escolher grau
while(i):
    os.system('cls')
    print('---------------- Interpolação Polinomial - Q3 - Queda de voltagem através de um resistor ----------------\n')
    n = input('Digite o grau do Polinômio(2-4): ')
    if((n == '2') or (n == '3') or (n == '4')):
        n = int(n) + 1
        i = False

os.system('cls') #Escolher valores
print('---------------- Interpolação Polinomial - Q3 - Queda de voltagem através de um resistor ----------------\n')
print('is da questão: x = ',vetori,'A')
print('Vs da questão: f(x) = ',vetorv,'V')
print('i da questão para a estimativa = ',estim, 'A\n')
for i in range(n):
    vetorx.append( float(input(f'Digite o {i+1}º valor da corrente (x{i+1}): ')) )
print()
for i in range(n):
    vetorfx.append( float(input(f'Digite o {i+1}º valor da voltagem (f(x{i+1})): ')) )
estim = float(input(f'\nDigite a corrente i para estimar a queda de V: '))
print()

if(escolha == '1' ): #Chamada das funções
    Lagrange(vetorx,vetorfx,estim)
else:
    Newton(vetorx,vetorfx,estim)