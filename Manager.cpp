//
// Created by Nati on 12/21/2025.
//

#include "Manager.h"
Manager::Manager() : Angajat() {}

int Manager::getCostCheckIn() const { return 5; }

int Manager::getCostCheckOut() const { return 5; }

void Manager::checkIn(Camera* c) {
    std::cout << "Manager " << idAngajat
              << " supravegheaza check-in pentru Camera ID:" << c->getId() << ".\n";
    consumaEnergie(getCostCheckIn());
}

void Manager::checkOut(Camera* c) {
    std::cout << "Manager " << idAngajat
              << " supravegheaza check-out pentru Camera ID:" << c->getId() << ".\n";
    consumaEnergie(getCostCheckOut());
}

void Manager::servicii() {}