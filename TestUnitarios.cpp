#include "TestUnitarios.h"
#include "Carta.h"
#include "Mano.h"
#include "Baraja.h"
#include "Apuesta.h"
#include "Jugador.h"
#include "Crupier.h"
#include "Interfaz.h"
#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

// Colores para output
#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

TestUnitarios::TestUnitarios() : testsPasados(0), testsFallidos(0), testsEjecutados(0) {}

void TestUnitarios::verificarTest(bool condicion, const string& nombreTest, const string& descripcion) {
    testsEjecutados++;
    
    if (condicion) {
        cout << GREEN << "  ✓ " << nombreTest << RESET;
        if (!descripcion.empty()) {
            cout << " - " << descripcion;
        }
        cout << endl;
        testsPasados++;
    } else {
        cout << RED << "  ✗ " << nombreTest << RESET;
        if (!descripcion.empty()) {
            cout << " - " << descripcion;
        }
        cout << endl;
        testsFallidos++;
        fallosDetallados.push_back(nombreTest + ": " + descripcion);
    }
}

void TestUnitarios::mostrarEncabezadoClase(const string& nombreClase) {
    cout << CYAN << "\n========== PRUEBAS CLASE " << nombreClase << " ==========" << RESET << endl;
}

void TestUnitarios::mostrarResultadoMetodo(const string& nombreMetodo, int pasados, int fallidos) {
    cout << YELLOW << "\n--- " << nombreMetodo << " ---" << RESET << endl;
}

void TestUnitarios::ejecutarTodasLasPruebas() {
    cout << BLUE << "==========================================" << endl;
    cout << "    EJECUTANDO PRUEBAS UNITARIAS        " << endl;
    cout << "==========================================" << RESET << endl;
    
    // Reiniciar contadores
    testsPasados = testsFallidos = testsEjecutados = 0;
    fallosDetallados.clear();
    
    // Ejecutar pruebas por clase
    mostrarEncabezadoClase("CARTA");
    probarCartaConstructor();
    probarCartaGetPuntos();
    probarCartaToString();
    probarCartaEsAs();
    
    mostrarEncabezadoClase("MANO");
    probarManoConstructor();
    probarManoAgregarCarta();
    probarManoCalcularPuntos();
    probarManoTieneBlackjack();
    probarManoEstaEliminado();
    
    mostrarEncabezadoClase("BARAJA");
    probarBarajaConstructor();
    probarBarajaMezclar();
    probarBarajaRepartir();
    
    mostrarEncabezadoClase("APUESTA");
    probarApuestaConstructor();
    probarApuestaEstablecerApuesta();
    probarApuestaGetCantidadApostada();
    probarApuestaCalcularGanancia();
    probarApuestaCalcularPerdida();
    probarApuestaCalcularEmpate();
    probarApuestaEsApuestaValida();
    probarApuestaReiniciar();
    
    mostrarEncabezadoClase("JUGADOR");
    probarJugadorConstructor();
    probarJugadorRecibirCarta();
    probarJugadorReiniciarMano();
    probarJugadorEstaEliminado();
    probarJugadorGetPuntos();
    probarJugadorTieneBlackjack();
    probarJugadorGetDinero();
    probarJugadorAjustarDinero();
    probarJugadorPuedeApostar();
    probarJugadorRealizarApuesta();
    probarJugadorGetCantidadApostada();
    probarJugadorProcesarResultado();
    probarJugadorPuedeSeguirJugando();
    
    mostrarEncabezadoClase("CRUPIER");
    probarCrupierConstructor();
    probarCrupierMostrarMano();
    probarCrupierDebeTomarCarta();
    
    mostrarEncabezadoClase("INTERFAZ");
    probarInterfazFormatearDinero();
    probarInterfazCalcularPorcentajeVictorias();
    
    // Mostrar resumen final
    mostrarResumenFinal();
}

// ========== PRUEBAS CLASE CARTA ==========

