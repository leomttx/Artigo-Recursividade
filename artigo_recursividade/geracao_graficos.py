import matplotlib.pyplot as plt

# Estruturas para armazenar os dados
minmax_iter = {'n': [], 'tempo': []}
minmax_rec = {'n': [], 'tempo': []}
fib_iter = {'n': [], 'tempo': []}
fib_rec = {'n': [], 'tempo': []}

# Leitura do arquivo gerado pelo C++
with open("resultados.txt", "r") as arquivo:
    for linha in arquivo:
        dados = linha.strip().split(";")

        algoritmo = dados[0]
        versao = dados[1]
        n = int(dados[2])
        tempo = float(dados[3].replace("ms", ""))

        if algoritmo == "MinMax":
            if versao == "Iterativo":
                minmax_iter['n'].append(n)
                minmax_iter['tempo'].append(tempo)
            else:
                minmax_rec['n'].append(n)
                minmax_rec['tempo'].append(tempo)

        elif algoritmo == "Fibonacci":
            if versao == "Iterativo":
                fib_iter['n'].append(n)
                fib_iter['tempo'].append(tempo)
            else:
                fib_rec['n'].append(n)
                fib_rec['tempo'].append(tempo)

# =======================
# Gráfico Min/Max
# =======================
plt.figure()
plt.plot(minmax_iter['n'], minmax_iter['tempo'], marker='o', label='Iterativo')
plt.plot(minmax_rec['n'], minmax_rec['tempo'], marker='o', label='Recursivo')
plt.xlabel("Tamanho do vetor (n)")
plt.ylabel("Tempo de execução (ms)")
plt.title("Desempenho do algoritmo Min/Max")
plt.legend()
plt.grid(True)
plt.savefig('comparacao_minmax.png')
plt.show()

# =======================
# Gráfico Fibonacci
# =======================
plt.figure()
plt.plot(fib_iter['n'], fib_iter['tempo'], marker='o', label='Iterativo')
plt.plot(fib_rec['n'], fib_rec['tempo'], marker='o', label='Recursivo')
plt.xlabel("Valor de n")
plt.ylabel("Tempo de execução (ms)")
plt.title("Desempenho do algoritmo Fibonacci")
plt.legend()
plt.grid(True)
plt.savefig('comparacao_fibonacci.png')
plt.show()
