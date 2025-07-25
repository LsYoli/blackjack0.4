#include <iostream>
#include "Carta.h"
#include "Baraja.h"
#include "Mano.h"
#include "Jugador.h"
#include "Crupier.h"
using namespace std;

int main() {
    Baraja baraja;
    Jugador jugador;
    Crupier crupier;

    jugador.recibirCarta(baraja.repartir());
    crupier.recibirCarta(baraja.repartir());
    jugador.recibirCarta(baraja.repartir());
    crupier.recibirCarta(baraja.repartir());

    cout << "\nTu mano:\n";
    jugador.mostrarMano();

    cout << "\nCarta visible del Crupier:\n";
    crupier.mostrarMano(false);

    jugador.turno(baraja);

    if (!jugador.estaEliminado()) {
        crupier.turno(baraja);
    }

    cout << "\nResultado final:\n";
    cout << "Tus puntos: " << jugador.getPuntos() << "\n";
    cout << "Puntos del Crupier: " << crupier.getPuntos() << "\n";

    if (jugador.estaEliminado())
        cout << "Has perdido.\n";
    else if (crupier.estaEliminado())
        cout << "¡Ganaste! El crupier se pasó de 21.\n";
    else if (jugador.getPuntos() > crupier.getPuntos())
        cout << "¡Ganaste!\n";
    else if (jugador.getPuntos() < crupier.getPuntos())
        cout << "Has perdido.\n";
    else
        cout << "Empate.\n";

    return 0;
}
