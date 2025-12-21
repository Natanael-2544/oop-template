//
// Created by Nati on 12/20/2025.
//

#ifndef CHECKINOUT_H
#define CHECKINOUT_H

#include "Camera.h"

class CheckInOut {
public:
    virtual void checkIn(Camera* c) = 0;
    virtual void checkOut(Camera* c) = 0;
    virtual ~CheckInOut() {}
};

#endif // CHECKINOUT_H
