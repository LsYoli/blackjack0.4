#include <iostream>
#include <iomanip>
#include <limits>
#include "Carta.h"
#include "Baraja.h"
#include "Mano.h"
#include "Jugador.h"
#include "Crupier.h"
#include "Apuesta.h"

using namespace std;

class JuegoBlackjack {
private:
    Jugador jugador;
    Baraja baraja;
    int partidasJugadas;
    int partidasGanadas;
    int partidasPerdidas;
    int partidasEmpatadas;

public:
    JuegoBlackjack() : partidasJugadas(0), partidasGanadas(0), 
                       partidasPerdidas(0), partidasEmpatadas(0) {}

    void mostrarBienvenida() {
        cout << "=========================================" << endl;
        cout << "    ¡BIENVENIDO AL BLACKJACK!           " << endl;
        cout << "=========================================" << endl;
        cout << "Dinero inicial: $" << fixed << setprecision(2) << jugador.getDinero() << endl;
        cout << "¡Que tengas suerte!" << endl << endl;
    }

    void mostrarEstadisticas() {
        cout << "\n--- ESTADÍSTICAS DEL JUGADOR ---" << endl;
        cout << "Dinero actual: $" << fixed << setprecision(2) << jugador.getDinero() << endl;
        cout << "Partidas jugadas: " << partidasJugadas << endl;
        cout << "Partidas ganadas: " << partidasGanadas << endl;
        cout << "Partidas perdidas: " << partidasPerdidas << endl;
        cout << "Partidas empatadas: " << partidasEmpatadas << endl;
        
        if (partidasJugadas > 0) {
            double porcentajeVictorias = (static_cast<double>(partidasGanadas) / partidasJugadas) * 100.0;
            cout << "Porcentaje de victorias: " << fixed << setprecision(1) << porcentajeVictorias << "%" << endl;
        }
    }

