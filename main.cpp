
/*
@brief Punto de entrada principal del juego Blackjack.

@details
Este archivo implementa el principio de responsabilidad única al mantener
el main lo más simple posible. Su única responsabilidad es crear las
instancias necesarias e iniciar el flujo del juego a través del Controlador.
Toda la lógica compleja ha sido delegada a las clases especializadas.

@autor [Daniel Andres Micolta Gongora]
@mail [micolta.daniel@correounivalle.edu.co]  
@autor [Luis Santiago Arenas Hincapie]
@mail [luis.arenas@correounivalle.edu.co]
@date 2025-07-24
@version 2.0
*/

#include "Controlador.h"

int main() {
    // Crear la instancia del controlador
    Controlador controladorJuego;
    
    // Iniciar el flujo completo del juego
    controladorJuego.iniciarJuego();
    
    return 0;
}
