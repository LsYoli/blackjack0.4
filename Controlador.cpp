#include "Controlador.h"
#include <iostream>
using namespace std;

Controlador::Controlador() 
    : partidasJugadas(0), partidasGanadas(0), partidasPerdidas(0), 
      partidasEmpatadas(0), juegoActivo(true) {}

void Controlador::iniciarJuego() {
    interfaz.mostrarBienvenida(jugador.getDinero());
    
    while (juegoActivo && validarContinuidad()) {
        if (prepararPartida()) {
            ejecutarPartida();
            finalizarPartida();
        } else {
            juegoActivo = false;
        }
    }
    
    mostrarEstadisticasFinales();
    interfaz.mostrarDespedida();
}

bool Controlador::prepararPartida() {
    // Verificar si el jugador puede seguir jugando
    if (!jugador.puedeSeguirJugando()) {
        interfaz.mostrarGameOver();
        return false;
    }
    
    // Mostrar inicio de partida
    interfaz.mostrarInicioPartida(partidasJugadas + 1);
    
    // Solicitar apuesta
    double apuesta = interfaz.solicitarApuesta(jugador.getDinero());
    
    if (apuesta == 0) {
        return false; // El jugador quiere salir
    }
    
    // Realizar la apuesta
    if (!jugador.realizarApuesta(apuesta)) {
        cout << "Error al realizar la apuesta." << endl;
        return false;
    }
    
    interfaz.mostrarApuestaRealizada(apuesta);
    return true;
}

void Controlador::ejecutarPartida() {
    partidasJugadas++;
    reiniciarParaPartida();
    
    Crupier crupier;
    
    // Repartir cartas iniciales
    repartirCartasIniciales(crupier);
    
    // Verificar blackjack inicial
    if (verificarBlackjackInicial(crupier)) {
        determinarGanador(crupier);
        return;
    }
    
    // Turno del jugador
    ejecutarTurnoJugador();
    
    // Si el jugador no se eliminó, turno del crupier
    if (!jugador.estaEliminado()) {
        ejecutarTurnoCrupier(crupier);
    }
    
    // Determinar ganador final
    determinarGanador(crupier);
}

void Controlador::finalizarPartida() {
    mostrarEstadisticasActuales();
    
    // Preguntar si quiere continuar
    if (!interfaz.preguntarOtraPartida(jugador.puedeSeguirJugando())) {
        juegoActivo = false;
    }
}

void Controlador::repartirCartasIniciales(Crupier& crupier) {
    // Repartir 2 cartas a cada uno, alternando
    jugador.recibirCarta(baraja.repartir());
    crupier.recibirCarta(baraja.repartir());
    jugador.recibirCarta(baraja.repartir());
    crupier.recibirCarta(baraja.repartir());
    
    interfaz.mostrarCartasIniciales(jugador, crupier);
}

bool Controlador::verificarBlackjackInicial(Crupier& crupier) {
    bool jugadorBlackjack = jugador.tieneBlackjack();
    bool crupierBlackjack = crupier.tieneBlackjack();
    
    if (jugadorBlackjack || crupierBlackjack) {
        interfaz.mostrarBlackjackDetectado(jugadorBlackjack, crupierBlackjack);
        
        if (crupierBlackjack) {
            interfaz.mostrarManoCompleta("Crupier", crupier);
        }
        
        return true;
    }
    
    return false;
}

void Controlador::ejecutarTurnoJugador() {
    while (true) {
        interfaz.mostrarManoJugador(jugador, "--- TU TURNO ---");
        
        // Verificar si se eliminó
        if (jugador.estaEliminado()) {
            interfaz.mostrarJugadorEliminado();
            break;
        }
        
        // Preguntar si quiere carta
        if (interfaz.solicitarCarta()) {
            Carta nuevaCarta = baraja.repartir();
            jugador.recibirCarta(nuevaCarta);
            interfaz.mostrarCartaRecibida(nuevaCarta.toString());
        } else {
            cout << "Te plantas con " << jugador.getPuntos() << " puntos." << endl;
            break;
        }
    }
}

void Controlador::ejecutarTurnoCrupier(Crupier& crupier) {
    interfaz.mostrarTurnoCrupier();
    
    // Mostrar mano completa inicial
    interfaz.mostrarManoCompleta("Crupier", crupier);
    
    // Lógica automática del crupier
    while (crupier.debeTomarCarta()) {
        cout << "\nEl crupier debe tomar carta (tiene " << crupier.getPuntos() << " puntos)..." << endl;
        
        Carta nuevaCarta = baraja.repartir();
        crupier.recibirCarta(nuevaCarta);
        
        interfaz.mostrarCartaRecibida(nuevaCarta.toString());
        interfaz.mostrarManoCompleta("Crupier", crupier);
        
        if (crupier.estaEliminado()) {
            interfaz.mostrarCrupierEliminado();
            break;
        }
    }
    
    if (!crupier.estaEliminado()) {
        cout << "El crupier se planta con " << crupier.getPuntos() << " puntos." << endl;
    }
}

