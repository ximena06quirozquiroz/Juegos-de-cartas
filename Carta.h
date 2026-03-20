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
