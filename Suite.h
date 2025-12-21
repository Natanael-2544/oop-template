//
// Created by Nati on 12/21/2025.
//

#ifndef SUITE_H
#define SUITE_H

#include "Camera.h"
#include <iostream>

class Suite : public Camera {
    bool vedereMare;
    bool minibar;
public:
    Suite(const int& nrNopti_, bool micDejun_ = false, bool roomService_ = false,
          bool vedereMare_ = false, bool minibar_ = false);

    double calcPret() const override;
    void afisare(std::ostream& out) const override;
};

#endif //SUITE_H