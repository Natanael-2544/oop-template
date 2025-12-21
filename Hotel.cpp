//
// Created by Nati on 12/21/2025.
//

#include "Hotel.h"

Hotel& Hotel::getInstance() {
    static Hotel h;
    return h;
}

void Hotel::adaugaCamera(Camera* c) {
    camere.push_back(c);
}

void Hotel::adaugaAngajat(Angajat* a) {
    angajati.push_back(a);
}

void Hotel::afisareAngajati() {
    int recep = 0, menajer = 0, manager = 0;
    for (auto a : angajati) {
        if (dynamic_cast<Receptioner*>(a)) recep++;
        if (dynamic_cast<Menajer*>(a)) menajer++;
        if (dynamic_cast<Manager*>(a)) manager++;
    }
    std::cout << "Receptioneri:" << recep
              << " Menajeri:" << menajer
              << " Manageri:" << manager << "\n";
}

void Hotel::afisareRezervari() {
    if (camere.empty()) {
        std::cout << "Nu exista rezervari.\n";
        return;
    }
    std::cout << "Rezervari hotel:\n";
    for (const auto c : camere) {
        std::cout << *c;
    }
}

void Hotel::afisareCamereDescrescator() {
    if (camere.empty()) {
        std::cout << "Nu exista rezervari.\n";
        return;
    }
    std::vector<Camera*> copie = camere;
    std::sort(copie.begin(), copie.end(), [](const Camera* a, const Camera* b) {
        return a->calcPret() > b->calcPret();
    });
    std::cout << "Camere ordonate descrescator dupa pret:\n";
    for (const auto c : copie) {
        std::cout << *c;
    }
}

std::vector<Angajat*>& Hotel::getAngajati() {
    return angajati;
}

std::vector<Camera*>& Hotel::getCamere() {
    return camere;
}

void Hotel::afisareAngajatiDetaliat() {
    std::cout << "angajati = [";
    for (size_t i = 0; i < angajati.size(); i++) {
        Angajat* a = angajati[i];
        if (dynamic_cast<Receptioner*>(a)) std::cout << "Receptioner";
        else if (dynamic_cast<Menajer*>(a)) std::cout << "Menajer";
        else if (dynamic_cast<Manager*>(a)) std::cout << "Manager";

        std::cout << "(" << a->getEnergie() << ")";
        if (i != angajati.size() - 1)
            std::cout << ", ";
    }
    std::cout << "]\n";
}