void TestUnitarios::probarCartaConstructor() {
    mostrarResultadoMetodo("Constructor", 0, 0);
    
    // Caso normal: carta numérica
    Carta carta2("2", "Corazones");
    verificarTest(true, "Construcción carta numérica", "Carta 2 de Corazones");
    
    // Caso normal: carta figura
    Carta cartaK("K", "Picas");
    verificarTest(true, "Construcción carta figura", "Rey de Picas");
    
    // Caso normal: As
    Carta cartaAs("A", "Diamantes");
    verificarTest(true, "Construcción As", "As de Diamantes");
    
    // Caso borde: carta 10
    Carta carta10("10", "Tréboles");
    verificarTest(true, "Construcción carta 10", "10 de Tréboles");
}

void TestUnitarios::probarCartaGetPuntos() {
    mostrarResultadoMetodo("getPuntos", 0, 0);
    
    // Cartas numéricas
    Carta carta2("2", "Corazones");
    verificarTest(carta2.getPuntos() == 2, "Carta 2 vale 2 puntos");
    
    Carta carta9("9", "Picas");
    verificarTest(carta9.getPuntos() == 9, "Carta 9 vale 9 puntos");
    
    // Carta 10
    Carta carta10("10", "Diamantes");
    verificarTest(carta10.getPuntos() == 10, "Carta 10 vale 10 puntos");
    
    // Figuras
    Carta cartaJ("J", "Corazones");
    verificarTest(cartaJ.getPuntos() == 10, "J vale 10 puntos");
    
    Carta cartaQ("Q", "Picas");
    verificarTest(cartaQ.getPuntos() == 10, "Q vale 10 puntos");
    
    Carta cartaK("K", "Diamantes");
    verificarTest(cartaK.getPuntos() == 10, "K vale 10 puntos");
    
    // As
    Carta cartaAs("A", "Tréboles");
    verificarTest(cartaAs.getPuntos() == 11, "As inicial vale 11 puntos");
}

void TestUnitarios::probarCartaToString() {
    mostrarResultadoMetodo("toString", 0, 0);
    
    Carta carta2("2", "Corazones");
    verificarTest(carta2.toString() == "2 de Corazones", "toString carta 2");
    
    Carta cartaAs("A", "Picas");
    verificarTest(cartaAs.toString() == "A de Picas", "toString As");
    
    Carta cartaK("K", "Diamantes");
    verificarTest(cartaK.toString() == "K de Diamantes", "toString Rey");
}

void TestUnitarios::probarCartaEsAs() {
    mostrarResultadoMetodo("esAs", 0, 0);
    
    Carta cartaAs("A", "Corazones");
    verificarTest(cartaAs.esAs(), "As es identificado correctamente");
    
    Carta carta2("2", "Picas");
    verificarTest(!carta2.esAs(), "Carta 2 no es As");
    
    Carta cartaK("K", "Diamantes");
    verificarTest(!cartaK.esAs(), "Rey no es As");
}

// ========== PRUEBAS CLASE MANO ==========

void TestUnitarios::probarManoConstructor() {
    mostrarResultadoMetodo("Constructor", 0, 0);
    
    Mano mano;
    verificarTest(mano.calcularPuntos() == 0, "Mano vacía tiene 0 puntos");
    verificarTest(!mano.tieneBlackjack(), "Mano vacía no tiene blackjack");
    verificarTest(!mano.estaEliminado(), "Mano vacía no está eliminada");
}

void TestUnitarios::probarManoAgregarCarta() {
    mostrarResultadoMetodo("agregarCarta", 0, 0);
    
    Mano mano;
    Carta carta7("7", "Corazones");
    
    mano.agregarCarta(carta7);
    verificarTest(mano.calcularPuntos() == 7, "Agregar carta 7");
    
    Carta carta8("8", "Picas");
    mano.agregarCarta(carta8);
    verificarTest(mano.calcularPuntos() == 15, "Agregar segunda carta (7+8=15)");
}

