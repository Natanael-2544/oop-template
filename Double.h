//
// Created by Nati on 12/21/2025.
//

#ifndef DOUBLE_H
#define DOUBLE_H

#include "Camera.h"

class Double: public Camera {
    bool vedereMare;
public:
    Double(const int& nrNopti_,  bool micDejun_ = false, bool roomService_=false, bool vedereMare_ = false)

    double calcPret() const override;
    void afisare(std::ostream& out) const override;
};

#endif // DOUBLE_H
