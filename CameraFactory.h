//
// Created by Nati on 12/21/2025.
//

#ifndef CAMERAFACTORY_H
#define CAMERAFACTORY_H

#include <stdexcept>
#include "Single.h"
#include "Double.h"
#include "Suite.h"

class CameraFactory {
public:
    static Camera* creeazaCamera (int tip, int nopti, bool micDejun, bool roomService, bool vedereMare=false, bool minibar=false) {
        switch (tip) {
            case 1: return new Single(nopti, micDejun, roomService);
            case 2: return new Double(nopti, micDejun, roomService, vedereMare);
            case 3: return new Suite(nopti, micDejun, roomService, vedereMare, minibar);
            default: throw std::invalid_argument("Tip camera invalid");
        }
    }
};

#endif //CAMERAFACTORY_H