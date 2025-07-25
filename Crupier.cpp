#include "Crupier.h"
#include <iostream>
using namespace std;

Crupier::Crupier() : Jugador(0.0) {
    // El crupier no necesita dinero, por eso se inicializa con 0
}

void Crupier::mostrarMano(bool mostrarTodo) const {
    // Usar el método de la clase Mano directamente para control específico
    mano.mostrar(mostrarTodo);
}

void Crupier::turno(Baraja& baraja) {
    cout << "\n=== TURNO DEL CRUPIER ===" << endl;
    cout << "El crupier revela su mano completa:" << endl;
    mostrarMano(true);
    
    // Lógica automática del crupier
    while (debeTomarCarta()) {
        cout << "\nEl crupier debe tomar carta (tiene " << getPuntos() << " puntos)..." << endl;
        
        Carta nuevaCarta = baraja.repartir();
        recibirCarta(nuevaCarta);
        
        cout << "El crupier recibe: " << nuevaCarta.toString() << endl;
        mostrarMano(true);
        
        // Verificar si se pasó
        if (estaEliminado()) {
            cout << "¡El crupier se pasó de 21!" << endl;
            break;
        }
    }
    
    // Mensaje final del turno del crupier
    if (!estaEliminado()) {
        cout << "\nEl crupier se planta con " << getPuntos() << " puntos." << endl;
    }
}

bool Crupier::debeTomarCarta() const {
    // Regla estándar del Blackjack: el crupier debe tomar carta si tiene menos de 17
    return getPuntos() < UMBRAL_PLANTARSE && !estaEliminado();
}

void Crupier::mostrarResultadoFinal() const {
    cout << "\n--- MANO FINAL DEL CRUPIER ---" << endl;
    mostrarMano(true);
    
    if (estaEliminado()) {
        cout << "El crupier se pasó de 21." << endl;
    } else if (tieneBlackjack()) {
        cout << "¡El crupier tiene Blackjack!" << endl;
    } else {
        cout << "El crupier terminó con " << getPuntos() << " puntos." << endl;
    }
}