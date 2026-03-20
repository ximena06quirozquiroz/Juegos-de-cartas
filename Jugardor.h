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
