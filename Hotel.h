//
// Created by Nati on 12/21/2025.
//

#ifndef OOP_HOTEL_H
#define OOP_HOTEL_H

#include <vector>
#include <iostream>
#include <algorithm>
#include "Camera.h"
#include "Angajat.h"
#include "Receptioner.h"
#include "Menajer.h"
#include "Manager.h"

class Hotel {
    Hotel() = default;

protected:
    std::vector<Camera*> camere;
    std::vector<Angajat*> angajati;

public:
    Hotel(const Hotel&) = delete;
    Hotel& operator=(const Hotel&) = delete;

    static Hotel& getInstance();

    void adaugaCamera(Camera* c);
    void adaugaAngajat(Angajat* a);
    void afisareAngajati();
    void afisareRezervari();
    void afisareCamereDescrescator();
    void afisareAngajatiDetaliat();

    std::vector<Angajat*>& getAngajati();
    std::vector<Camera*>& getCamere();
};

#endif //OOP_HOTEL_H