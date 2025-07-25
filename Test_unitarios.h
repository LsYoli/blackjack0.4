/*
@brief Sistema de pruebas unitarias organizadas por método.

@details
Esta clase implementa un sistema completo de pruebas unitarias estructuradas
por método individual. Cada función pública de las clases principales tiene
sus propias pruebas independientes que validan casos normales, casos borde
y manejo de errores. Proporciona reportes detallados de los resultados.

Responsabilidades:
- Probar cada método individual de las clases principales.
- Validar casos normales, bordes y errores.
- Generar reportes detallados de resultados.
- Mantener estadísticas de pruebas ejecutadas.

Colaboraciones:
- Utiliza todas las clases del sistema para probarlas.
- Proporciona interfaz para ejecutar pruebas desde main.

 @autor [Daniel Andres Micolta Gongora]
 @mail [micolta.daniel@correounivalle.edu.co]
 @autor [Luis Santiago Arenas Hincapie]
 @mail [luis.arenas@correounivalle.edu.co]
 @date 2025-07-24
 @version 2.0
*/

#ifndef TEST_UNITARIOS_H
#define TEST_UNITARIOS_H

#include <string>
#include <vector>

class TestUnitarios {
private:
    int testsPasados;
    int testsFallidos;
    int testsEjecutados;
    std::vector<std::string> fallosDetallados;

    // Método auxiliar para verificar y reportar tests
    void verificarTest(bool condicion, const std::string& nombreTest, 
                      const std::string& descripcion = "");
    
    // Métodos auxiliares para reportes
    void mostrarEncabezadoClase(const std::string& nombreClase);
    void mostrarResultadoMetodo(const std::string& nombreMetodo, int pasados, int fallidos);

public:
    // Constructor
    TestUnitarios();
    
    // Método principal para ejecutar todas las pruebas
    void ejecutarTodasLasPruebas();
    
    // === PRUEBAS CLASE CARTA ===
    void probarCartaConstructor();
    void probarCartaGetPuntos();
    void probarCartaToString();
    void probarCartaEsAs();
    
    // === PRUEBAS CLASE MANO ===
    void probarManoConstructor();
    void probarManoAgregarCarta();
    void probarManoCalcularPuntos();
    void probarManoMostrar();
    void probarManoTieneBlackjack();
    void probarManoEstaEliminado();
    
    // === PRUEBAS CLASE BARAJA ===
    void probarBarajaConstructor();
    void probarBarajaMezclar();
    void probarBarajaRepartir();
    
    // === PRUEBAS CLASE APUESTA ===
    void probarApuestaConstructor();
    void probarApuestaEstablecerApuesta();
    void probarApuestaGetCantidadApostada();
    void probarApuestaCalcularGanancia();
    void probarApuestaCalcularPerdida();
    void probarApuestaCalcularEmpate();
    void probarApuestaEsApuestaValida();
    void probarApuestaReiniciar();
    
    // === PRUEBAS CLASE JUGADOR ===
    void probarJugadorConstructor();
    void probarJugadorRecibirCarta();
    void probarJugadorMostrarMano();
    void probarJugadorReiniciarMano();
    void probarJugadorEstaEliminado();
    void probarJugadorGetPuntos();
    void probarJugadorTieneBlackjack();
    void probarJugadorGetDinero();
    void probarJugadorAjustarDinero();
    void probarJugadorPuedeApostar();
    void probarJugadorRealizarApuesta();
    void probarJugadorGetCantidadApostada();
    void probarJugadorProcesarResultado();
    void probarJugadorPuedeSeguirJugando();
    
    // === PRUEBAS CLASE CRUPIER ===
    void probarCrupierConstructor();
    void probarCrupierMostrarMano();
    void probarCrupierDebeTomarCarta();
    void probarCrupierMostrarResultadoFinal();
    
    // === PRUEBAS CLASE INTERFAZ ===
    void probarInterfazFormatearDinero();
    void probarInterfazCalcularPorcentajeVictorias();
    void probarInterfazCentrarTexto();
    
    // Métodos de reporte
    void mostrarResumenFinal();
    void mostrarDetallesFallos();
    bool todosPasaron() const;
};

#endif