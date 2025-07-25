#include "Carta.h"

Carta::Carta(string v, string p) : valor(v), palo(p) {
    if (v == "A") puntos = 11;
    else if (v == "J" || v == "Q" || v == "K") puntos = 10;
    else puntos = stoi(v);
}

int Carta::getPuntos() const { return puntos; }
string Carta::toString() const { return valor + " de " + palo; }
bool Carta::esAs() const { return valor == "A"; }