#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
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

// clase mazo

class Mazo {
    public:
        Carta cartas[100];
        int total;

        Mazo();
        void Revolver();
};

Mazo::Mazo() {
    this->total = 100;
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
}


class Jugador {
    public:
        Carta mano[12];
        int numCartas;

        Jugador();
        void RecibirCarta(Carta c);
        void MostrarMano();
        Carta JugarCarta(int i);
        void DescartarMenores(int n);
};

Jugador::Jugador() {
    this->numCartas = 0;
}

void Jugador::RecibirCarta(Carta c) {
    this->mano[numCartas] = c;
    this->numCartas++;
}

void Jugador::MostrarMano() {
    cout << "Tu mano: ";
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

void Jugador::DescartarMenores(int n) {
    int i = 0;
    while (i < numCartas) {
        if (mano[i].numero < n) {
            for (int j = i; j < numCartas - 1; j++) {
                mano[j] = mano[j + 1];
            }
            numCartas--;
        } else {
            i++;
        }
    }
}


class Game {
    public:
        Jugador jugadores[2];
        Mazo mazo;
        int vidas;
        int nivel;
        int mesaTop;

        Game();
        void IniciarNivel();
        bool VerificarCarta(int n);
        void MostrarMesa();
        void GuardarPartida();
        bool CargarPartida();
        void Jugar();
};

Game::Game() {
    srand(time(0));
    this->vidas = 3;
    this->nivel = 1;
    this->mesaTop = 0;
}

void Game::GuardarPartida() {
    ofstream archivo("partida.txt");
    archivo << nivel << endl;
    archivo << vidas << endl;
    archivo.close();
    cout << "Partida guardada!" << endl;
}

bool Game::CargarPartida() {
    ifstream archivo("partida.txt");
    if (!archivo) {
        return false;
    }
    archivo >> nivel;
    archivo >> vidas;
    archivo.close();
    return true;
}

void Game::IniciarNivel() {
    jugadores[0].numCartas = 0;
    jugadores[1].numCartas = 0;
    mesaTop = 0;

    mazo.Revolver();

    for (int i = 0; i < nivel; i++) {
        jugadores[0].RecibirCarta(mazo.cartas[i]);
        jugadores[1].RecibirCarta(mazo.cartas[i + nivel]);
    }

    cout << "\n========== NIVEL " << nivel << " ==========" << endl;
    cout << "Vidas: " << vidas << endl;
    cout << "Cada jugador recibe " << nivel << " carta(s)." << endl;
    cout << "Pongan la mano sobre la mesa..." << endl;
    cout << "Presiona Enter cuando esten listos." << endl;
    cin.ignore();
    cin.get();
}

bool Game::VerificarCarta(int n) {
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < jugadores[j].numCartas; i++) {
            if (jugadores[j].mano[i].numero < n) {
                return false;
            }
        }
    }
    return true;
}

void Game::MostrarMesa() {
    cout << "\n--- Mesa ---" << endl;
    cout << "Nivel: " << nivel << " | Vidas: " << vidas << endl;
    if (mesaTop == 0) {
        cout << "Mesa vacia" << endl;
    } else {
        cout << "Ultima carta: [ " << mesaTop << " ]" << endl;
    }
    cout << "------------" << endl;
}

void Game::Jugar() {
    while (vidas > 0 && nivel <= 5) {
        IniciarNivel();

        while (jugadores[0].numCartas > 0 || jugadores[1].numCartas > 0) {
            MostrarMesa();

            int quien = 0;
            cout << "¿Quien juega? (1 o 2): ";
            cin >> quien;
            while (quien < 1 || quien > 2) {
                cout << "Opcion invalida (1 o 2): ";
                cin >> quien;
            }

            Jugador* j = &jugadores[quien - 1];
            if (j->numCartas == 0) {
                cout << "Jugador " << quien << " no tiene cartas!" << endl;
                continue;
            }

            cout << "Jugador " << quien << ", ";
            j->MostrarMano();

            int opcion = 0;
            cout << "Elige carta (1-" << j->numCartas << "): ";
            cin >> opcion;
            while (opcion < 1 || opcion > j->numCartas) {
                cout << "Opcion invalida. Elige de 1 a " << j->numCartas << ": ";
                cin >> opcion;
            }

            Carta c = j->JugarCarta(opcion - 1);
            cout << "Jugador " << quien << " jugo: ";
            c.Mostrar();
            cout << endl;

            if (!VerificarCarta(c.numero)) {
                cout << "!! Habia cartas menores sin jugar. Pierden una vida !!" << endl;
                jugadores[0].DescartarMenores(c.numero);
                jugadores[1].DescartarMenores(c.numero);
                vidas--;
                if (vidas <= 0) {
                    cout << "\nSin vidas. Game over!" << endl;
                    return;
                }
            } else {
                cout << "Bien jugado!" << endl;
                mesaTop = c.numero;
            }
        }

        cout << "\n*** Nivel " << nivel << " completado! ***" << endl;
        GuardarPartida();
        nivel++;

        if (nivel <= 5) {
            cout << "Presiona Enter para el siguiente nivel...";
            cin.ignore();
            cin.get();
        }
    }

    if (nivel > 5) {
        cout << "\nGanaron! Completaron todos los niveles!" << endl;
    }
}

int main() {
    cout << "Bienvenidos a The Mind!" << endl;
    cout << "Buena suerte :)" << endl;
    

    Game game;

    char opcion;
    cout << "¿Desea continuar partida guardada? (s/n): ";
    cin >> opcion;

    if (opcion == 's' || opcion == 'S') {
        if (game.CargarPartida()) {
            cout << "Partida cargada! Nivel: " << game.nivel << " | Vidas: " << game.vidas << endl;
        } else {
            cout << "No hay partida guardada. Iniciando nueva partida..." << endl;
        }
    }

    game.Jugar();

    return 0;
}
