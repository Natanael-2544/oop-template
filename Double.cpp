//
// Created by Nati on 12/21/2025.
//

#include "Double.h"

Double::Double(const int& nrNopti_, bool micDejun_, bool roomService_, bool vedereMare_)
    : Camera(nrNopti_, 100 * 1.25, micDejun_, roomService_), vedereMare(vedereMare_) {}

double Double::calcPret() const {
    double pret = calcPretBaza();
    if (vedereMare) pret += 5 * nrNopti;
    return pret;
}

void Double::afisare(std::ostream& out) const {
    out << "Double ID:" << id << " Nopti:" << nrNopti
        << " MicDejun:" << micDejun << " RoomService:" << roomService
        << " VedereMare:" << vedereMare
        << " Pret:" << calcPret() << "\n";
}
