//
// Created by Nati on 12/19/2025.
//

#include "Camera.h"
class Camera {
    static int idGenerator;
protected:
    int id;
    int nrNopti;
    int pretNoapte;
    bool micDejun;
    bool roomService;
    double calcPretBaza() const {
        double pret = pretNoapte;
        if (micDejun) {pret += 20;}
        if (roomService) {pret += 5;}
        return pret * nrNopti;
    }
public:
    Camera(const int& nrNopti_, const int& pretNoapte_=100, bool micDejun_=false, bool roomService_=false):
    id(++idGenerator), nrNopti(nrNopti_), pretNoapte(pretNoapte_), micDejun(micDejun_), roomService(roomService_) {}
    int getId()const{ return id;}

    virtual double calcPret() const =0;
    virtual void afisare(std::ostream& out) const = 0;
    friend std::ostream& operator<<(std::ostream& out, const Camera& c) {
        c.afisare(out);
        return out;
    }
    bool hasRoomService() const { return roomService; }
    int getNopti() const { return nrNopti; }
    virtual ~ Camera()=default;
};
int Camera::idGenerator = 0;