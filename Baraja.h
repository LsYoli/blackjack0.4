/*
@brief Representa la baraja completa de cartas, permite barajar y repartir.

@details
La clase Baraja contiene una colección completa de cartas estandar y proporciona funcionalidad para mezclar las cartas y repartirlas una por una. Esta clase asegura que el mazo se inicializa correctamente haciendo que se puede barajar aleatoriamente y que las cartas se repartan en orden.

Responsabilidades:
- Inicializar un mazo completo de cartas.
- Mezclar las cartas aleatoriamente.
- Repartir la siguiente carta disponible.

Colaboraciones:
- Usa Carta para crear el mazo.
- Provee cartas a Jugador y Crupier.

 @autor [Daniel Andres Micolta Gongora]
 @mail [micolta.daniel@correounivalle.edu.co]
 @autor [Luis Santiago Arenas Hincapie]
 @mail [luis.arenas@correounivalle.edu.co]
 @date 2025-05-14
 @version 1.0
*/
#ifndef BARAJA_H
#define BARAJA_H
#include <vector>
#include "Carta.h"

class Baraja {
private:
    vector<Carta> cartas;
    size_t indice;

public:
    Baraja();
    void mezclar();
    Carta repartir();
};

#endif