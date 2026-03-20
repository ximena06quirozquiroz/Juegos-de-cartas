#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


class Carta {
    public:
        int numero;
        bool jugada;
        Carta();
        Carta(int numero);
        void Mostrar();
};

Carta::Carta() {
    this->numero = 0;
    this->jugada = false;
}

Carta::Carta(int numero) {
    this->numero = numero;
    this->jugada = false;
}

void Carta::Mostrar() {
    cout << "[ " << numero << " ]";
}


class Mazo {
    public:
        Carta cartas[100];
        int total;
        int indiceActual; 
        Mazo();
        void Revolver();
        void Mostrar();
        Carta* Repartir(int n); 
};

Mazo::Mazo() {
    this->total = 100;
    this->indiceActual = 0;
    for (int i = 0; i < 100; i++) {
        cartas[i] = Carta(i + 1);
    }
}

void Mazo::Revolver() {
    for (int i = 99; i > 0; i--) {
        int j = rand() % (i + 1);
        Carta temp = cartas[i];
        cartas[i] = cartas[j];
        cartas[j] = temp;
    }
    indiceActual = 0; 
}

void Mazo::Mostrar() {
    for (int i = 0; i < total; i++) {
        cartas[i].Mostrar();
        cout << " ";
    }
    cout << endl;
}


Carta* Mazo::Repartir(int n) {
    Carta* repartidas = new Carta[n];
    for (int i = 0; i < n; i++) {
        if (indiceActual < total) {
            repartidas[i] = cartas[indiceActual];
            indiceActual++;
        }
    }
    return repartidas;
}


class Jugador {
    public:
        Carta mano[12];
        int numCartas;
        Jugador();
        void RecibirCarta(Carta c);
        void MostrarMano();
        Carta JugarCarta(int i);
};

Jugador::Jugador() {
    this->numCartas = 0;
}

void Jugador::RecibirCarta(Carta c) {
    if (numCartas < 12) {
        this->mano[numCartas] = c;
        this->numCartas++;
    }
}

void Jugador::MostrarMano() {
    cout << "Mano: ";
    for (int i = 0; i < numCartas; i++) {
        cout << i + 1 << ":";
        mano[i].Mostrar();
        cout << " ";
    }
    cout << endl;
}

Carta Jugador::JugarCarta(int i) {
    Carta c = mano[i];
    
    for (int j = i; j < numCartas - 1; j++) {
        mano[j] = mano[j + 1];
    }
    numCartas--;
    return c;
}


class Game {
    public:
        Jugador* jugadores[2];
        Mazo* mazo;
        int vidas;
        int nivel;

        Game();
        ~Game();
        void IniciarNivel();
        bool VerificarCarta(int n);
        void MostrarEstado();
};

Game::Game() {
    srand(time(0));
    mazo = new Mazo();
    jugadores[0] = new Jugador();
    jugadores[1] = new Jugador();
    vidas = 3;
    nivel = 1;
}

Game::~Game() {
    delete mazo;
    delete jugadores[0];
    delete jugadores[1];
}


void Game::IniciarNivel() {
    cout << "\n========== NIVEL " << nivel << " ==========" << endl;
    cout << "Vidas restantes: " << vidas << endl;

    
    jugadores[0]->numCartas = 0;
    jugadores[1]->numCartas = 0;

    mazo->Revolver();

    
    int cartasPorJugador = nivel + 2; 
    if (cartasPorJugador > 12) cartasPorJugador = 12;

    Carta* cartasJ1 = mazo->Repartir(cartasPorJugador);
    Carta* cartasJ2 = mazo->Repartir(cartasPorJugador);

    for (int i = 0; i < cartasPorJugador; i++) {
        jugadores[0]->RecibirCarta(cartasJ1[i]);
        jugadores[1]->RecibirCarta(cartasJ2[i]);
    }

    delete[] cartasJ1;
    delete[] cartasJ2;

    cout << "Cada jugador recibio " << cartasPorJugador << " cartas." << endl;
}


bool Game::VerificarCarta(int n) {
    
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < jugadores[j]->numCartas; i++) {
            if (jugadores[j]->mano[i].numero > n) {
                return false; 
            }
        }
    }
    return true; 
}

void Game::MostrarEstado() {
    cout << "\n--- Estado del juego ---" << endl;
    cout << "Nivel: " << nivel << " | Vidas: " << vidas << endl;
    cout << "Jugador 1 - ";
    jugadores[0]->MostrarMano();
    cout << "Jugador 2 - ";
    jugadores[1]->MostrarMano();
    cout << "------------------------" << endl;
}


int main() {
    cout << "=============================" << endl;
    cout << "   JUEGO DE CARTAS en C++    " << endl;
    cout << "=============================" << endl;

    Game game;
    bool jugando = true;

    while (jugando && game.vidas > 0 && game.nivel <= 5) {
        game.IniciarNivel();
        game.MostrarEstado();

        
        while (game.jugadores[0]->numCartas > 0 && game.jugadores[1]->numCartas > 0) {
            cout << "\n--- Turno ---" << endl;

            
            int opcion1 = 0;
            cout << "Jugador 1, elige una carta (1-" << game.jugadores[0]->numCartas << "): ";
            cin >> opcion1;
            while (opcion1 < 1 || opcion1 > game.jugadores[0]->numCartas) {
                cout << "Opcion invalida. Elige de 1 a " << game.jugadores[0]->numCartas << ": ";
                cin >> opcion1;
            }
            Carta c1 = game.jugadores[0]->JugarCarta(opcion1 - 1);
            cout << "Jugador 1 jugo: ";
            c1.Mostrar();
            cout << endl;

            
            int opcion2 = 0;
            cout << "Jugador 2, elige una carta (1-" << game.jugadores[1]->numCartas << "): ";
            cin >> opcion2;
            while (opcion2 < 1 || opcion2 > game.jugadores[1]->numCartas) {
                cout << "Opcion invalida. Elige de 1 a " << game.jugadores[1]->numCartas << ": ";
                cin >> opcion2;
            }
            Carta c2 = game.jugadores[1]->JugarCarta(opcion2 - 1);
            cout << "Jugador 2 jugo: ";
            c2.Mostrar();
            cout << endl;

           
            if (c1.numero > c2.numero) {
                cout << ">> Jugador 1 gana esta ronda!" << endl;
            } else if (c2.numero > c1.numero) {
                cout << ">> Jugador 2 gana esta ronda!" << endl;
            } else {
                cout << ">> Empate en esta ronda!" << endl;
                game.vidas--;
                cout << "Pierden una vida. Vidas restantes: " << game.vidas << endl;
            }

            if (game.vidas <= 0) {
                cout << "\nSin vidas. Fin del juego!" << endl;
                jugando = false;
                break;
            }
        }

        if (jugando) {
            cout << "\n** Nivel " << game.nivel << " completado! **" << endl;
            game.nivel++;

            if (game.nivel <= 5) {
                cout << "Presiona Enter para continuar al siguiente nivel...";
                cin.ignore();
                cin.get();
            }
        }
    }

    if (game.nivel > 5) {
        cout << "\n=============================";
        cout << "\n  Ganastes todos los niveles!" << endl;
    } else {
        cout << "\n=============================";
        cout << "\n  Fin del fuego llegastes al nivel " << game.nivel << endl;
    }

    return 0;
}
