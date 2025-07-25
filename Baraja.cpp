#include "Baraja.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

Baraja::Baraja() {
    string palos[] = {"Corazones", "Diamantes", "Tréboles", "Picas"};
    string valores[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    for (const auto& palo : palos)
        for (const auto& valor : valores)
            cartas.push_back(Carta(valor, palo));
    indice = 0;
    mezclar();
}

void Baraja::mezclar() {
    srand(time(nullptr));
    random_shuffle(cartas.begin(), cartas.end());
    indice = 0;
}

Carta Baraja::repartir() {
    if (indice < cartas.size())
        return cartas[indice++];
    else {
        cout << "Se acabaron las cartas, se mezclará de nuevo.\n";
        mezclar();
        return cartas[indice++];
    }
}
