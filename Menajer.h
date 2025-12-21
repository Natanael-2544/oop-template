//
// Created by Nati on 12/21/2025.
//

#ifndef OOP_MENAJER_H
#define OOP_MENAJER_H


#include "Angajat.h"
#include <iostream>

class Menajer : public Angajat {
public:
    Menajer();
    int getCostServicii() const;
    void servicii() override;
};

#endif //OOP_MENAJER_H