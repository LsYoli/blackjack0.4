TARGET = blackjack

SRCS = main.cpp Carta.cpp Baraja.cpp Mano.cpp Jugador.cpp Crupier.cpp Apuesta.cpp Controlador.cpp Interfaz.cpp

OBJS = $(SRCS:.cpp=.o)

CXX = g++
CXXFLAGS = -Wall -std=c++11

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)
