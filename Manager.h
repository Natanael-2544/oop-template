//
// Created by Nati on 12/21/2025.
//

#ifndef OOP_MANAGER_H
#define OOP_MANAGER_H


#include "Angajat.h"
#include "CheckInOut.h"
#include <iostream>

class Manager : public Angajat, public CheckInOut {
public:
    Manager();
    int getCostCheckIn() const;
    int getCostCheckOut() const;
    void checkIn(Camera* c) override;
    void checkOut(Camera* c) override;
    void servicii() override;
};


#endif //OOP_MANAGER_H