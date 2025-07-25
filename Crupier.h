/*
@brief Representa al crupier, que juega automáticamente según reglas.

@details
El Crupier es un oponente automático que sigue reglas estrictas: Debe continuar pidiendo cartas hasta alcanzar al menos 17 puntos, tiene su propia mano de cartas y puede mostrar su contenido parcial o total. Esta clase administradora del turno del crupier.

Responsabilidades:
- Gestionar su propia mano.
- Solicitar cartas automáticamente según reglas (mínimo 17).
- Mostrar su mano (con opción de ocultar cartas).
- Determinar su estado de juego (ganador v eliminado).

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
#ifndef CRUPIER_H
#define CRUPIER_H
#include "Mano.h"
#include "Baraja.h"

class Crupier {
private:
    Mano mano;

public:
    void recibirCarta(Carta c);
    void mostrarMano(bool mostrarTodo = true) const;
    bool estaEliminado() const;
    int getPuntos() const;
    void turno(Baraja& baraja);
};

#endif
