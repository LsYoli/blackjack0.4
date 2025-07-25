/*
@brief Representa a un jugador humano del juego Blackjack.

@details
La clase Jugador contiene una mano propia y administra su interacción durante el turno. Permite que el jugador solicite más cartas o decida plantarse y ofrece funciones para verificar si esta eliminado, permite mostrar cual es su puntaje total y tambien permite mostrar el estado actual de su mano.

Responsabilidades:
- Gestionar la mano del jugador.
- Permitir al jugador pedir cartas o plantarse.
- Mostrar la mano y puntaje.
- Determinar si ganó, perdió o tiene blackjack.

Colaboraciones:
- Usa Mano para administrar cartas.
- Recibe cartas desde Baraja.

 @autor [Daniel Andres Micolta Gongora]
 @mail [micolta.daniel@correounivalle.edu.co]
 @autor [Luis Santiago Arenas Hincapie]
 @mail [luis.arenas@correounivalle.edu.co]
 @date 2025-05-14
 @version 1.0
*/
#ifndef JUGADOR_H
#define JUGADOR_H
#include "Mano.h"
#include "Baraja.h"

class Jugador {
private:
    Mano mano;

public:
    void recibirCarta(Carta c);
    void mostrarMano() const;
    bool estaEliminado() const;
    int getPuntos() const;
    bool tieneBlackjack() const;
    void turno(Baraja& baraja);
};

#endif