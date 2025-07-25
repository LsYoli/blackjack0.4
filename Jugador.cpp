#include "Jugador.h"
#include <iostream>
using namespace std;

// Definición de constante estática
const double Jugador::DINERO_INICIAL = 1000.0;

Jugador::Jugador(double dineroInicial) : dinero(dineroInicial) {}

void Jugador::recibirCarta(Carta c) {
    mano.agregarCarta(c);
}

void Jugador::mostrarMano() const {
    mano.mostrar();
}

void Jugador::reiniciarMano() {
    mano = Mano(); // Crear nueva mano vacía
}

bool Jugador::estaEliminado() const {
    return mano.estaEliminado();
}

int Jugador::getPuntos() const {
    return mano.calcularPuntos();
}

bool Jugador::tieneBlackjack() const {
    return mano.tieneBlackjack();
}

double Jugador::getDinero() const {
    return dinero;
}

void Jugador::ajustarDinero(double cantidad) {
    dinero += cantidad;
    if (dinero < 0) {
        dinero = 0; // No permitir dinero negativo
    }
}

bool Jugador::puedeApostar(double cantidad) const {
    return apuestaActual.esApuestaValida(cantidad, dinero);
}

bool Jugador::realizarApuesta(double cantidad) {
    if (puedeApostar(cantidad)) {
        apuestaActual.establecerApuesta(cantidad);
        dinero -= cantidad; // Descontar la apuesta del dinero
        return true;
    }
    return false;
}

double Jugador::getCantidadApostada() const {
    return apuestaActual.getCantidadApostada();
}

void Jugador::procesarResultado(bool gano, bool empate, bool esBlackjack) {
    double resultado = 0.0;
    
    if (empate) {
        resultado = apuestaActual.calcularEmpate();
        cout << "Empate. Recuperas tu apuesta: $" << apuestaActual.getCantidadApostada() << endl;
        dinero += apuestaActual.getCantidadApostada(); // Devolver la apuesta
    } else if (gano) {
        resultado = apuestaActual.calcularGanancia(esBlackjack);
        dinero += resultado;
        if (esBlackjack) {
            cout << "¡Blackjack! Ganas: $" << (resultado - apuestaActual.getCantidadApostada()) << endl;
        } else {
            cout << "¡Ganaste! Recibes: $" << resultado << endl;
        }
    } else {
        resultado = apuestaActual.calcularPerdida();
        cout << "Perdiste la apuesta: $" << apuestaActual.getCantidadApostada() << endl;
        // El dinero ya se descontó al hacer la apuesta
    }
    
    // Reiniciar apuesta para la siguiente partida
    apuestaActual.reiniciar();
}

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
        
        if (opcion == "s" || opcion == "S") {
            recibirCarta(baraja.repartir());
            cout << "Recibiste: " << baraja.repartir().toString() << endl;
        } else {
            cout << "Te plantas con " << getPuntos() << " puntos.\n";
            break;
        }
    }
}

bool Jugador::puedeSeguirJugando() const {
    return dinero > 0;
}