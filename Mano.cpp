#include "Mano.h"
#include <iostream>
using namespace std;

void Mano::agregarCarta(Carta c) { cartas.push_back(c); }

int Mano::calcularPuntos() const {
    int total = 0, ases = 0;
    for (const auto& c : cartas) {
        total += c.getPuntos();
        if (c.esAs()) ases++;
    }
    while (total > 21 && ases > 0) {
        total -= 10;
        ases--;
    }
    return total;
}

void Mano::mostrar(bool mostrarTodo) const {
    for (size_t i = 0; i < cartas.size(); ++i) {
        if (!mostrarTodo && i == 0)
            cout << "[Carta Oculta]\n";
        else
            cout << " - " << cartas[i].toString() << "\n";
    }
    if (mostrarTodo)
        cout << "Total: " << calcularPuntos() << "\n";
}

bool Mano::tieneBlackjack() const { return cartas.size() == 2 && calcularPuntos() == 21; }
bool Mano::estaEliminado() const { return calcularPuntos() > 21; }