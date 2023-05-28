#include <iostream>
#include <thread>
#include <queue>
#include <stack>
#include <random>
#include <chrono>

using namespace std;

int generarNumeroAleatorio(int min, int max) {
    static random_device rd;
    static mt19937 mt(rd());
    uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}

void cajeroFuncion(queue<int>& cola, stack<int>& pila) {
    while (true) {
        if (!cola.empty()) {
            int numero = cola.front();
            cola.pop();
            pila.push(numero);
            cout << "Cajero atendiendo al numero: " << numero << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }
    }
}

int main() {
    const int numCajas = 4;
    const int numNumeros = 200;
    const int minNumero = 1;
    const int maxNumero = 90;

   
    vector<queue<int>> colas(numCajas);

    vector<stack<int>> pilas(numCajas);

    vector<thread> cajeros;

    for (int i = 0; i < numCajas; i++) {
        cajeros.emplace_back(cajeroFuncion, ref(colas[i]), ref(pilas[i]));
    }

    for (int i = 0; i < numNumeros; i++) {
        int numero = generarNumeroAleatorio(minNumero, maxNumero);
        int caja = generarNumeroAleatorio(0, numCajas - 1);
        colas[caja].push(numero);
        cout << "Nuevo numero en la cola de la caja " << caja << ": " << numero << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

    for (auto& cajero : cajeros) {
        cajero.join();
    }

    for (int i = 0; i < numCajas; i++) {
        int suma = 0;
        while (!pilas[i].empty()) {
            int numero = pilas[i].top();
            pilas[i].pop();
            suma += numero;
        }
        cout << "Suma de numeros atendidos por el cajero: " << i << ": " << suma << endl;
    }

    return 0;
}
