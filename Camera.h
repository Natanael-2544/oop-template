//
// Created by Nati on 12/19/2025.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

class Camera {
    static int idGenerator;
protected:
    int id;
    int nrNopti;
    int pretNoapte;
    bool micDejun;
    bool roomService;
    double calcPretBaza() const;

public:
    Camera(const int& nrNopti_, const int& pretNoapte_=100, bool micDejun_=false, bool roomService_=false);
    virtual double calcPret() const = 0;
    virtual void afisare(std::ostream& out) const = 0;
    int getId() const;
    bool hasRoomService() const;
    int getNopti() const;
    virtual ~Camera() = default;
    friend std::ostream& operator<<(std::ostream& out, const Camera& c);
};

#endif // CAMERA_H
