/*
@brief Controla la lógica principal del juego Blackjack.

@details
La clase Controlador implementa el principio de responsabilidad única al
encargarse exclusivamente de la lógica del juego. Actúa como intermediario
entre las entidades del juego (Jugador, Crupier, Baraja, etc.) y la interfaz
de usuario. Coordina el flujo del juego, determina ganadores y gestiona
el estado general de la aplicación.

Responsabilidades:
- Coordinar el flujo completo del juego.
- Gestionar el estado de las partidas.
- Determinar condiciones de victoria, derrota y empate.
- Coordinar turnos de jugador y crupier.
- Mantener estadísticas del juego.
- Validar reglas del Blackjack.

Colaboraciones:
- Utiliza Interfaz para interactuar con el usuario.
- Gestiona instancias de Jugador, Crupier y Baraja.
- Coordina el flujo entre todas las entidades del juego.

 @autor [Daniel Andres Micolta Gongora]
 @mail [micolta.daniel@correounivalle.edu.co]
 @autor [Luis Santiago Arenas Hincapie]
 @mail [luis.arenas@correounivalle.edu.co]
 @date 2025-07-24
 @version 2.0
*/

#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "Jugador.h"
#include "Crupier.h"
#include "Baraja.h"
#include "Interfaz.h"

class Controlador {
private:
    // Entidades del juego
    Jugador jugador;
    Baraja baraja;
    Interfaz interfaz;
    
    // Estadísticas del juego
    int partidasJugadas;
    int partidasGanadas;
    int partidasPerdidas;
    int partidasEmpatadas;
    
    // Estado del juego
    bool juegoActivo;

public:
    // Constructor
    Controlador();
    
    // Método principal del controlador
    void iniciarJuego();
    
private:
    // Métodos de gestión de partidas
    bool prepararPartida();
    void ejecutarPartida();
    void finalizarPartida();
    
    // Métodos de lógica del juego
    void repartirCartasIniciales(Crupier& crupier);
    bool verificarBlackjackInicial(Crupier& crupier);
    void ejecutarTurnoJugador();
    void ejecutarTurnoCrupier(Crupier& crupier);
    
    // Métodos de determinación de resultados
    void determinarGanador(Crupier& crupier);
    void procesarVictoria(bool esBlackjack);
    void procesarDerrota();
    void procesarEmpate();
    
    // Métodos de validación y estado  
    bool validarContinuidad();
    void actualizarEstadisticas(const std::string& resultado);
    void reiniciarParaPartida();
    
    // Métodos auxiliares
    void mostrarEstadisticasActuales();
    void mostrarEstadisticasFinales();
};

#endif