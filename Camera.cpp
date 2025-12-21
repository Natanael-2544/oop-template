//
// Created by Nati on 12/19/2025.
//

#include "Camera.h"

int Camera::idGenerator = 0;

Camera::Camera(const int& nrNopti_, const int& pretNoapte_, bool micDejun_, bool roomService_)
    : id(++idGenerator), nrNopti(nrNopti_), pretNoapte(pretNoapte_), micDejun(micDejun_), roomService(roomService_) {}

double Camera::calcPretBaza() const {
    double pret = pretNoapte;
    if (micDejun) pret += 20;
    if (roomService) pret += 5;
    return pret * nrNopti;
}

int Camera::getId() const { return id; }

std::ostream& operator<<(std::ostream& out, const Camera& c) {
    c.afisare(out);
    return out;
}

bool Camera::hasRoomService() const { return roomService; }

