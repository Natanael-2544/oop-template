//
// Created by Nati on 12/21/2025.
//

#ifndef SINGLE_H
#define SINGLE_H

#include "Camera.h"
#include <iostream>

class Single : public Camera {
public:
    Single(const int& nrNopti_, bool micDejun_ = false, bool roomService_ = false);

    double calcPret() const override;
    void afisare(std::ostream& out) const override;
};

#endif // SINGLE_H