/*Colaboraciones:
- Utilizada por Jugador para gestionar su dinero.
- Utilizada por el flujo principal del juego.

 @autor [Daniel Andres Micolta Gongora]
 @mail [micolta.daniel@correounivalle.edu.co]
 @autor [Luis Santiago Arenas Hincapie]
 @mail [luis.arenas@correounivalle.edu.co]
 @date 2025-07-24
 @version 2.0
*/

#ifndef APUESTA_H
#define APUESTA_H

class Apuesta {
private:
    double cantidadApostada;
    static const double MULTIPLICADOR_BLACKJACK; // 1.5 (paga 3:2)
    static const double MULTIPLICADOR_GANANCIA;  // 1.0 (paga 1:1)

public:
    // Constructor
    Apuesta();
    
    // Métodos principales
    void establecerApuesta(double cantidad);
    double getCantidadApostada() const;
    
    // Cálculo de resultados
    double calcularGanancia(bool esBlackjack = false) const;
    double calcularPerdida() const;
    double calcularEmpate() const;
    
    // Validación
    bool esApuestaValida(double cantidad, double dineroDisponible) const;
    
    // Métodos de utilidad
    void reiniciar();
};

#endif