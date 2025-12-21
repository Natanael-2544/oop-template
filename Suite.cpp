//
// Created by Nati on 12/21/2025.
//

#include "Suite.h"

Suite::Suite(const int& nrNopti_, bool micDejun_, bool roomService_,
             bool vedereMare_, bool minibar_)
    : Camera(nrNopti_, 100 * 1.5, micDejun_, roomService_),
      vedereMare(vedereMare_), minibar(minibar_) {}

double Suite::calcPret() const {
    double pret = calcPretBaza();
    if (vedereMare) pret += 10 * nrNopti;
    if (minibar) pret += 5 * nrNopti;
    return pret;
}

void Suite::afisare(std::ostream& out) const {
    out << "Suite ID:" << id << " Nopti:" << nrNopti
        << " MicDejun:" << micDejun << " RoomService:" << roomService
        << " VedereMare:" << vedereMare << " Minibar:" << minibar
        << " Pret:" << calcPret() << "\n";
}