void Controlador::determinarGanador(Crupier& crupier) {
    // Mostrar manos finales
    interfaz.mostrarManoCompleta("Jugador", jugador);
    interfaz.mostrarManoCompleta("Crupier", crupier);
    
    // Variables para determinar el resultado
    bool jugadorEliminado = jugador.estaEliminado();
    bool crupierEliminado = crupier.estaEliminado();
    bool jugadorBlackjack = jugador.tieneBlackjack();
    bool crupierBlackjack = crupier.tieneBlackjack();
    int puntosJugador = jugador.getPuntos();
    int puntosCrupier = crupier.getPuntos();
    
    cout << "\nTus puntos: " << puntosJugador << endl;
    cout << "Puntos del Crupier: " << puntosCrupier << endl;
    
    // Lógica de determinación del resultado
    if (jugadorEliminado) {
        procesarDerrota();
        actualizarEstadisticas("derrota");
        interfaz.mostrarResultadoPartida("¡PERDISTE! Te pasaste de 21.", jugador.getDinero());
    } 
    else if (crupierEliminado) {
        procesarVictoria(jugadorBlackjack);
        actualizarEstadisticas("victoria");
        interfaz.mostrarResultadoPartida("¡GANASTE! El crupier se pasó de 21.", jugador.getDinero());
    } 
    else if (jugadorBlackjack && !crupierBlackjack) {
        procesarVictoria(true);
        actualizarEstadisticas("victoria");
        interfaz.mostrarResultadoPartida("¡GANASTE CON BLACKJACK!", jugador.getDinero());
    } 
    else if (!jugadorBlackjack && crupierBlackjack) {
        procesarDerrota();
        actualizarEstadisticas("derrota");
        interfaz.mostrarResultadoPartida("¡PERDISTE! El crupier tiene Blackjack.", jugador.getDinero());
    } 
    else if (jugadorBlackjack && crupierBlackjack) {
        procesarEmpate();
        actualizarEstadisticas("empate");
        interfaz.mostrarResultadoPartida("¡EMPATE! Ambos tienen Blackjack.", jugador.getDinero());
    } 
    else if (puntosJugador > puntosCrupier) {
        procesarVictoria(false);
        actualizarEstadisticas("victoria");
        interfaz.mostrarResultadoPartida("¡GANASTE! Tienes más puntos que el crupier.", jugador.getDinero());
    } 
    else if (puntosJugador < puntosCrupier) {
        procesarDerrota();
        actualizarEstadisticas("derrota");
        interfaz.mostrarResultadoPartida("¡PERDISTE! El crupier tiene más puntos.", jugador.getDinero());
    } 
    else {
        procesarEmpate();
        actualizarEstadisticas("empate");
        interfaz.mostrarResultadoPartida("¡EMPATE! Misma puntuación.", jugador.getDinero());
    }
}

void Controlador::procesarVictoria(bool esBlackjack) {
    jugador.procesarResultado(true, false, esBlackjack);
}

void Controlador::procesarDerrota() {
    jugador.procesarResultado(false, false, false);
}

void Controlador::procesarEmpate() {
    jugador.procesarResultado(false, true, false);
}

bool Controlador::validarContinuidad() {
    return jugador.puedeSeguirJugando();
}

void Controlador::actualizarEstadisticas(const string& resultado) {
    if (resultado == "victoria") {
        partidasGanadas++;
    } else if (resultado == "derrota") {
        partidasPerdidas++;
    } else if (resultado == "empate") {
        partidasEmpatadas++;
    }
}

void Controlador::reiniciarParaPartida() {
    jugador.reiniciarMano();
}

void Controlador::mostrarEstadisticasActuales() {
    interfaz.mostrarEstadisticas(partidasJugadas, partidasGanadas, 
                                partidasPerdidas, partidasEmpatadas, jugador.getDinero());
}

void Controlador::mostrarEstadisticasFinales() {
    cout << "\n===========================================" << endl;
    cout << "         ESTADÍSTICAS FINALES           " << endl;
    cout << "===========================================" << endl;
    
    interfaz.mostrarEstadisticas(partidasJugadas, partidasGanadas, 
                                partidasPerdidas, partidasEmpatadas, jugador.getDinero());
}
