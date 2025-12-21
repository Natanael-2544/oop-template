//
// Created by Nati on 12/21/2025.
//

#ifndef OOP_RECEPTIONER_H
#define OOP_RECEPTIONER_H


#include "Angajat.h"
#include "CheckInOut.h"
#include "Camera.h"
#include <iostream>

class Receptioner : public Angajat, public CheckInOut {
public:
    Receptioner();
    int getCostCheckIn() const;
    int getCostCheckOut() const;
    void checkIn(Camera* c) override;
    void checkOut(Camera* c) override;
    void servicii() override;
};

#endif //OOP_RECEPTIONER_H