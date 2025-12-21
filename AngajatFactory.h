//
// Created by Nati on 12/21/2025.
//

#ifndef OOP_ANGAJATFACTORY_H
#define OOP_ANGAJATFACTORY_H

#include <stdexcept>
#include "Receptioner.h"
#include "Menajer.h"
#include "Manager.h"

class AngajatFactory {
public:
    static Angajat* creeazaAngajat (int tip) {
        switch (tip) {
            case 1: return new Receptioner();
            case 2: return new Menajer();
            case 3: return new Manager();
            default: throw std::invalid_argument("Tip angajat invalid");
        }
    }
};

#endif //OOP_ANGAJATFACTORY_H