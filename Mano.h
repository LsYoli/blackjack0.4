/*
@brief Representa la mano de cartas de un jugador o crupier.

@details
La clase Mano permite almacenar multiples cartas y calcular el total de puntos de la mano, considerando reglas especiales del Blackjack, como el valor del As (1 u 11). Tambien puede mostrar las cartas de la mano, verificar si hay un Blackjack natural (21 con dos cartas) o si la mano esta eliminada (mas de 21 puntos).

Responsabilidades:
- Guardar cartas que tiene el jugador/crupier.
- Calcular el puntaje total de la mano (considerando reglas del As).
- Mostrar cartas al usuario.
- Detectar si tiene blackjack o si está eliminado (>21).

Colaboraciones:
- Utiliza cartas de tipo Carta.
- Utilizada por Jugador y Crupier.

 @autor [Daniel Andres Micolta Gongora]
 @mail [micolta.daniel@correounivalle.edu.co]
 @autor [Luis Santiago Arenas Hincapie]
 @mail [luis.arenas@correounivalle.edu.co]
 @date 2025-05-14
 @version 1.0
*/
#ifndef MANO_H
#define MANO_H
#include <vector>
#include "Carta.h"

class Mano {
private:
    vector<Carta> cartas;

public:
    void agregarCarta(Carta c);
    int calcularPuntos() const;
    void mostrar(bool mostrarTodo = true) const;
    bool tieneBlackjack() const;
    bool estaEliminado() const;
};

#endif