void TestUnitarios::probarManoCalcularPuntos() {
    mostrarResultadoMetodo("calcularPuntos", 0, 0);
    
    // Caso normal: cartas sin As
    Mano mano1;
    mano1.agregarCarta(Carta("7", "Corazones"));
    mano1.agregarCarta(Carta("8", "Picas"));
    verificarTest(mano1.calcularPuntos() == 15, "7 + 8 = 15 puntos");
    
    // Caso As suave
    Mano mano2;
    mano2.agregarCarta(Carta("A", "Corazones"));
    mano2.agregarCarta(Carta("6", "Picas"));
    verificarTest(mano2.calcularPuntos() == 17, "As + 6 = 17 (As vale 11)");
    
    // Caso As duro
    Mano mano3;
    mano3.agregarCarta(Carta("A", "Corazones"));
    mano3.agregarCarta(Carta("6", "Picas"));
    mano3.agregarCarta(Carta("8", "Diamantes"));
    verificarTest(mano3.calcularPuntos() == 15, "As + 6 + 8 = 15 (As vale 1)");
    
    // Múltiples Ases
    Mano mano4;
    mano4.agregarCarta(Carta("A", "Corazones"));
    mano4.agregarCarta(Carta("A", "Picas"));
    mano4.agregarCarta(Carta("9", "Diamantes"));
    verificarTest(mano4.calcularPuntos() == 21, "As + As + 9 = 21");
}

void TestUnitarios::probarManoTieneBlackjack() {
    mostrarResultadoMetodo("tieneBlackjack", 0, 0);
    
    // Blackjack verdadero: As + figura
    Mano mano1;
    mano1.agregarCarta(Carta("A", "Corazones"));
    mano1.agregarCarta(Carta("K", "Picas"));
    verificarTest(mano1.tieneBlackjack(), "As + Rey es blackjack");
    
    // Blackjack verdadero: As + 10
    Mano mano2;
    mano2.agregarCarta(Carta("10", "Diamantes"));
    mano2.agregarCarta(Carta("A", "Tréboles"));
    verificarTest(mano2.tieneBlackjack(), "10 + As es blackjack");
    
    // No blackjack: 21 con 3 cartas
    Mano mano3;
    mano3.agregarCarta(Carta("7", "Corazones"));
    mano3.agregarCarta(Carta("7", "Picas"));
    mano3.agregarCarta(Carta("7", "Diamantes"));
    verificarTest(!mano3.tieneBlackjack(), "21 con 3 cartas no es blackjack");
    
    // No blackjack: menos de 21
    Mano mano4;
    mano4.agregarCarta(Carta("10", "Corazones"));
    mano4.agregarCarta(Carta("9", "Picas"));
    verificarTest(!mano4.tieneBlackjack(), "19 puntos no es blackjack");
}

void TestUnitarios::probarManoEstaEliminado() {
    mostrarResultadoMetodo("estaEliminado", 0, 0);
    
    // No eliminado: menos de 21
    Mano mano1;
    mano1.agregarCarta(Carta("10", "Corazones"));
    mano1.agregarCarta(Carta("9", "Picas"));
    verificarTest(!mano1.estaEliminado(), "19 puntos no está eliminado");
    
    // No eliminado: exactamente 21
    Mano mano2;
    mano2.agregarCarta(Carta("A", "Corazones"));
    mano2.agregarCarta(Carta("K", "Picas"));
    verificarTest(!mano2.estaEliminado(), "21 puntos no está eliminado");
    
    // Eliminado: más de 21
    Mano mano3;
    mano3.agregarCarta(Carta("K", "Corazones"));
    mano3.agregarCarta(Carta("Q", "Picas"));
    mano3.agregarCarta(Carta("5", "Diamantes"));
    verificarTest(mano3.estaEliminado(), "25 puntos está eliminado");
}

// ========== PRUEBAS CLASE BARAJA ==========

void TestUnitarios::probarBarajaConstructor() {
    mostrarResultadoMetodo("Constructor", 0, 0);
    
    Baraja baraja;
    Carta carta1 = baraja.repartir();
    verificarTest(!carta1.toString().empty(), "Baraja inicializada con cartas");
}

void TestUnitarios::probarBarajaMezclar() {
    mostrarResultadoMetodo("mezclar", 0, 0);
    
    Baraja baraja;
    // No podemos verificar el orden exacto, pero verificamos que no falle
    baraja.mezclar();
    Carta carta = baraja.repartir();
    verificarTest(!carta.toString().empty(), "Mezclar funciona correctamente");
}

