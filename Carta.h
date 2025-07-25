/*
@brief Representa una carta individual con valor y palo.

@details
Esta clase modela una carta de una baraja de 52 cartas. Cada carta tiene un valor nominal (por ejemplo, "A", "2", "J") y un palo ("Corazones", "Picas", etc.). Ademas, asigna un valor numérico usado para calcular los puntos en una partida de Blackjack. La clase puede identificar si una carta es un As y proporcionar una representación textual de si misma.

Responsabilidades:
- Conocer su valor nominal (2-11).
- Conocer su palo (Corazones, Diamantes, Tréboles, Picas).
- Determinar si es un As.
- Proveer representación textual para mostrar.

Colaboraciones:
- Utilizada por Baraja para crear cartas.
- Utilizada por Mano para gestionar cartas.

 @autor [Daniel Andres Micolta Gongora]
 @mail [micolta.daniel@correounivalle.edu.co]
 @autor [Luis Santiago Arenas Hincapie]
 @mail [luis.arenas@correounivalle.edu.co]
 @date 2025-05-14
 @version 1.0
*/
#ifndef CARTA_H
#define CARTA_H

#include <string>

using namespace std;

class Carta {
private:
    string palo;
    string valor;
    int puntos;

public:
    Carta(string v, string p);
    int getPuntos() const;
    string toString() const;
    bool esAs() const;
};

#endif