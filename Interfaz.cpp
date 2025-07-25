#include "Interfaz.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>
using namespace std;

void Interfaz::mostrarBienvenida(double dineroInicial) const {
    mostrarSeparador("BIENVENIDO AL BLACKJACK");
    cout << endl;
    centrarTexto("¡Que tengas suerte!");
    cout << "Dinero inicial: " << formatearDinero(dineroInicial) << endl;
    mostrarLinea();
}

void Interfaz::mostrarDespedida() const {
    mostrarSeparador("GRACIAS POR JUGAR");
    centrarTexto("¡Hasta la próxima!");
    mostrarLinea();
}

void Interfaz::mostrarGameOver() const {
    mostrarSeparador("GAME OVER");
    centrarTexto("¡Te quedaste sin dinero!");
    mostrarLinea();
}

double Interfaz::solicitarApuesta(double dineroDisponible) const {
    double cantidad;
    
    cout << "\nDinero disponible: " << formatearDinero(dineroDisponible) << endl;
    
    while (true) {
        cout << "Ingresa la cantidad a apostar (0 para salir): $";
        cin >> cantidad;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "❌ Por favor, ingresa un número válido.\n";
            continue;
        }
        
        if (cantidad == 0) {
            return 0; // Señal para salir
        }
        
        if (cantidad > 0 && cantidad <= dineroDisponible) {
            return cantidad;
        }
        
        cout << "❌ Apuesta inválida. Debe ser mayor a 0 y no exceder tu dinero disponible.\n";
    }
}

bool Interfaz::solicitarCarta() const {
    string opcion;
    
    while (true) {
        cout << "\n¿Quieres pedir una carta? (s/n): ";
        cin >> opcion;
        
        if (opcion == "s" || opcion == "S" || opcion == "si" || opcion == "SI") {
            return true;
        } else if (opcion == "n" || opcion == "N" || opcion == "no" || opcion == "NO") {
            return false;
        } else {
            cout << "❌ Por favor, responde 's' para sí o 'n' para no.\n";
        }
    }
}

bool Interfaz::preguntarOtraPartida(bool puedeJugar) const {
    if (!puedeJugar) {
        cout << "\n❌ ¡Te quedaste sin dinero! No puedes seguir jugando.\n";
        return false;
    }
    
    string respuesta;
    cout << "\n¿Quieres jugar otra partida? (s/n): ";
    cin >> respuesta;
    
    return (respuesta == "s" || respuesta == "S" || 
            respuesta == "si" || respuesta == "SI");
}

void Interfaz::mostrarInicioPartida(int numeroPartida) const {
    mostrarSeparador("PARTIDA #" + to_string(numeroPartida));
}

void Interfaz::mostrarApuestaRealizada(double cantidad) const {
    cout << "✅ Apuesta realizada: " << formatearDinero(cantidad) << endl;
}

void Interfaz::mostrarCartasIniciales(const Jugador& jugador, const Crupier& crupier) const {
    cout << "\n🎴 REPARTIENDO CARTAS INICIALES 🎴\n" << endl;
    
    cout << "📋 Tu mano inicial:" << endl;
    jugador.mostrarMano();
    
    cout << "\n🎭 Carta visible del Crupier:" << endl;
    crupier.mostrarMano(false);
}

void Interfaz::mostrarManoJugador(const Jugador& jugador, const string& mensaje) const {
    if (!mensaje.empty()) {
        cout << "\n" << mensaje << endl;
    }
    cout << "📋 Tu mano actual:" << endl;
    jugador.mostrarMano();
}

void Interfaz::mostrarCartaRecibida(const string& carta) const {
    cout << "🎴 Recibiste: " << carta << endl;
}

void Interfaz::mostrarTurnoCrupier() const {
    mostrarSeparador("TURNO DEL CRUPIER");
    cout << "🎭 El crupier revela su mano completa:" << endl;
}

void Interfaz::mostrarManoCompleta(const string& nombre, const Jugador& jugador) const {
    cout << "\n📋 Mano final de " << nombre << ":" << endl;
    jugador.mostrarMano();
}

void Interfaz::mostrarResultadoPartida(const string& resultado, double dineroRestante) const {
    mostrarSeparador("RESULTADO FINAL");
    centrarTexto(resultado);
    cout << "💰 Dinero restante: " << formatearDinero(dineroRestante) << endl;
    mostrarLinea();
}

void Interfaz::mostrarBlackjackDetectado(bool jugadorBJ, bool crupierBJ) const {
    cout << "\n🃏 ¡BLACKJACK DETECTADO! 🃏\n" << endl;
    
    if (jugadorBJ) {
        cout << "🎉 ¡Tienes Blackjack!" << endl;
    }
    
    if (crupierBJ) {
        cout << "🎭 ¡El crupier tiene Blackjack!" << endl;
    }
}

void Interfaz::mostrarJugadorEliminado() const {
    cout << "\n💥 Te pasaste de 21. Has perdido." << endl;
}

void Interfaz::mostrarCrupierEliminado() const {
    cout << "\n💥 ¡El crupier se pasó de 21!" << endl;
}

void Interfaz::mostrarEstadisticas(int jugadas, int ganadas, int perdidas, int empatadas, double dinero) const {
    mostrarSeparador("ESTADÍSTICAS");
    
    cout << "💰 Dinero actual: " << formatearDinero(dinero) << endl;
    cout << "🎮 Partidas jugadas: " << jugadas << endl;
    cout << "🏆 Partidas ganadas: " << ganadas << endl;
    cout << "❌ Partidas perdidas: " << perdidas << endl;
    cout << "🤝 Partidas empatadas: " << empatadas << endl;
    
    if (jugadas > 0) {
        double porcentaje = calcularPorcentajeVictorias(ganadas, jugadas);
        cout << "📊 Porcentaje de victorias: " << fixed << setprecision(1) 
             << porcentaje << "%" << endl;
    }
    
    mostrarLinea();
}

void Interfaz::mostrarSeparador(const string& titulo) const {
    cout << "\n";
    cout << "==========================================" << endl;
    if (!titulo.empty()) {
        centrarTexto(titulo);
    }
    cout << "==========================================" << endl;
}

void Interfaz::mostrarLinea() const {
    cout << "------------------------------------------" << endl;
}

void Interfaz::limpiarBuffer() const {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Interfaz::centrarTexto(const string& texto, int ancho) const {
    int espacios = (ancho - texto.length()) / 2;
    if (espacios > 0) {
        cout << string(espacios, ' ');
    }
    cout << texto << endl;
}

string Interfaz::formatearDinero(double cantidad) const {
    ostringstream oss;
    oss << "$" << fixed << setprecision(2) << cantidad;
    return oss.str();
}

double Interfaz::calcularPorcentajeVictorias(int ganadas, int total) const {
    if (total == 0) return 0.0;
    return (static_cast<double>(ganadas) / total) * 100.0;
}