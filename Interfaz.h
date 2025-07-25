/*
@brief Maneja toda la interacción con el usuario a través de la consola.

@details
La clase Interfaz se encarga exclusivamente de la presentación y entrada de datos
del usuario. Implementa el principio de responsabilidad única al separar
completamente la lógica de presentación de la lógica del juego. Proporciona
métodos para mostrar información y solicitar entrada del usuario de manera
consistente y clara.

Responsabilidades:
- Mostrar mensajes de bienvenida y despedida.
- Solicitar y validar entrada del usuario (apuestas, decisiones).
- Mostrar el estado del juego (manos, puntos, resultados).
- Presentar estadísticas y resúmenes.
- Formatear la salida de manera consistente.

Colaboraciones:
- Utilizada por Controlador para interactuar con el usuario.
- Recibe datos de las entidades del juego para mostrarlos.

 @autor [Daniel Andres Micolta Gongora]
 @mail [micolta.daniel@correounivalle.edu.co]
 @autor [Luis Santiago Arenas Hincapie]
 @mail [luis.arenas@correounivalle.edu.co]
 @date 2025-07-24
 @version 2.0
*/

#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <string>
#include "Jugador.h"
#include "Crupier.h"

class Interfaz {
public:
    // Mensajes de bienvenida y despedida
    void mostrarBienvenida(double dineroInicial) const;
    void mostrarDespedida() const;
    void mostrarGameOver() const;
    
    // Solicitud de entrada del usuario
    double solicitarApuesta(double dineroDisponible) const;
    bool solicitarCarta() const;
    bool preguntarOtraPartida(bool puedeJugar) const;
    
    // Mostrar estado del juego
    void mostrarInicioPartida(int numeroPartida) const;
    void mostrarApuestaRealizada(double cantidad) const;
    void mostrarCartasIniciales(const Jugador& jugador, const Crupier& crupier) const;
    void mostrarManoJugador(const Jugador& jugador, const std::string& mensaje = "") const;
    void mostrarCartaRecibida(const std::string& carta) const;
    void mostrarTurnoCrupier() const;
    void mostrarManoCompleta(const std::string& nombre, const Jugador& jugador) const;
    
    // Mostrar resultados
    void mostrarResultadoPartida(const std::string& resultado, double dineroRestante) const;
    void mostrarBlackjackDetectado(bool jugadorBJ, bool crupierBJ) const;
    void mostrarJugadorEliminado() const;
    void mostrarCrupierEliminado() const;
    
    // Estadísticas
    void mostrarEstadisticas(int jugadas, int ganadas, int perdidas, int empatadas, double dinero) const;
    
    // Métodos de utilidad para formato
    void mostrarSeparador(const std::string& titulo = "") const;
    void mostrarLinea() const;
    void limpiarBuffer() const;
    
private:
    // Métodos auxiliares para formateo
    void centrarTexto(const std::string& texto, int ancho = 50) const;
    std::string formatearDinero(double cantidad) const;
    double calcularPorcentajeVictorias(int ganadas, int total) const;
};

#endif