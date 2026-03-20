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