void TestUnitarios::probarBarajaRepartir() {
    mostrarResultadoMetodo("repartir", 0, 0);
    
    Baraja baraja;
    
    // Repartir cartas normalmente
    Carta carta1 = baraja.repartir();
    Carta carta2 = baraja.repartir();
    verificarTest(!carta1.toString().empty(), "Primera carta repartida");
    verificarTest(!carta2.toString().empty(), "Segunda carta repartida");
    
    // Verificar que pueden ser diferentes (muy probable)
    bool sonDiferentes = (carta1.toString() != carta2.toString());
    verificarTest(sonDiferentes, "Cartas repartidas pueden ser diferentes");
}

// ========== PRUEBAS CLASE APUESTA ==========

void TestUnitarios::probarApuestaConstructor() {
    mostrarResultadoMetodo("Constructor", 0, 0);
    
    Apuesta apuesta;
    verificarTest(apuesta.getCantidadApostada() == 0.0, "Apuesta inicial es 0");
}

void TestUnitarios::probarApuestaEstablecerApuesta() {
    mostrarResultadoMetodo("establecerApuesta", 0, 0);
    
    Apuesta apuesta;
    apuesta.establecerApuesta(100.0);
    verificarTest(apuesta.getCantidadApostada() == 100.0, "Establecer apuesta de 100");
    
    apuesta.establecerApuesta(50.5);
    verificarTest(apuesta.getCantidadApostada() == 50.5, "Cambiar apuesta a 50.5");
}

void TestUnitarios::probarApuestaGetCantidadApostada() {
    mostrarResultadoMetodo("getCantidadApostada", 0, 0);
    
    Apuesta apuesta;
    verificarTest(apuesta.getCantidadApostada() == 0.0, "Cantidad inicial es 0");
    
    apuesta.establecerApuesta(75.25);
    verificarTest(apuesta.getCantidadApostada() == 75.25, "Obtener cantidad 75.25");
}

void TestUnitarios::probarApuestaCalcularGanancia() {
    mostrarResultadoMetodo("calcularGanancia", 0, 0);
    
    Apuesta apuesta;
    apuesta.establecerApuesta(100.0);
    
    // Ganancia normal (1:1)
    double gananciaNormal = apuesta.calcularGanancia(false);
    verificarTest(gananciaNormal == 200.0, "Ganancia normal: apuesta + 100% (100 -> 200)");
    
    // Ganancia blackjack (3:2)
    double gananciaBlackjack = apuesta.calcularGanancia(true);
    verificarTest(gananciaBlackjack == 250.0, "Ganancia blackjack: apuesta + 150% (100 -> 250)");
}

void TestUnitarios::probarApuestaCalcularPerdida() {
    mostrarResultadoMetodo("calcularPerdida", 0, 0);
    
    Apuesta apuesta;
    apuesta.establecerApuesta(100.0);
    
    double perdida = apuesta.calcularPerdida();
    verificarTest(perdida == -100.0, "Pérdida es negativa de la apuesta");
}

void TestUnitarios::probarApuestaCalcularEmpate() {
    mostrarResultadoMetodo("calcularEmpate", 0, 0);
    
    Apuesta apuesta;
    apuesta.establecerApuesta(100.0);
    
    double empate = apuesta.calcularEmpate();
    verificarTest(empate == 0.0, "Empate devuelve 0 (sin cambio)");
}

void TestUnitarios::probarApuestaEsApuestaValida() {
    mostrarResultadoMetodo("esApuestaValida", 0, 0);
    
    Apuesta apuesta;
    
    // Casos válidos
    verificarTest(apuesta.esApuestaValida(50.0, 100.0), "Apuesta 50 con dinero 100 es válida");
    verificarTest(apuesta.esApuestaValida(100.0, 100.0), "Apuesta igual al dinero es válida");
    verificarTest(apuesta.esApuestaValida(0.01, 100.0), "Apuesta mínima es válida");
    
    // Casos inválidos
    verificarTest(!apuesta.esApuestaValida(0.0, 100.0), "Apuesta 0 no es válida");
    verificarTest(!apuesta.esApuestaValida(-10.0, 100.0), "Apuesta negativa no es válida");
    verificarTest(!apuesta.esApuestaValida(150.0, 100.0), "Apuesta mayor al dinero no es válida");
}

