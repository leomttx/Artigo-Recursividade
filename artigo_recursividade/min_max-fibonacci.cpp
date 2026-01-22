#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>

using namespace std;
using namespace chrono;

/*
   MIN / MAX
*/

// Iterativo
void minMaxIterativo(const vector<int>& v, int& min, int& max) { // O & serve para passar por referência o argumento
    min = max = v[0];
    for (size_t i = 1; i < v.size(); i++) { // size_t para evitar comparação entre signed e unsigned
        if (v[i] < min) min = v[i];
        if (v[i] > max) max = v[i];
    }
}

// Recursivo
void minMaxRecursivo(const vector<int>& v, int inicio, int fim, int& min, int& max) {
    if (inicio == fim) {
        min = max = v[inicio];
        return; // Caso base: apenas um elemento
    }

    int min1, max1;
    minMaxRecursivo(v, inicio + 1, fim, min1, max1); // É somado 1 para evitar reprocessar o elemento atual

    min = (v[inicio] < min1) ? v[inicio] : min1;
    max = (v[inicio] > max1) ? v[inicio] : max1;
}

/*
   FIBONACCI
*/

// Iterativo
long long fibonacciIterativo(int n) {
    if (n <= 1) return n;

    long long a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

// Recursivo
long long fibonacciRecursivo(int n) {
    if (n <= 1) return n;
    return fibonacciRecursivo(n - 1) + fibonacciRecursivo(n - 2);
}

/*
   FUNÇÃO AUXILIAR
*/

vector<int> gerarVetor(int n) {
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        v[i] = rand() % 10000; // Números aleatórios entre 0 e 9999
    }
    return v;
}

/*
   MAIN
*/

int main() {
    srand(time(NULL));

    int algoritmo, versao;
    char analisar;

    cout << "Escolha o algoritmo:\n";
    cout << "1 - Min/Max\n";
    cout << "2 - Fibonacci\n";
    cin >> algoritmo;

    cout << "\nEscolha a versao:\n";
    cout << "1 - Iterativa\n";
    cout << "2 - Recursiva\n";
    cin >> versao;

    cout << "\nDeseja realizar analise de desempenho? (s/n): ";
    cin >> analisar;

    ofstream arquivo("resultados.txt", ios::app); 

    if (algoritmo == 1) {
        int n;
        cout << "\nInforme o tamanho do vetor: ";
        cin >> n;

        if (analisar == 's' || analisar == 'S') {
            for (int i = 1; i <= 5; i++) {
                vector<int> v = gerarVetor(n * i); // Cria 5 vetores com tamanhos crescentes
                int min, max;

                auto inicio = high_resolution_clock::now();

                if (versao == 1) {
                    minMaxIterativo(v, min, max);
                } else {
                    minMaxRecursivo(v, 0, v.size() - 1, min, max);
                }

                auto fim = high_resolution_clock::now();
                double tempo = duration<double, milli>(fim - inicio).count();

                arquivo << "MinMax;"
                        << (versao == 1 ? "Iterativo;" : "Recursivo;")
                        << v.size() << ";"
                        << tempo << "ms\n";

                cout << "Tamanho: " << v.size()
                     << " | Tempo: " << tempo << " ms\n";
            }
        } else {
            vector<int> v = gerarVetor(n);
            int min, max;

            if (versao == 1)
                minMaxIterativo(v, min, max);
            else
                minMaxRecursivo(v, 0, v.size() - 1, min, max);

            cout << "Min: " << min << " | Max: " << max << endl;
        }
    }

    else if (algoritmo == 2) {
        int n;
        cout << "\nInforme o valor de n: ";
        cin >> n;

        if (analisar == 's' || analisar == 'S') {
            for (int i = 1; i <= 5; i++) {
                int valor = n * i;

                auto inicio = high_resolution_clock::now(); // Início da medição do tempo

                long long resultado;
                if (versao == 1)
                    resultado = fibonacciIterativo(valor);
                else
                    resultado = fibonacciRecursivo(valor);

                auto fim = high_resolution_clock::now(); // Fim da medição do tempo
                double tempo = duration<double, milli>(fim - inicio).count();

                arquivo << "Fibonacci;"
                        << (versao == 1 ? "Iterativo;" : "Recursivo;")
                        << valor << ";"
                        << tempo << "ms\n";

                cout << "n: " << valor
                     << " | Tempo: " << tempo << " ms\n";
            }
        } else {
            long long resultado;
            if (versao == 1)
                resultado = fibonacciIterativo(n);
            else
                resultado = fibonacciRecursivo(n);

            cout << "Resultado: " << resultado << endl;
        }
    }

    arquivo.close();
    cout << "\nResultados salvos em resultados.txt\n";

    return 0;
}
