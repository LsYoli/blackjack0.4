/*
@brief Representa un jugador del juego Blackjack (clase base).

@details
La clase Jugador ahora sirve como clase base que contiene funcionalidad común
para jugadores humanos y el crupier. Maneja la mano de cartas, el dinero del
jugador y las apuestas. Incluye métodos virtuales que pueden ser sobrescritos
por clases derivadas para implementar comportamientos específicos.

Responsabilidades:
- Gestionar la mano del jugador.
- Administrar el dinero y las apuestas.
- Proporcionar interfaz común para jugadores y crupier.
- Permitir personalización del comportamiento mediante herencia.

Colaboraciones:
- Usa Mano para administrar cartas.
- Usa Apuesta para gestionar dinero.
- Clase base para Crupier.

 @autor [Daniel Andres Micolta Gongora]
 @mail [micolta.daniel@correounivalle.edu.co]
 @autor [Luis Santiago Arenas Hincapie]
 @mail [luis.arenas@correounivalle.edu.co]
 @date 2025-07-24
 @version 3.0
*/

#ifndef JUGADOR_H
#define JUGADOR_H

#include "Mano.h"
#include "Baraja.h"
#include "Apuesta.h"

class Jugador {
protected:
    Mano mano;
    double dinero;
    Apuesta apuestaActual;
    static const double DINERO_INICIAL;

public:
    // Constructor
    Jugador(double dineroInicial = 1000.0);
    
    // Destructor virtual para permitir herencia correcta
    virtual ~Jugador() = default;
    
    // Métodos básicos de manejo de cartas
    virtual void recibirCarta(Carta c);
    virtual void mostrarMano() const;
    virtual void reiniciarMano();
    
    // Métodos de estado del juego
    bool estaEliminado() const;
    int getPuntos() const;
    bool tieneBlackjack() const;
    
    // Métodos de gestión de dinero
    double getDinero() const;
    void ajustarDinero(double cantidad);
    bool puedeApostar(double cantidad) const;
    
    // Métodos de apuestas
    bool realizarApuesta(double cantidad);
    double getCantidadApostada() const;
    void procesarResultado(bool gano, bool empate = false, bool esBlackjack = false);
    
    // Método virtual para el turno (puede ser sobrescrito)
    virtual void turno(Baraja& baraja);
    
    // Método para verificar si puede seguir jugando
    bool puedeSeguirJugando() const;
};
 #endif