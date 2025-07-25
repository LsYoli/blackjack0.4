#include "Crupier.h"
#include <iostream>
using namespace std;

void Crupier::recibirCarta(Carta c) { mano.agregarCarta(c); }

void Crupier::mostrarMano(bool mostrarTodo) const { mano.mostrar(mostrarTodo); }
bool Crupier::estaEliminado() const { return mano.estaEliminado(); }
int Crupier::getPuntos() const { return mano.calcularPuntos(); }

void Crupier::turno(Baraja& baraja) {
    while (getPuntos() < 17) {
        cout << "El crupier pide carta...\n";
        recibirCarta(baraja.repartir());
    }
    cout << "\nMano del Crupier:\n";
    mostrarMano();
}
