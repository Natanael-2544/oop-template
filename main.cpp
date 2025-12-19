#include <iostream>
#include <vector>
#include <stdexcept>

//Clasa Camera: Single, Double, Suite
class Camera {
    static int idGenerator;
    int id;
protected:
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

    virtual double calcPret()=0;
    virtual void afisare(std::ostream& out) const = 0;
    friend std::ostream& operator<<(std::ostream& out, const Camera& c) {
        c.afisare(out);
        return out;
    }
    virtual ~ Camera()=default;
};
int Camera::idGenerator = 0;

class Single: public Camera {
public:
    Single(const int& nrNopti_, bool micDejun_ = false, bool roomService_=false):
         Camera(nrNopti_, 100, micDejun_, roomService_) {}

    void afisare(std::ostream& out) const override {
        out<<" Single: "<< getId()
             << " (NrNopti= " <<nrNopti
             << " MicDejun= " <<micDejun
             << " RoomService= " <<roomService<< ")\n";
    }
    double calcPret() override {
        return calcPretBaza();}
};

class Double: public Camera {
    bool vedereMare;
    public:
    Double(const int& nrNopti_,  bool micDejun_ = false, bool roomService_=false, bool vedereMare_ = false)
        : Camera(nrNopti_, 100 * 1.25, micDejun_, roomService_), vedereMare(vedereMare_) {}
    void afisare(std::ostream& out) const override {
        out<<" Double: "<< getId()
             << " (NrNopti= " <<nrNopti
             << " MicDejun= " <<micDejun
             << " RoomService= " <<roomService
             <<" VedereMare= " <<vedereMare<< ")\n";
    }
    double calcPret() override {
        double pret = calcPretBaza();
        if (vedereMare) pret += 5 * nrNopti;
        return pret;
    }
};

class Suite: public Camera {
    bool vedereMare;
    bool minibar;
public:
    Suite(const int& nrNopti_, bool micDejun_ = false, bool roomService_=false, bool vedereMare_ = false, bool minibar_ = false)
        : Camera(nrNopti_, 100 * 1.5, micDejun_, roomService_), vedereMare(vedereMare_), minibar(minibar_) {}
    void afisare(std::ostream& out) const override {
        out<<" Suite: "<< getId()
             << " (NrNopti= " <<nrNopti
             << " MicDejun= " <<micDejun
             << "roomService= "<<roomService
             <<" VedereMare= " <<vedereMare
             <<" Minibar= " <<minibar<< ")";
    }
    double calcPret() override {
        double pret = calcPretBaza();
        if (vedereMare) pret += 10 * nrNopti;
        if (minibar) pret += 15 * nrNopti;
        return pret;
    }
};
//----------------------------------------------------------------------------
//Clasa Angajat

class CheckInOut {
public:
    virtual void checkIn(int camareOcupate) = 0;
    virtual void checkOut(int camareOcupate) = 0;
    virtual ~CheckInOut() {}
};

class Angajat {
    static int idGenAngajat;
protected:
    int idAngajat;
    int energie;
    void consumaEnergie(int cost) {
        energie -= cost;
        if (energie < 0) {
            throw std::runtime_error("Angajat " + std::to_string(idAngajat) + " a rămas fără energie!");
        }
    }
public:
    Angajat(const int& energie_=100):
        idAngajat(++idGenAngajat), energie(energie_) {}
    int getEnergie()const {return energie;}
    int getIdAngajat()const {return idAngajat;}
    void resetEnergie() { energie = 100; }
    virtual void servicii()=0;
    virtual ~Angajat()=default;
};
int Angajat::idGenAngajat=0;

class Receptioner: public Angajat, public CheckInOut {
public:
    Receptioner(): Angajat(){}
    void checkIn(int camereOcupate) override {
        std::cout << "Receptioner " << idAngajat << " face check-in.\n";
        consumaEnergie(25);
    }
    void checkOut(int camereOcupate) override {
        std::cout << "Receptioner " << idAngajat << " face check-out.\n";
        consumaEnergie(25);
    }
    void servicii() override {
        // Receptioner nu face room service
    }
};

class Menajer : public Angajat {
public:
    Menajer() : Angajat() {}

    void servicii() override {
        std::cout << "Menajer " << idAngajat << " efectuează room service/curățenie.\n";
        consumaEnergie(15);
    }
};

class Manager : public Angajat, public CheckInOut {
public:
    Manager() : Angajat() {}
    void checkIn(int camereOcupate) override {
        std::cout << "Manager " << idAngajat << " supraveghează check-in.\n";
        consumaEnergie(5 * camereOcupate);
    }
    void checkOut( int camereOcupate ) override {
        std::cout << "Manager " << idAngajat << " supraveghează check-out.\n";
        consumaEnergie(5 * camereOcupate);
    }
};


int main() {

    return 0;
}
