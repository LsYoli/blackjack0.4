#include "Apuesta.h"

Apuesta::Apuesta() : cantidadApostada(0.0) {}

void Apuesta::establecerApuesta(double cantidad) {
    cantidadApostada = cantidad;
}

double Apuesta::getCantidadApostada() const {
    return cantidadApostada;
}

double Apuesta::calcularGanancia(bool esBlackjack) const {
    if (esBlackjack) {
        // Blackjack paga 3:2 (devuelve apuesta + ganancia de 1.5x)
        return cantidadApostada + (cantidadApostada * 1.5);
    } else {
        // Ganancia normal paga 1:1 (devuelve apuesta + ganancia igual)
        return 2*cantidadApostada ;
    }
}

double Apuesta::calcularPerdida() const {
    // Pierde toda la apuesta
    return -cantidadApostada;
}

double Apuesta::calcularEmpate() const {
    // En empate, devuelve la apuesta (no gana ni pierde)
    return 0.0;
}

bool Apuesta::esApuestaValida(double cantidad, double dineroDisponible) const {
    return cantidad > 0 && cantidad <= dineroDisponible;
}

void Apuesta::reiniciar() {
    cantidadApostada = 0.0;
}