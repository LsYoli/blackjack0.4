
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

#include <iostream>
#include "Controlador.h"
#include "TestUnitarios.h"

using namespace std;

int main() {
    int opcion;
    TestUnitarios testUnitarios;

    do {
        cout << "==========================" << endl;
        cout << "       MENÚ PRINCIPAL     " << endl;
        cout << "==========================" << endl;
        cout << "1. Jugar" << endl;
        cout << "2. Ejecutar pruebas unitarias" << endl;
        cout << "3. Salir" << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                Controlador controlador;
                controlador.iniciarJuego();
                break;
            }
            case 2: {
                testUnitarios.ejecutarTodasLasPruebas();
                break;
            }
            case 3:
                cout << "Saliendo del programa. ¡Hasta luego!" << endl;
                break;
            default:
                cout << "Opción no válida. Por favor, selecciona de nuevo." << endl;
        }
    } while (opcion != 3);

    return 0;
}
