/*
@brief Representa al crupier, que hereda de Jugador y juega automáticamente.

@details
El Crupier ahora hereda de la clase Jugador, aprovechando la funcionalidad común
mientras implementa su comportamiento específico. Sigue reglas estrictas: debe
continuar pidiendo cartas hasta alcanzar al menos 17 puntos. Sobrescribe métodos
virtuales para implementar su lógica particular de juego.

Responsabilidades:
- Heredar funcionalidad básica de Jugador.
- Implementar lógica automática de juego (regla de 17).
- Mostrar su mano con opción de ocultar la primera carta.
- Gestionar su turno de forma automática.

Colaboraciones:
- Hereda de Jugador.
- Usa Baraja para recibir cartas.
- Sobrescribe métodos virtuales según reglas del crupier.

 @autor [Daniel Andres Micolta Gongora]
 @mail [micolta.daniel@correounivalle.edu.co]
 @autor [Luis Santiago Arenas Hincapie]
 @mail [luis.arenas@correounivalle.edu.co]
 @date 2025-07-24
 @version 3.0
*/

#ifndef CRUPIER_H
#define CRUPIER_H

#include "Jugador.h"

class Crupier : public Jugador {
private:
    static const int UMBRAL_PLANTARSE = 17; // El crupier se planta con 17 o más

public:
    // Constructor
    Crupier();
    
    // Destructor
    virtual ~Crupier() = default;
    
    // Sobrescribir método de mostrar mano para poder ocultar cartas
    void mostrarMano(bool mostrarTodo = true) const;
    
    // Sobrescribir el método turno con lógica automática del crupier
    virtual void turno(Baraja& baraja) override;
    
    // Método específico para lógica de decisión del crupier
    bool debeTomarCarta() const;
    
    // Método para mostrar resultado final del crupier
    void mostrarResultadoFinal() const;
};

#endif