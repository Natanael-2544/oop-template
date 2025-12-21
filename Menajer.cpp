//
// Created by Nati on 12/21/2025.
//

#include "Menajer.h"
Menajer::Menajer() : Angajat() {}

// Costul serviciilor
int Menajer::getCostServicii() const { return 15; }

// Execută serviciile
void Menajer::servicii() {
    std::cout << "Menajer " << idAngajat << " efectueaza room service/curațenie.\n";
    consumaEnergie(getCostServicii());
}