//
// Created by Nati on 12/21/2025.
//

#include "Receptioner.h"
Receptioner::Receptioner() : Angajat() {}

int Receptioner::getCostCheckIn() const { return 20; }
int Receptioner::getCostCheckOut() const { return 20; }

void Receptioner::checkIn(Camera* c) {
    std::cout << "Receptioner " << idAngajat
              << " supravegheaza check-in pentru Camera ID:" << c->getId() << ".\n";
    consumaEnergie(getCostCheckIn());
}

void Receptioner::checkOut(Camera* c) {
    std::cout << "Receptioner " << idAngajat
              << " supravegheaza check-out pentru Camera ID:" << c->getId() << ".\n";
    consumaEnergie(getCostCheckOut());
}

void Receptioner::servicii() {}