//
// Created by Nati on 12/20/2025.
//

#ifndef OOP_ANGAJAT_H
#define OOP_ANGAJAT_H

#include <iostream>
class Angajat {
    static int idGen;
protected:
    int idAngajat;
    int energie;
    void consumaEnergie(int cost) {
        energie -= cost;
        if (energie < 0) {
            std::cout << "Angajatul " << idAngajat << " a ramas fara energie!\n";
        }
    }
public:
    Angajat(const int& energie_ = 100) : idAngajat(++idGen), energie(energie_) {}
    int getEnergie() const { return energie; }
    virtual void servicii() = 0;
    virtual ~Angajat() = default;
};
#endif //OOP_ANGAJAT_H