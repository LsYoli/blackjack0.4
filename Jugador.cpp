#include "Jugador.h"
#include <iostream>
using namespace std;

void Jugador::recibirCarta(Carta c) { mano.agregarCarta(c); }
void Jugador::mostrarMano() const { mano.mostrar(); }
bool Jugador::estaEliminado() const { return mano.estaEliminado(); }
int Jugador::getPuntos() const { return mano.calcularPuntos(); }
bool Jugador::tieneBlackjack() const { return mano.tieneBlackjack(); }

void Jugador::turno(Baraja& baraja) {
    string opcion;
    while (true) {
        cout << "\nTu mano actual:\n";
        mostrarMano();
        if (estaEliminado()) {
            cout << "Te pasaste de 21. Has perdido.\n";
            break;
        }
        cout << "¿Quieres pedir una carta? (s/n): ";
        cin >> opcion;
        if (opcion == "s") {
            recibirCarta(baraja.repartir());
        } else {
            break;
        }
    }
}