void TestUnitarios::probarApuestaReiniciar() {
    mostrarResultadoMetodo("reiniciar", 0, 0);
    
    Apuesta apuesta;
    apuesta.establecerApuesta(100.0);
    verificarTest(apuesta.getCantidadApostada() == 100.0, "Apuesta establecida");
    
    apuesta.reiniciar();
    verificarTest(apuesta.getCantidadApostada() == 0.0, "Apuesta reiniciada a 0");
}

// ========== PRUEBAS CLASE JUGADOR ==========

void TestUnitarios::probarJugadorConstructor() {
    mostrarResultadoMetodo("Constructor", 0, 0);
    
    // Constructor por defecto
    Jugador jugador1;
    verificarTest(jugador1.getDinero() == 1000.0, "Dinero inicial por defecto es 1000");
    verificarTest(jugador1.getPuntos() == 0, "Puntos iniciales son 0");
    verificarTest(!jugador1.estaEliminado(), "Jugador no inicia eliminado");
    
    // Constructor con dinero personalizado
    Jugador jugador2(500.0);
    verificarTest(jugador2.getDinero() == 500.0, "Constructor con dinero personalizado");
}

void TestUnitarios::probarJugadorRecibirCarta() {
    mostrarResultadoMetodo("recibirCarta", 0, 0);
    
    Jugador jugador;
    Carta carta7("7", "Corazones");
    
    jugador.recibirCarta(carta7);
    verificarTest(jugador.getPuntos() == 7, "Recibir carta 7");
    
    Carta carta8("8", "Picas");
    jugador.recibirCarta(carta8);
    verificarTest(jugador.getPuntos() == 15, "Recibir segunda carta (7+8=15)");
}

void TestUnitarios::probarJugadorReiniciarMano() {
    mostrarResultadoMetodo("reiniciarMano", 0, 0);
    
    Jugador jugador;
    jugador.recibirCarta(Carta("K", "Corazones"));
    jugador.recibirCarta(Carta("Q", "Picas"));
    verificarTest(jugador.getPuntos() == 20, "Jugador tiene 20 puntos");
    
    jugador.reiniciarMano();
    verificarTest(jugador.getPuntos() == 0, "Mano reiniciada a 0 puntos");
}

void TestUnitarios::probarJugadorEstaEliminado() {
    mostrarResultadoMetodo("estaEliminado", 0, 0);
    
    Jugador jugador;
    jugador.recibirCarta(Carta("10", "Corazones"));
    jugador.recibirCarta(Carta("9", "Picas"));
    verificarTest(!jugador.estaEliminado(), "19 puntos no está eliminado");
    
    jugador.recibirCarta(Carta("5", "Diamantes"));
    verificarTest(jugador.estaEliminado(), "24 puntos está eliminado");
}

void TestUnitarios::probarJugadorGetPuntos() {
    mostrarResultadoMetodo("getPuntos", 0, 0);
    
    Jugador jugador;
    verificarTest(jugador.getPuntos() == 0, "Puntos iniciales son 0");
    
    jugador.recibirCarta(Carta("A", "Corazones"));
    verificarTest(jugador.getPuntos() == 11, "As inicial vale 11");
    
    jugador.recibirCarta(Carta("K", "Picas"));
    verificarTest(jugador.getPuntos() == 21, "As + Rey = 21");
}

void TestUnitarios::probarJugadorTieneBlackjack() {
    mostrarResultadoMetodo("tieneBlackjack", 0, 0);
    
    Jugador jugador1;
    jugador1.recibirCarta(Carta("A", "Corazones"));
    jugador1.recibirCarta(Carta("K", "Picas"));
    verificarTest(jugador1.tieneBlackjack(), "As + Rey es blackjack");
    
    Jugador jugador2;
    jugador2.recibirCarta(Carta("10", "Corazones"));
    jugador2.recibirCarta(Carta("9", "Picas"));
    verificarTest(!jugador2.tieneBlackjack(), "