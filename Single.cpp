//
// Created by Nati on 12/21/2025.
//

// Single.cpp
#include "Single.h"
#include <iostream>

Single::Single(const int& nrNopti_, bool micDejun_, bool roomService_)
    : Camera(nrNopti_, 100, micDejun_, roomService_) {}

double Single::calcPret() const {
    return calcPretBaza();
}

void Single::afisare(std::ostream& out) const {
    out << "Single ID:" << id
        << " Nopti:" << nrNopti
        << " MicDejun:" << micDejun
        << " RoomService:" << roomService
        << " Pret:" << calcPret() << "\n";
}