    bool solicitarApuesta() {
        double cantidad;
        cout << "\n--- NUEVA PARTIDA ---" << endl;
        cout << "Dinero disponible: $" << fixed << setprecision(2) << jugador.getDinero() << endl;
        
        while (true) {
            cout << "Ingresa la cantidad a apostar (0 para salir): $";
            cin >> cantidad;
            
            // Verificar entrada válida
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Por favor, ingresa un número válido.\n";
                continue;
            }
            
            // Verificar si quiere salir
            if (cantidad == 0) {
                return false;
            }
            
            // Verificar apuesta válida
            if (jugador.puedeApostar(cantidad)) {
                jugador.realizarApuesta(cantidad);
                cout << "Apuesta realizada: $" << fixed << setprecision(2) << cantidad << endl;
                return true;
            } else {
                cout << "Apuesta inválida. Debe ser mayor a 0 y no exceder tu dinero disponible.\n";
            }
        }
    }

    void repartirCartasIniciales(Crupier& crupier) {
        cout << "\n--- REPARTIENDO CARTAS INICIALES ---" << endl;
        
        // Repartir 2 cartas a cada uno, alternando
        jugador.recibirCarta(baraja.repartir());
        crupier.recibirCarta(baraja.repartir());
        jugador.recibirCarta(baraja.repartir());
        crupier.recibirCarta(baraja.repartir());
        
        cout << "\nTu mano inicial:" << endl;
        jugador.mostrarMano();
        
        cout << "\nCarta visible del Crupier:" << endl;
        crupier.mostrarMano(false); // Ocultar la primera carta
    }

    bool verificarBlackjackInicial(Crupier& crupier) {
        bool jugadorBlackjack = jugador.tieneBlackjack();
        bool crupierBlackjack = crupier.tieneBlackjack();
        
        if (jugadorBlackjack || crupierBlackjack) {
            cout << "\n¡BLACKJACK DETECTADO!" << endl;
            
            if (jugadorBlackjack) {
                cout << "¡Tienes Blackjack!" << endl;
            }
            
            if (crupierBlackjack) {
                cout << "El crupier revela su mano:" << endl;
                crupier.mostrarMano(true);
                cout << "¡El crupier tiene Blackjack!" << endl;
            }
            
            return true; // Hay blackjack, terminar la partida inmediatamente
        }
        
        return false; // No hay blackjack, continuar el juego normal
    }

    void determinarGanador(Crupier& crupier) {
        cout << "\n========== RESULTADO FINAL ==========" << endl;
        
        // Mostrar manos finales
        cout << "Tu mano final:" << endl;
        jugador.mostrarMano();
        crupier.mostrarResultadoFinal();
        
        // Determinar resultado
        bool jugadorEliminado = jugador.estaEliminado();
        bool crupierEliminado = crupier.estaEliminado();
        bool jugadorBlackjack = jugador.tieneBlackjack();
        bool crupierBlackjack = crupier.tieneBlackjack();
        int puntosJugador = jugador.getPuntos();
        int puntosCrupier = crupier.getPuntos();
        
        cout << "\nTus puntos: " << puntosJugador << endl;
        cout << "Puntos del Crupier: " << puntosCrupier << endl;
        
        // Lógica de determinación del ganador
        if (jugadorEliminado) {
            cout << "\n¡PERDISTE! Te pasaste de 21." << endl;
            jugador.procesarResultado(false, false, false);
            partidasPerdidas++;
        } else if (crupierEliminado) {
            cout << "\n¡GANASTE! El crupier se pasó de 21." << endl;
            jugador.procesarResultado(true, false, jugadorBlackjack);
            partidasGanadas++;
        } else if (jugadorBlackjack && !crupierBlackjack) {
            cout << "\n¡GANASTE CON BLACKJACK!" << endl;
            jugador.procesarResultado(true, false, true);
            partidasGanadas++;
        } else if (!jugadorBlackjack && crupierBlackjack) {
            cout << "\n¡PERDISTE! El crupier tiene Blackjack." << endl;
            jugador.procesarResultado(false, false, false);
            partidasPerdidas++;
        } else if (jugadorBlackjack && crupierBlackjack) {
            cout << "\n¡EMPATE! Ambos tienen Blackjack." << endl;
            jugador.procesarResultado(false, true, false);
            partidasEmpatadas++;
        } else if (puntosJugador > puntosCrupier) {
            cout << "\n¡GANASTE! Tienes más puntos que el crupier." << endl;
            jugador.procesarResultado(true, false, false);
            partidasGanadas++;
        } else if (puntosJugador < puntosCrupier) {
            cout << "\n¡PERDISTE! El crupier tiene más puntos." << endl;
            jugador.procesarResultado(false, false, false);
            partidasPerdidas++;
        } else {
            cout << "\n¡EMPATE! Misma puntuación." << endl;
            jugador.procesarResultado(false, true, false);
            partidasEmpatadas++;
        }
        
        cout << "Dinero restante: $" << fixed << setprecision(2) << jugador.getDinero() << endl;
    }

    void jugarPartida() {
        Crupier crupier;
        partidasJugadas++;
        
        // Preparar nueva partida
        jugador.reiniciarMano();
        crupier.reiniciarMano();
        
        // Repartir cartas iniciales
        repartirCartasIniciales(crupier);
        
        // Verificar blackjack inicial
        if (verificarBlackjackInicial(crupier)) {
            determinarGanador(crupier);
            return;
        }
        
        // Turno del jugador
        cout << "\n--- TU TURNO ---" << endl;
        jugador.turno(baraja);
        
        // Si el jugador no se eliminó, turno del crupier
        if (!jugador.estaEliminado()) {
            crupier.turno(baraja);
        }
        
        // Determinar ganador
        determinarGanador(crupier);
    }

    bool preguntarOtraPartida() {
        if (!jugador.puedeSeguirJugando()) {
            cout << "\n¡Te quedaste sin dinero! No puedes seguir jugando." << endl;
            return false;
        }
        
        string respuesta;
        cout << "\n¿Quieres jugar otra partida? (s/n): ";
        cin >> respuesta;
        
        return (respuesta == "s" || respuesta == "S" || respuesta == "si" || respuesta == "SI");
    }

    void ejecutar() {
        mostrarBienvenida();
        
        do {
            // Verificar si puede seguir jugando
            if (!jugador.puedeSeguirJugando()) {
                cout << "\n¡Game Over! Te quedaste sin dinero." << endl;
                break;
            }
            
            // Solicitar apuesta
            if (!solicitarApuesta()) {
                cout << "\nGracias por jugar. ¡Hasta la próxima!" << endl;
                break;
            }
            
            // Jugar la partida
            jugarPartida();
            
            // Mostrar estadísticas
            mostrarEstadisticas();
            
        } while (preguntarOtraPartida());
        
        // Mostrar estadísticas finales
        cout << "\n=========================================" << endl;
        cout << "         ESTADÍSTICAS FINALES           " << endl;
        cout << "=========================================" << endl;
        mostrarEstadisticas();
        cout << "\n¡Gracias por jugar Blackjack!" << endl;
    }
};

int main() {
    JuegoBlackjack juego;
    juego.ejecutar();
    return 0;
}